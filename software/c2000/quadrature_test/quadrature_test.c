// **************************************************************************
// the includes
#include "main_position.h"

// **************************************************************************
// the defines

#define LED_BLINK_FREQ_Hz   5

// **************************************************************************
// the globals

HAL_Handle halHandle;
USER_Params gUserParams;
PWM_Handle pwmHandle;

// **************************************************************************
// the functions

void pwm_setup();
void pwm_set_duty_cycle(double duty_cycle);

void main(void) {
	// initialize the hardware abstraction layer
	halHandle = HAL_init(&hal, sizeof(hal));

	// check for errors in user parameters
	USER_checkForErrors(&gUserParams);

	// initialize the user parameters
	USER_setParams(&gUserParams);

	// set the hardware abstraction layer parameters
	HAL_setParams(halHandle, &gUserParams);

	// setup faults
	HAL_setupFaults(halHandle);

	// enable global interrupts
	HAL_enableGlobalInts(halHandle);

	// enable debug interrupts
	HAL_enableDebugInt(halHandle);

	pwm_setup();

	for (;;) {
		uint32_t rawPosition = HAL_getQepPosnCounts(halHandle);
		double position = (double) (360 * rawPosition) / (double) HAL_getQepPosnMaximum(halHandle);

		if (position > 330.0 || position < 30.0) {
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			pwm_set_duty_cycle(0.15);
		} else if (position > 270.0 || position < 90.0) {
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			pwm_set_duty_cycle(0.35);
		} else if (position < 210.0 && position > 150.0) {
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			pwm_set_duty_cycle(0.90);
		} else {
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			pwm_set_duty_cycle(0.60);
		}
	}
}

void pwm_setup() {
	HAL_Obj* obj = (HAL_Obj*)halHandle;
	pwmHandle = PWM_init((void *) PWM_ePWM1_BASE_ADDR, sizeof(PWM_Obj));

	CLK_disableTbClockSync(obj->clkHandle);

	PWM_setCounterMode(pwmHandle, PWM_CounterMode_Up);
	PWM_setPeriod(pwmHandle, 2000);
	PWM_enableCounterLoad(pwmHandle);
	PWM_setPhase(pwmHandle, 0);
	PWM_setCount(pwmHandle, 0);
	PWM_setHighSpeedClkDiv(pwmHandle, PWM_HspClkDiv_by_1);
	PWM_setClkDiv(pwmHandle, PWM_ClkDiv_by_1);

	PWM_write_CmpA(pwmHandle, 1000);
	PWM_write_CmpB(pwmHandle, 1000);

	PWM_setShadowMode_CmpA(pwmHandle, PWM_ShadowMode_Shadow);
	PWM_setShadowMode_CmpB(pwmHandle, PWM_ShadowMode_Shadow);
	PWM_setLoadMode_CmpA(pwmHandle, PWM_LoadMode_Zero);
	PWM_setLoadMode_CmpB(pwmHandle, PWM_LoadMode_Zero);

	PWM_setActionQual_Zero_PwmA(pwmHandle, PWM_ActionQual_Set);
	PWM_setActionQual_CntUp_CmpA_PwmA(pwmHandle, PWM_ActionQual_Clear);
	PWM_setActionQual_Zero_PwmB(pwmHandle, PWM_ActionQual_Set);
	PWM_setActionQual_CntUp_CmpB_PwmB(pwmHandle, PWM_ActionQual_Clear);

	PWM_setSyncMode(pwmHandle, PWM_SyncMode_EPWMxSYNC);
	PWM_setPhaseDir(pwmHandle, PWM_PhaseDir_CountUp);
	PWM_setRunMode(pwmHandle, PWM_RunMode_FreeRun);

	CLK_enableTbClockSync(obj->clkHandle);
}

void pwm_set_duty_cycle(double duty_cycle) {
	PWM_write_CmpA(pwmHandle, (uint16_t)(2000 * duty_cycle));
	PWM_write_CmpB(pwmHandle, (uint16_t)(2000 * duty_cycle));
}
