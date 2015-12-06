#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"
#include "clock.h"
#include "dev/comms.h"
#include "dev/pwm.h"
#include "dev/leds.h"

#include <stdio.h>
#include <stdint.h>

#ifndef SCISSOR_H_
#define SCISSOR_H_

#define PWM_FREQUENCY 20000.0
#define PWM_PERIOD_MS (1000.0 / PWM_FREQUENCY)

//DIR(PHASE pin of DRV8801) connected to Atum B4
//PWM(ENABLE pin of DRV8801) connected to Atum B3

void set_up_single_driver_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void set_up_pwm();
void set_duty_cycle(double new_duty_cycle);
void scissorMotorControl(double direction, double speed);
#endif
