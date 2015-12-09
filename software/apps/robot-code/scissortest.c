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

#define PWM_FREQUENCY 20000.0
#define PWM_PERIOD_MS (1000.0 / PWM_FREQUENCY)

#define POS_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define POS_DRIVER_CTL_PIN_NUM 3
#define NEG_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define NEG_DRIVER_CTL_PIN_NUM 4


static double haptics_duty_cycle;
void set_up_pwm();
void set_up_single_driver_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void adjust_duty_cycle(double desired_torque);
void set_duty_cycle(double new_duty_cycle);

PROCESS_THREAD(init_linkaddr_process, ev, data) {
    PROCESS_BEGIN();

    set_up_pwm();

    static linkaddr_t nodeAddr;
    nodeAddr.u8[0] = BODY_ADDR_A;
    nodeAddr.u8[1] = BODY_ADDR_B;
    linkaddr_set_node_addr(&nodeAddr);

    process_start(&init_network_process, NULL);

    PROCESS_END();
}

void set_up_pwm() {
    pwm_gpt2_pwm1_init();
    pwm_gpt2_pwm1_config_gpio(POS_DRIVER_CTL_PORT_NUM, POS_DRIVER_CTL_PIN_NUM);
    pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm1_start();

    pwm_gpt2_pwm2_init();
    pwm_gpt2_pwm2_config_gpio(NEG_DRIVER_CTL_PORT_NUM, NEG_DRIVER_CTL_PIN_NUM);
    pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm2_start();

    set_duty_cycle(50.0);
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
