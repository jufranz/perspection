#include "contiki.h"
#include "dev/adc.h"
#include "dev/leds.h"
#include "dev/pwm.h"
#include "dev/quadrature.h"
#include "dev/serial-line.h"
#include "dev/uart.h"

#include <stdio.h>

// Limits and defines

#define PWM_FREQUENCY 25000.0
#define PWM_PERIOD_MS (1000.0 / PWM_FREQUENCY)
#define PWM_POS_PORT_NUM GPIO_B_NUM
#define PWM_POS_PIN_NUM 3
#define PWM_NEG_PORT_NUM GPIO_B_NUM
#define PWM_NEG_PIN_NUM 4

#define TORQUE_MAX 32767.0 // 2^15 - 1, the max ADC value we can get
#define TORQUE_MIN 0.0
#define TORQUE_RANGE ((TORQUE_MAX - TORQUE_MIN) / 2.0)
#define TORQUE_ZERO (TORQUE_MIN + TORQUE_RANGE)
#define TORQUE_ADC_CHANNEL SOC_ADC_ADCCON_CH_AIN3

#define DUTY_CYCLE_MAX_ADJUSTMENT 2.0

// Helpful functions and state

static double duty_cycle;
void set_up_pwm();
void adjust_duty_cycle(double desired_torque);
void set_duty_cycle(double new_duty_cycle);
void set_pos_duty_cycle(double new_duty_cycle);
void set_neg_duty_cycle(double new_duty_cycle);

double get_current_torque();
int16_t read_raw_torque();
double normalize_raw_torque(int16_t raw_torque);

// Torque as a function of position
// Position is in degrees, torque should be -1.0 to 1.0

double torque_from_position(double position) {
    // Spring, should be full torque at -30.0 and 30.0 degrees
    return (position / -30.0);
}

// The torque control loop

void adjust_duty_cycle(double desired_torque) {
    double current_torque = get_current_torque();
    double torque_delta = desired_torque - current_torque; // Between -2.0 and 2.0
    double normalized_torque_delta = torque_delta / 2.0; // Between -1.0 and 1.0
    double duty_cycle_adjustment = (DUTY_CYCLE_MAX_ADJUSTMENT * normalized_torque_delta);

    set_duty_cycle(duty_cycle + duty_cycle_adjustment);
}

// Haptics process

PROCESS(haptics_process, "Haptics");
AUTOSTART_PROCESSES(&haptics_process);
PROCESS_THREAD(haptics_process, ev, data) {
	PROCESS_BEGIN();

    quadrature_init();
    set_up_pwm();

	while(1) {
        double position = quadrature_get_position();
        double desired_torque = torque_from_position(position);
        adjust_duty_cycle(desired_torque);
	}

	PROCESS_END();
}

// Helpful function definitions

void set_up_pwm() {
    pwm_gpt2_pwm1_init();
    pwm_gpt2_pwm1_config_gpio(PWM_POS_PORT_NUM, PWM_POS_PIN_NUM);
    pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm1_start();

    pwm_gpt2_pwm2_init();
    pwm_gpt2_pwm2_config_gpio(PWM_NEG_PORT_NUM, PWM_NEG_PIN_NUM);
    pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm2_start();

    set_duty_cycle(0.0);
}

void set_duty_cycle(double new_duty_cycle) {
    duty_cycle = new_duty_cycle;

    if(duty_cycle < 0.0) {
        set_pos_duty_cycle(0.0);
        set_neg_duty_cycle(-duty_cycle);
        leds_on(LEDS_RED);
        leds_off(LEDS_GREEN);
        leds_off(LEDS_BLUE);
    } else if(duty_cycle > 0.0) {
        set_pos_duty_cycle(duty_cycle);
        set_neg_duty_cycle(0.0);
        leds_off(LEDS_RED);
        leds_on(LEDS_GREEN);
        leds_off(LEDS_BLUE);
    } else {
        set_pos_duty_cycle(0.0);
        set_neg_duty_cycle(0.0);
        leds_off(LEDS_RED);
        leds_off(LEDS_GREEN);
        leds_on(LEDS_BLUE);
    }
}

void set_pos_duty_cycle(double new_duty_cycle) {
    pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, new_duty_cycle);
}

void set_neg_duty_cycle(double new_duty_cycle) {
    pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, new_duty_cycle);
}

double get_current_torque() {
    int16_t raw_torque = read_raw_torque();
    return normalize_raw_torque(raw_torque);
}

int16_t read_raw_torque() {
    return adc_get(TORQUE_ADC_CHANNEL, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512);
}

double normalize_raw_torque(int16_t raw_torque) {
    return (((double)raw_torque - TORQUE_ZERO) / TORQUE_RANGE);
}

