/*
 * perspection_pwm.c
 *
 *  Created on: Nov 22, 2015
 *      Author: boztalay
 */

#include "perspection_pwm.h"
#include <stdint.h>

// Defines

#define PERSPECTION_PWM_A 0
#define PERSPECTION_PWM_B 1

// Globals

PWM_Handle pwm1Handle = (PWM_Handle)NULL;
PWM_Handle pwm2Handle = (PWM_Handle)NULL;
PWM_Handle pwm3Handle = (PWM_Handle)NULL;

// Generic functions

void perspection_pwm_make_obj(PWM_Handle* pwmHandle, uint32_t pwm_base_addr) {
	if(*pwmHandle != NULL) {
		return;
	}

	(*pwmHandle) = PWM_init((void*)pwm_base_addr, sizeof(PWM_Obj));
}

void perspection_pwm_init(HAL_Handle halHandle, PWM_Handle pwmHandle, uint16_t a_or_b, double period_usec) {
	HAL_Obj* obj = (HAL_Obj*)halHandle;
	uint16_t periodVal = (uint16_t)(90.075 * period_usec);

	CLK_disableTbClockSync(obj->clkHandle);

	PWM_setCounterMode(pwmHandle, PWM_CounterMode_Up);
	PWM_setPeriod(pwmHandle, periodVal);
	PWM_enableCounterLoad(pwmHandle);
	PWM_setPhase(pwmHandle, 0);
	PWM_setCount(pwmHandle, 0);
	PWM_setHighSpeedClkDiv(pwmHandle, PWM_HspClkDiv_by_1);
	PWM_setClkDiv(pwmHandle, PWM_ClkDiv_by_1);

	if(a_or_b == PERSPECTION_PWM_A) {
		PWM_write_CmpA(pwmHandle, 0);
		PWM_setShadowMode_CmpA(pwmHandle, PWM_ShadowMode_Shadow);
		PWM_setLoadMode_CmpA(pwmHandle, PWM_LoadMode_Zero);
		PWM_setActionQual_Zero_PwmA(pwmHandle, PWM_ActionQual_Set);
		PWM_setActionQual_CntUp_CmpA_PwmA(pwmHandle, PWM_ActionQual_Clear);
	} else {
		PWM_write_CmpB(pwmHandle, 0);
		PWM_setShadowMode_CmpB(pwmHandle, PWM_ShadowMode_Shadow);
		PWM_setLoadMode_CmpB(pwmHandle, PWM_LoadMode_Zero);
		PWM_setActionQual_Zero_PwmB(pwmHandle, PWM_ActionQual_Set);
		PWM_setActionQual_CntUp_CmpB_PwmB(pwmHandle, PWM_ActionQual_Clear);
	}

	PWM_setSyncMode(pwmHandle, PWM_SyncMode_EPWMxSYNC);
	PWM_setPhaseDir(pwmHandle, PWM_PhaseDir_CountUp);
	PWM_setRunMode(pwmHandle, PWM_RunMode_FreeRun);

	CLK_enableTbClockSync(obj->clkHandle);
}

void perspection_pwm_set_duty_cycle(PWM_Handle pwmHandle, uint16_t a_or_b, double duty_cycle) {
	uint16_t period = PWM_getPeriod(pwmHandle);
	uint16_t duty_cycle_val = (uint16_t)((double)period * duty_cycle);

	if(a_or_b == PERSPECTION_PWM_A) {
		PWM_write_CmpA(pwmHandle, duty_cycle_val);
	} else {
		PWM_write_CmpB(pwmHandle, duty_cycle_val);
	}
}

// More specific functions because fuck having to remember registers and shit.

// Also if you call set_duty_cycle before init, you're a dunk ass and deserve
// whatever pain is brought upon you.
// And no, there isn't a goddamn set_period function because who the fuck
// do you think you are anyway?

void perspection_pwm_1a_init(HAL_Handle halHandle, double period_usec) {
	perspection_pwm_make_obj(&pwm1Handle, PWM_ePWM1_BASE_ADDR);
	perspection_pwm_init(halHandle, pwm1Handle, PERSPECTION_PWM_A, period_usec);
}

void perspection_pwm_1a_set_duty_cycle(double duty_cycle) {
	perspection_pwm_set_duty_cycle(pwm1Handle, PERSPECTION_PWM_A, duty_cycle);
}

void perspection_pwm_1b_init(HAL_Handle halHandle, double period_usec) {
	perspection_pwm_make_obj(&pwm1Handle, PWM_ePWM1_BASE_ADDR);
	perspection_pwm_init(halHandle, pwm1Handle, PERSPECTION_PWM_B, period_usec);
}

void perspection_pwm_1b_set_duty_cycle(double duty_cycle) {
	perspection_pwm_set_duty_cycle(pwm1Handle, PERSPECTION_PWM_B, duty_cycle);
}

void perspection_pwm_2a_init(HAL_Handle halHandle, double period_usec) {
	perspection_pwm_make_obj(&pwm2Handle, PWM_ePWM2_BASE_ADDR);
	perspection_pwm_init(halHandle, pwm2Handle, PERSPECTION_PWM_A, period_usec);
}

void perspection_pwm_2a_set_duty_cycle(double duty_cycle) {
	perspection_pwm_set_duty_cycle(pwm2Handle, PERSPECTION_PWM_A, duty_cycle);
}

void perspection_pwm_2b_init(HAL_Handle halHandle, double period_usec) {
	perspection_pwm_make_obj(&pwm2Handle, PWM_ePWM2_BASE_ADDR);
	perspection_pwm_init(halHandle, pwm2Handle, PERSPECTION_PWM_B, period_usec);
}

void perspection_pwm_2b_set_duty_cycle(double duty_cycle) {
	perspection_pwm_set_duty_cycle(pwm2Handle, PERSPECTION_PWM_B, duty_cycle);
}

void perspection_pwm_3a_init(HAL_Handle halHandle, double period_usec) {
	perspection_pwm_make_obj(&pwm3Handle, PWM_ePWM3_BASE_ADDR);
	perspection_pwm_init(halHandle, pwm3Handle, PERSPECTION_PWM_A, period_usec);
}

void perspection_pwm_3a_set_duty_cycle(double duty_cycle) {
	perspection_pwm_set_duty_cycle(pwm3Handle, PERSPECTION_PWM_A, duty_cycle);
}

void perspection_pwm_3b_init(HAL_Handle halHandle, double period_usec) {
	perspection_pwm_make_obj(&pwm3Handle, PWM_ePWM3_BASE_ADDR);
	perspection_pwm_init(halHandle, pwm3Handle, PERSPECTION_PWM_B, period_usec);
}

void perspection_pwm_3b_set_duty_cycle(double duty_cycle) {
	perspection_pwm_set_duty_cycle(pwm3Handle, PERSPECTION_PWM_B, duty_cycle);
}
