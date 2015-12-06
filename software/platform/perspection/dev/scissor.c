#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"
#include "clock.h"
#include "dev/comms.h"
#include "dev/leds.h"
#include "dev/scissor.h"

#include <math.h>
#include <stdio.h>
#include <stdint.h>


void set_up_pwm() {
    pwm_gpt2_pwm1_init();
    pwm_gpt2_pwm1_config_gpio(GPIO_B_NUM, 4);
    pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm1_start();

    pwm_gpt2_pwm2_init();
    pwm_gpt2_pwm2_config_gpio(GPIO_B_NUM, 4);
    pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm2_start();

    set_duty_cycle(0.0);
}

void scissorMotorControl(double direction, double speed) {

    set_up_pwm();
    double dirInRads = (direction * M_PI) / 180.0;
    double dutyCycle1 = (speed * cos(((150.0 * M_PI) / 180.0) - dirInRads));

    uint16_t direction1 = (dutyCycle1 > 0.0) ? 1 : 0;

    dutyCycle1 = (dutyCycle1 < 0.0) ? (dutyCycle1 * -1.0) : dutyCycle1;

	set_duty_cycle(dutyCycle1);
    
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
