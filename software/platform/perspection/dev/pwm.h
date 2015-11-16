#ifndef ATUM_PWM_H_
#define ATUM_PWM_H_

#include "dev/gpio.h"
#include "dev/ioc.h"

void pwm_gpt0_pwm1_init();
void pwm_gpt0_pwm1_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt0_pwm1_set_timing(double period_ms, double duty_cycle);
void pwm_gpt0_pwm1_start();
void pwm_gpt0_pwm1_stop();

void pwm_gpt0_pwm2_init();
void pwm_gpt0_pwm2_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt0_pwm2_set_timing(double period_ms, double duty_cycle);
void pwm_gpt0_pwm2_start();
void pwm_gpt0_pwm2_stop();

void pwm_gpt1_pwm1_init();
void pwm_gpt1_pwm1_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt1_pwm1_set_timing(double period_ms, double duty_cycle);
void pwm_gpt1_pwm1_start();
void pwm_gpt1_pwm1_stop();

void pwm_gpt1_pwm2_init();
void pwm_gpt1_pwm2_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt1_pwm2_set_timing(double period_ms, double duty_cycle);
void pwm_gpt1_pwm2_start();
void pwm_gpt1_pwm2_stop();

void pwm_gpt2_pwm1_init();
void pwm_gpt2_pwm1_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt2_pwm1_set_timing(double period_ms, double duty_cycle);
void pwm_gpt2_pwm1_start();
void pwm_gpt2_pwm1_stop();

void pwm_gpt2_pwm2_init();
void pwm_gpt2_pwm2_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt2_pwm2_set_timing(double period_ms, double duty_cycle);
void pwm_gpt2_pwm2_start();
void pwm_gpt2_pwm2_stop();

void pwm_gpt3_pwm1_init();
void pwm_gpt3_pwm1_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt3_pwm1_set_timing(double period_ms, double duty_cycle);
void pwm_gpt3_pwm1_start();
void pwm_gpt3_pwm1_stop();

void pwm_gpt3_pwm2_init();
void pwm_gpt3_pwm2_config_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void pwm_gpt3_pwm2_set_timing(double period_ms, double duty_cycle);
void pwm_gpt3_pwm2_start();
void pwm_gpt3_pwm2_stop();

#endif
