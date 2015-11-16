#include "pwm.h"

#include "dev/gptimer.h"
#include "dev/sys-ctrl.h"

#define PWM_CLOCK_FREQUENCY 16000000.0
#define PWM_MAX_PERIOD_VAL 0xffff
#define PWM_MIN_PERIOD_VAL 0x00ff

#define PWM_TIMER_1_SEL 1
#define PWM_TIMER_2_SEL 2

// Generic functions to be used by the more specific functions below

void pwm_set_up_timer(uint8_t gptimer_num, uint32_t gptimer_base, uint32_t timer_sel) {
    REG(SYS_CTRL_RCGCGPT) |= 1 << gptimer_num; // Enable the clock for this timer during active mode
    REG(SYS_CTRL_SCGCGPT) |= 1 << gptimer_num; // Enable the clock for this timer during sleep mode
    REG(SYS_CTRL_DCGCGPT) |= 1 << gptimer_num; // Enable the clock for this timer during deep sleep mode

    REG(gptimer_base + GPTIMER_CFG) = 0x4; // Configure as PWM mode

    uint32_t mr_register = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_TAMR : GPTIMER_TBMR;
    REG(gptimer_base + mr_register) |= GPTIMER_TAMR_TAAMS; // PWM mode
    REG(gptimer_base + mr_register) |= GPTIMER_TAMR_TACMR; // Edge-time capture mode
    REG(gptimer_base + mr_register) = (REG(gptimer_base + mr_register) & ~GPTIMER_TAMR_TAMR) | GPTIMER_TAMR_TAMR_PERIODIC; // Periodic mode

    uint32_t pwm_inversion_bitmask = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_CTL_TAPWML : GPTIMER_CTL_TBPWML;
    REG(gptimer_base + GPTIMER_CTL) |= pwm_inversion_bitmask; // Invert the PWM (makes math a little nicer)

    uint32_t pr_register = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_TAPR : GPTIMER_TBPR;
    REG(gptimer_base + pr_register) = 0x0; // No prescale
}

void pwm_config_gpio(uint32_t ioc_pin_select, uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    uint32_t gpio_port_base = GPIO_PORT_TO_BASE(gpio_port_num);
    GPIO_PERIPHERAL_CONTROL(gpio_port_base, GPIO_PIN_MASK(gpio_pin_num));
    GPIO_SET_OUTPUT(gpio_port_base, GPIO_PIN_MASK(gpio_pin_num));
    ioc_set_over(gpio_port_num, gpio_pin_num, IOC_OVERRIDE_OE);
    ioc_set_sel(gpio_port_num, gpio_pin_num, ioc_pin_select);
}

void pwm_set_timing(uint32_t gptimer_base, uint32_t timer_sel, double period_ms, double duty_cycle) {
    // Figure out and write the period value

    uint32_t interval_load_register = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_TAILR : GPTIMER_TBILR;

    uint16_t period_value = (uint16_t)((PWM_CLOCK_FREQUENCY * period_ms) / 1000.0);
    if(period_value < PWM_MIN_PERIOD_VAL) {
        period_value = PWM_MIN_PERIOD_VAL;
    } else if(period_value > PWM_MAX_PERIOD_VAL) {
        period_value = PWM_MAX_PERIOD_VAL;
    }

    REG(gptimer_base + interval_load_register) = period_value;

    // Figure out and write the duty cycle value

    uint32_t match_register = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_TAMATCHR : GPTIMER_TBMATCHR;
    uint16_t duty_cycle_value = (uint16_t)(period_value * duty_cycle);
    REG(gptimer_base + match_register) = duty_cycle_value;
}

void pwm_start(uint32_t gptimer_base, uint32_t timer_sel) {
    uint32_t gptimer_en_bitmask = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_CTL_TAEN : GPTIMER_CTL_TBEN;
    REG(gptimer_base + GPTIMER_CTL) |= gptimer_en_bitmask;
}

void pwm_stop(uint32_t gptimer_base, uint32_t timer_sel) {
    uint32_t gptimer_en_bitmask = (timer_sel == PWM_TIMER_1_SEL) ? GPTIMER_CTL_TAEN : GPTIMER_CTL_TBEN;
    REG(gptimer_base + GPTIMER_CTL) &= ~gptimer_en_bitmask;
}

// Specific, user-facing functions

// GPT 0, timer A

void pwm_gpt0_pwm1_init() {
    pwm_gpt0_pwm1_stop();
    pwm_set_up_timer(0, GPT_0_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt0_pwm1_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT0_ICP1, gpio_port_num, gpio_pin_num);
}

void pwm_gpt0_pwm1_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_0_BASE, PWM_TIMER_1_SEL, period_ms, duty_cycle);
}

