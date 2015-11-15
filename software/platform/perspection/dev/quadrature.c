#include "dev/quadrature.h"

#include "dev/gpio.h"
#include "dev/ioc.h"
#include "dev/nvic.h"
#include "dev/leds.h"

#define CHANNEL_A_PIN 4
#define CHANNEL_B_PIN 5

#define COUNTS_PER_REV 4096.0
#define DEGREES_PER_COUNT (360.0 / COUNTS_PER_REV)

static double current_position;

void quadrature_set_up_gpio(int pin_number);

void channel_a_positive_edge(uint8_t port, uint8_t pin) {
    if(GPIO_READ_PIN(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN)) == 0) {
        leds_off(LEDS_RED);
        leds_toggle(LEDS_GREEN);
        current_position += DEGREES_PER_COUNT;
    } else {
        leds_off(LEDS_GREEN);
        leds_toggle(LEDS_RED);
        current_position -= DEGREES_PER_COUNT;
    }
}

void channel_b_positive_edge(uint8_t port, uint8_t pin) {
    if(GPIO_READ_PIN(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN)) == 0) {
        leds_off(LEDS_GREEN);
        leds_toggle(LEDS_RED);
        current_position -= DEGREES_PER_COUNT;
    } else {
        leds_off(LEDS_RED);
        leds_toggle(LEDS_GREEN);
        current_position += DEGREES_PER_COUNT;
    }
}

void quadrature_init() {
    current_position = 0.0;

    quadrature_set_up_gpio(CHANNEL_A_PIN);
    quadrature_set_up_gpio(CHANNEL_B_PIN);

    nvic_interrupt_enable(NVIC_INT_GPIO_PORT_B);

    gpio_register_callback(&channel_a_positive_edge, GPIO_B_NUM, CHANNEL_A_PIN);
    gpio_register_callback(&channel_b_positive_edge, GPIO_B_NUM, CHANNEL_B_PIN);
}

void quadrature_set_up_gpio(int pin_number) {
    GPIO_SOFTWARE_CONTROL(GPIO_B_BASE, GPIO_PIN_MASK(pin_number));
    GPIO_SET_INPUT(GPIO_B_BASE, GPIO_PIN_MASK(pin_number));
    GPIO_DETECT_EDGE(GPIO_B_BASE, GPIO_PIN_MASK(pin_number));
    GPIO_TRIGGER_SINGLE_EDGE(GPIO_B_BASE, GPIO_PIN_MASK(pin_number));
    GPIO_DETECT_RISING(GPIO_B_BASE, GPIO_PIN_MASK(pin_number));
    GPIO_ENABLE_INTERRUPT(GPIO_B_BASE, GPIO_PIN_MASK(pin_number));
    ioc_set_over(GPIO_B_BASE, pin_number, IOC_OVERRIDE_PDE);
}

double quadrature_get_position() {
    return current_position;
}

