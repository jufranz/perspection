/*
 * perspection_pwm.h
 *
 *  Created on: Nov 22, 2015
 *      Author: boztalay
 */

#ifndef PERSPECTION_PWM_H_
#define PERSPECTION_PWM_H_

#include "hal.h"

void perspection_pwm_1a_init(HAL_Handle halHandle, double period_usec);
void perspection_pwm_1a_set_duty_cycle(double duty_cycle);
void perspection_pwm_1b_init(HAL_Handle halHandle, double period_usec);
void perspection_pwm_1b_set_duty_cycle(double duty_cycle);
void perspection_pwm_2a_init(HAL_Handle halHandle, double period_usec);
void perspection_pwm_2a_set_duty_cycle(double duty_cycle);
void perspection_pwm_2b_init(HAL_Handle halHandle, double period_usec);
void perspection_pwm_2b_set_duty_cycle(double duty_cycle);
void perspection_pwm_3a_init(HAL_Handle halHandle, double period_usec);
void perspection_pwm_3a_set_duty_cycle(double duty_cycle);
void perspection_pwm_3b_init(HAL_Handle halHandle, double period_usec);
void perspection_pwm_3b_set_duty_cycle(double duty_cycle);

#endif /* PERSPECTION_PWM_H_ */
