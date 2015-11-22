// **************************************************************************
// the includes
#include "main_position.h"
#include "perspection_pwm.h"
#include "perspection_adc.h"

// **************************************************************************
// the globals

HAL_Handle halHandle;
USER_Params gUserParams;

// **************************************************************************
// the functions

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

	// get dis pwm rippin shit up yo
	perspection_pwm_1a_init(halHandle, 40.0);
	perspection_pwm_1b_init(halHandle, 40.0);

	// ayyyyydc
	perspection_adc_init(halHandle);

	for (;;) {
		uint32_t rawPosition = HAL_getQepPosnCounts(halHandle);
		double position = (double) (360 * rawPosition) / (double) HAL_getQepPosnMaximum(halHandle);

		if (position > 330.0 || position < 30.0) {
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			perspection_pwm_1a_set_duty_cycle(0.15);
		} else if (position > 270.0 || position < 90.0) {
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			perspection_pwm_1a_set_duty_cycle(0.35);
		} else if (position < 210.0 && position > 150.0) {
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			perspection_pwm_1a_set_duty_cycle(0.90);
		} else {
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
			perspection_pwm_1a_set_duty_cycle(0.60);
		}

		uint16_t adc_val = perspection_adc_read_vpropi1(halHandle);
		perspection_pwm_1b_set_duty_cycle((double)adc_val / (double)0xffff);
	}
}
