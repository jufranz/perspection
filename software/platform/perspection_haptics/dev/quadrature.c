#include "dev/quadrature.h"

#include "dev/gpio.h"
#include "dev/ioc.h"
#include "dev/nvic.h"

#include "dev/leds.h"

#define CHANNEL_A_PIN 4
#define CHANNEL_B_PIN 5

QuadratureCallback registeredCallback;

int32_t current_position;

void channel_a_positive_edge(uint8_t port, uint8_t pin) {
    if(GPIO_READ_PIN(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN)) == 0) {
        current_position++;
    } else {
        current_position--;
    }

    if(registeredCallback != NULL) {
        registeredCallback(current_position, 0.0);
    }

    leds_toggle(LEDS_RED);
}

void channel_b_positive_edge(uint8_t port, uint8_t pin) {
    if(GPIO_READ_PIN(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN)) == 0) {
        current_position--;
    } else {
        current_position++;
    }

    if(registeredCallback != NULL) {
        registeredCallback(current_position, 0.0);
    }

    leds_toggle(LEDS_RED);
}

void quadrature_init() {
    gpio_init();
    leds_toggle(LEDS_RED);

    registeredCallback = NULL;
    current_position = 0;

    GPIO_SOFTWARE_CONTROL(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN));
    GPIO_SET_INPUT(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN));
    GPIO_DETECT_EDGE(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN));
    GPIO_TRIGGER_SINGLE_EDGE(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN));
    GPIO_DETECT_RISING(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN));
    GPIO_ENABLE_INTERRUPT(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_A_PIN));
    ioc_set_over(GPIO_B_BASE, CHANNEL_A_PIN, IOC_OVERRIDE_PDE);

    GPIO_SOFTWARE_CONTROL(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN));
    GPIO_SET_INPUT(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN));
    GPIO_DETECT_EDGE(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN));
    GPIO_TRIGGER_SINGLE_EDGE(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN));
    GPIO_DETECT_RISING(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN));
    GPIO_ENABLE_INTERRUPT(GPIO_B_BASE, GPIO_PIN_MASK(CHANNEL_B_PIN));
    ioc_set_over(GPIO_B_BASE, CHANNEL_B_PIN, IOC_OVERRIDE_PDE);

    nvic_interrupt_enable(NVIC_INT_GPIO_PORT_B);

    gpio_register_callback(&channel_b_positive_edge, GPIO_B_NUM, CHANNEL_B_PIN);
    gpio_register_callback(&channel_a_positive_edge, GPIO_B_NUM, CHANNEL_A_PIN);
}

void quadrature_register_callback(QuadratureCallback callback) {
    registeredCallback = callback;
}
