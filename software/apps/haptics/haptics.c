#include "contiki.h"
#include "dev/adc.h"
#include "dev/gpio.h"
#include "dev/ioc.h"
#include "dev/leds.h"
#include "dev/pwm.h"
#include "dev/quadrature.h"
#include "dev/serial-line.h"
#include "dev/uart.h"
#include "sys/clock.h"

#include <stdio.h>

// Limits and defines

#define PWM_FREQUENCY 20000.0
#define PWM_PERIOD_MS (1000.0 / PWM_FREQUENCY)

#define POS_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define POS_DRIVER_CTL_PIN_NUM 3
#define NEG_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define NEG_DRIVER_CTL_PIN_NUM 4

#define TORQUE_MAX 20068.0 // Calibrated to the hardware
#define TORQUE_MIN 9444.0
#define TORQUE_RANGE ((TORQUE_MAX - TORQUE_MIN) / 2.0)
#define TORQUE_ADC_CHANNEL SOC_ADC_ADCCON_CH_AIN3
#define TORQUE_ADC_PORT_NUM GPIO_A_NUM
#define TORQUE_ADC_PIN_NUM 3

#define TORQUE_DIRECTION_POSITIVE 0
#define TORQUE_DIRECTION_NEGATIVE 1

#define DUTY_CYCLE_MAX_ADJUSTMENT 0.01

// Helpful functions and state

static double haptics_duty_cycle;
void set_up_pwm();
void set_up_single_driver_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void adjust_duty_cycle(double desired_torque);
void set_duty_cycle(double new_duty_cycle);

static double torque_zero;
void calibrate_zero_torque();
double get_current_torque();
int16_t read_raw_torque();
double normalize_raw_torque(int16_t raw_torque);

// Torque as a function of position
// Position is in degrees, torque should be -1.0 to 1.0

double torque_from_position(double position) {
    if(position > 90.0) {
        leds_on(LEDS_RED);
        leds_off(LEDS_GREEN);
        leds_off(LEDS_BLUE);
    } else if(position > 45.0) {
        leds_off(LEDS_RED);
        leds_off(LEDS_GREEN);
        leds_on(LEDS_BLUE);
    } else {
        leds_off(LEDS_RED);
        leds_on(LEDS_GREEN);
        leds_off(LEDS_BLUE);
    }

    // Loose spring
    /*return (position / -360.0);*/

    // Wall
    if(position > 45.0) {
        return -0.5;
    } else {
        return 0;
    }
}

// The torque control loop

void adjust_duty_cycle(double desired_torque) {
    double current_torque = get_current_torque();

    double torque_delta = desired_torque - current_torque; // Between -2.0 and 2.0
    double normalized_torque_delta = torque_delta / 2.0; // Between -1.0 and 1.0
    double duty_cycle_adjustment = (DUTY_CYCLE_MAX_ADJUSTMENT * normalized_torque_delta);
    set_duty_cycle(haptics_duty_cycle + duty_cycle_adjustment);
}

// Haptics process

PROCESS(haptics_process, "Haptics");
AUTOSTART_PROCESSES(&haptics_process);
PROCESS_THREAD(haptics_process, ev, data) {
	PROCESS_BEGIN();

    leds_on(LEDS_BLUE);

    quadrature_init();
    set_up_pwm();
    ioc_set_over(TORQUE_ADC_PORT_NUM, TORQUE_ADC_PIN_NUM, IOC_OVERRIDE_ANA);

    calibrate_zero_torque();

    leds_off(LEDS_BLUE);
    leds_on(LEDS_GREEN);

	while(1) {
        double position = quadrature_get_position();

        double desired_torque = torque_from_position(position);
        if(desired_torque < -1.0) {
            desired_torque = -1.0;
        } else if(desired_torque > 1.0) {
            desired_torque = 1.0;
        }

        adjust_duty_cycle(desired_torque);
	}

	PROCESS_END();
}

// Helpful function definitions

void set_up_pwm() {
    pwm_gpt2_pwm1_init();
    pwm_gpt2_pwm1_config_gpio(POS_DRIVER_CTL_PORT_NUM, POS_DRIVER_CTL_PIN_NUM);
    pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm1_start();

    pwm_gpt2_pwm2_init();
    pwm_gpt2_pwm2_config_gpio(NEG_DRIVER_CTL_PORT_NUM, NEG_DRIVER_CTL_PIN_NUM);
    pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm2_start();

    set_duty_cycle(0.0);
}

void set_up_single_driver_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(gpio_port_num), GPIO_PIN_MASK(gpio_pin_num));
    GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(gpio_port_num), GPIO_PIN_MASK(gpio_pin_num));
    ioc_set_over(gpio_port_num, gpio_pin_num, IOC_OVERRIDE_OE);
}

void set_duty_cycle(double new_duty_cycle) {
    haptics_duty_cycle = new_duty_cycle;
    if(haptics_duty_cycle < -1.0) {
        haptics_duty_cycle = -1.0;
    } else if(haptics_duty_cycle > 1.0) {
        haptics_duty_cycle = 1.0;
    }

    if(haptics_duty_cycle < 0.0) {
        pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
        pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, -haptics_duty_cycle);
    } else if(haptics_duty_cycle > 0.0) {
        pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, haptics_duty_cycle);
        pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    } else {
        pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
        pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    }
}

void calibrate_zero_torque() {
    int16_t last_raw_torque = read_raw_torque();
    int16_t this_raw_torque;

    while(1) {
        // Wait 260ms
        clock_delay_usec(0xffff);
        clock_delay_usec(0xffff);
        clock_delay_usec(0xffff);
        clock_delay_usec(0xffff);

        // See how much the torque has changed
        this_raw_torque = read_raw_torque();
        int16_t torque_change = (this_raw_torque - last_raw_torque);
        torque_change = (torque_change < 0) ? (torque_change * -1) : torque_change;

        // If it's changed less than +/- 2mV, we're calibrated
        if(torque_change < 20) {
            break;
        }

        // Else, try again
        last_raw_torque = this_raw_torque;
    }

    torque_zero = this_raw_torque;
}

double get_current_torque() {
    int16_t raw_torque = read_raw_torque();
    return normalize_raw_torque(raw_torque);
}

int16_t read_raw_torque() {
    return adc_get(TORQUE_ADC_CHANNEL, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512);
}

double normalize_raw_torque(int16_t raw_torque) {
    return (((double)raw_torque - torque_zero) / TORQUE_RANGE);
}

