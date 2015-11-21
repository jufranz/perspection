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

	// disable the PWM
	HAL_disablePwm(halHandle);

	for (;;) {
		uint32_t rawPosition = HAL_getQepPosnCounts(halHandle);
		double position = (double) (360 * rawPosition) / (double) HAL_getQepPosnMaximum(halHandle);

		if (position > 330.0 || position < 30.0) {
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
		} else if (position > 270.0 || position < 90.0) {
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
		} else if (position < 210.0 && position > 150.0) {
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOff(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
		} else {
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED2);
			HAL_turnLedOn(halHandle, (GPIO_Number_e) HAL_Gpio_LED3);
		}
	}
}