void pwm_gpt0_pwm1_start() {
    pwm_start(GPT_0_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt0_pwm1_stop() {
    pwm_stop(GPT_0_BASE, PWM_TIMER_1_SEL);
}

// GPT 0, timer B

void pwm_gpt0_pwm2_init() {
    pwm_gpt0_pwm2_stop();
    pwm_set_up_timer(0, GPT_0_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt0_pwm2_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT0_ICP2, gpio_port_num, gpio_pin_num);
}

void pwm_gpt0_pwm2_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_0_BASE, PWM_TIMER_2_SEL, period_ms, duty_cycle);
}

void pwm_gpt0_pwm2_start() {
    pwm_start(GPT_0_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt0_pwm2_stop() {
    pwm_stop(GPT_0_BASE, PWM_TIMER_2_SEL);
}

// GPT 1, timer A

void pwm_gpt1_pwm1_init() {
    pwm_gpt1_pwm1_stop();
    pwm_set_up_timer(1, GPT_1_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt1_pwm1_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT1_ICP1, gpio_port_num, gpio_pin_num);
}

void pwm_gpt1_pwm1_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_1_BASE, PWM_TIMER_1_SEL, period_ms, duty_cycle);
}

void pwm_gpt1_pwm1_start() {
    pwm_start(GPT_1_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt1_pwm1_stop() {
    pwm_stop(GPT_1_BASE, PWM_TIMER_1_SEL);
}

// GPT 1, timer B

void pwm_gpt1_pwm2_init() {
    pwm_gpt1_pwm2_stop();
    pwm_set_up_timer(1, GPT_1_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt1_pwm2_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT1_ICP2, gpio_port_num, gpio_pin_num);
}

void pwm_gpt1_pwm2_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_1_BASE, PWM_TIMER_2_SEL, period_ms, duty_cycle);
}

void pwm_gpt1_pwm2_start() {
    pwm_start(GPT_1_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt1_pwm2_stop() {
    pwm_stop(GPT_1_BASE, PWM_TIMER_2_SEL);
}

// GPT 2, timer A

void pwm_gpt2_pwm1_init() {
    pwm_gpt2_pwm1_stop();
    pwm_set_up_timer(2, GPT_2_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt2_pwm1_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT2_ICP1, gpio_port_num, gpio_pin_num);
}

void pwm_gpt2_pwm1_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_2_BASE, PWM_TIMER_1_SEL, period_ms, duty_cycle);
}

void pwm_gpt2_pwm1_start() {
    pwm_start(GPT_2_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt2_pwm1_stop() {
    pwm_stop(GPT_2_BASE, PWM_TIMER_1_SEL);
}

// GPT 2, timer B

void pwm_gpt2_pwm2_init() {
    pwm_gpt2_pwm2_stop();
    pwm_set_up_timer(2, GPT_2_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt2_pwm2_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT2_ICP2, gpio_port_num, gpio_pin_num);
}

void pwm_gpt2_pwm2_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_2_BASE, PWM_TIMER_2_SEL, period_ms, duty_cycle);
}

void pwm_gpt2_pwm2_start() {
    pwm_start(GPT_2_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt2_pwm2_stop() {
    pwm_stop(GPT_2_BASE, PWM_TIMER_2_SEL);
}

// GPT 3, timer A

void pwm_gpt3_pwm1_init() {
    pwm_gpt3_pwm1_stop();
    pwm_set_up_timer(3, GPT_3_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt3_pwm1_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT3_ICP1, gpio_port_num, gpio_pin_num);
}

void pwm_gpt3_pwm1_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_3_BASE, PWM_TIMER_1_SEL, period_ms, duty_cycle);
}

void pwm_gpt3_pwm1_start() {
    pwm_start(GPT_3_BASE, PWM_TIMER_1_SEL);
}

void pwm_gpt3_pwm1_stop() {
    pwm_stop(GPT_3_BASE, PWM_TIMER_1_SEL);
}

// GPT 3, timer B

void pwm_gpt3_pwm2_init() {
    pwm_gpt3_pwm2_stop();
    pwm_set_up_timer(3, GPT_3_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt3_pwm2_config_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    pwm_config_gpio(IOC_PXX_SEL_GPT3_ICP2, gpio_port_num, gpio_pin_num);
}

void pwm_gpt3_pwm2_set_timing(double period_ms, double duty_cycle) {
    pwm_set_timing(GPT_3_BASE, PWM_TIMER_2_SEL, period_ms, duty_cycle);
}

void pwm_gpt3_pwm2_start() {
    pwm_start(GPT_3_BASE, PWM_TIMER_2_SEL);
}

void pwm_gpt3_pwm2_stop() {
    pwm_stop(GPT_3_BASE, PWM_TIMER_2_SEL);
}

