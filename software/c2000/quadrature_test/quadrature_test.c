#include "main_position.h"
#include "perspection_pwm.h"
#include "perspection_adc.h"

// Limits and defines

#define PWM_FREQUENCY 20000.0
#define PWM_PERIOD_MS (1000.0 / PWM_FREQUENCY)

#define POS_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define POS_DRIVER_CTL_PIN_NUM 3
#define NEG_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define NEG_DRIVER_CTL_PIN_NUM 4

#define TORQUE_MAX 2508.0 // Calibrated to the hardware
#define TORQUE_MIN 1180.0
#define TORQUE_RANGE ((TORQUE_MAX - TORQUE_MIN) / 2.0)

#define TORQUE_DIRECTION_POSITIVE 0
#define TORQUE_DIRECTION_NEGATIVE 1

#define DUTY_CYCLE_MAX_ADJUSTMENT 2.0
#define DUTY_CYCLE_FILTER_LENGTH 10

// Global state

HAL_Handle halHandle;
USER_Params gUserParams;

double haptics_duty_cycle;
double duty_cycle_filter[DUTY_CYCLE_FILTER_LENGTH];
uint16_t duty_cycle_filter_index;
double torque_zero;

uint16_t rdata = 0;
uint16_t ints = 0;

// Functions

void adjust_duty_cycle(double desired_torque);
void set_duty_cycle(double new_duty_cycle);
void init_duty_cycle_filter();
void add_duty_cycle_to_filter(double duty_cycle);
double get_duty_cycle_filter_value();

void calibrate_zero_torque();
double get_current_torque();
uint16_t read_raw_torque();
double normalize_raw_torque(uint16_t raw_torque);

// Torque as a function of position
// Position is in degrees, torque should be -1.0 to 1.0

double torque_from_position(double position) {
    // Loose spring
	if(position > 0.0 && position < 180.0) {
		return (position / -180.0);
	} else {
		return ((position - 360.0) / -180.0);
	}

    // Wall
//    if(position > 45.0) {
//        return -0.5;
//    } else {
//        return 0;
//    }

//	return 0.0;
}

// The torque control loop

void adjust_duty_cycle(double desired_torque) {
    double current_torque = get_current_torque();

    double torque_delta = desired_torque - current_torque; // Between -2.0 and 2.0
    double normalized_torque_delta = torque_delta / 2.0; // Between -1.0 and 1.0
    double duty_cycle_adjustment = (DUTY_CYCLE_MAX_ADJUSTMENT * normalized_torque_delta);
    set_duty_cycle(haptics_duty_cycle + duty_cycle_adjustment);
}

// Real shit yo

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

	// yo these are important
	HAL_initIntVectorTable(halHandle);
	HAL_enableAdcInts(halHandle);

	// enable global interrupts
	HAL_enableGlobalInts(halHandle);

	// enable debug interrupts
	HAL_enableDebugInt(halHandle);

	// enable SPI A slave and SPI interrupts
//	HAL_setupSpiAslave(halHandle);
	HAL_enableSpiInt(halHandle);

	// get dis pwm rippin shit up yo
	perspection_pwm_1a_init(halHandle, 40.0);
	perspection_pwm_1b_init(halHandle, 40.0);
	init_duty_cycle_filter();

	// ayyyyydc
	perspection_adc_init(halHandle);

	// calibrate
	calibrate_zero_torque();

	// reset shit
	haptics_duty_cycle = 0.0;

	for (;;) {
//		HAL_turnLedOn(halHandle, (GPIO_Number_e)HAL_Gpio_LED2);

//		uint32_t rawPosition = HAL_getQepPosnCounts(halHandle);
//		double position = (double) (360 * rawPosition) / (double) HAL_getQepPosnMaximum(halHandle);
//
//		double desired_torque = torque_from_position(position);
//		if(desired_torque < -1.0) {
//			desired_torque = -1.0;
//		} else if(desired_torque > 1.0) {
//			desired_torque = 1.0;
//		}
//
//		adjust_duty_cycle(desired_torque);

//		HAL_turnLedOff(halHandle, (GPIO_Number_e)HAL_Gpio_LED2);
	}
}

// SPI A slave ISR

interrupt void spiISR(void)
{
  // toggle status LED
//  HAL_toggleLed(halHandle,(GPIO_Number_e)HAL_Gpio_LED2);
  rdata = HAL_readSPIAslaveData(halHandle);
  ints++;
  return;
}

// Helpful function definitions

void set_duty_cycle(double new_duty_cycle) {
	add_duty_cycle_to_filter(new_duty_cycle);
    haptics_duty_cycle = get_duty_cycle_filter_value();
    if(haptics_duty_cycle < -1.0) {
        haptics_duty_cycle = -1.0;
    } else if(haptics_duty_cycle > 1.0) {
        haptics_duty_cycle = 1.0;
    }

    if(haptics_duty_cycle < 0.0) {
    	perspection_pwm_1a_set_duty_cycle(0.0);
    	perspection_pwm_1b_set_duty_cycle(-haptics_duty_cycle);
    } else if(haptics_duty_cycle > 0.0) {
    	perspection_pwm_1a_set_duty_cycle(haptics_duty_cycle);
    	perspection_pwm_1b_set_duty_cycle(0.0);
    } else {
    	perspection_pwm_1a_set_duty_cycle(0.0);
    	perspection_pwm_1b_set_duty_cycle(0.0);
    }
}

void init_duty_cycle_filter() {
	duty_cycle_filter_index = 0;
	uint16_t i;
	for(i = 0; i < DUTY_CYCLE_FILTER_LENGTH; i++) {
		duty_cycle_filter[i] = 0.0;
	}
}

void add_duty_cycle_to_filter(double duty_cycle) {
	duty_cycle_filter[duty_cycle_filter_index] = duty_cycle;
	duty_cycle_filter_index++;
	if(duty_cycle_filter_index >= DUTY_CYCLE_FILTER_LENGTH) {
		duty_cycle_filter_index = 0;
	}
}

double get_duty_cycle_filter_value() {
	double duty_cycle_average = 0.0;
	uint16_t i;
	for(i = 0; i < DUTY_CYCLE_FILTER_LENGTH; i++) {
		duty_cycle_average += duty_cycle_filter[i];
	}
	return (duty_cycle_average / (double)DUTY_CYCLE_FILTER_LENGTH);
}

void calibrate_zero_torque() {
    uint16_t last_raw_torque = read_raw_torque();
    uint16_t this_raw_torque;

    while(1) {
    	// Wait 500ms
    	usDelay(500000);

        // See how much the torque has changed
        this_raw_torque = read_raw_torque();
        int16_t torque_change = (this_raw_torque - last_raw_torque);
        torque_change = (torque_change < 0) ? (torque_change * -1) : torque_change;

        // If it's changed less than +/- 4mV, we're calibrated
        if(torque_change < 5) {
            break;
        }

        // Else, try again
        last_raw_torque = this_raw_torque;
    }

    torque_zero = (double)this_raw_torque;
}

double get_current_torque() {
    uint16_t raw_torque = read_raw_torque();
    return normalize_raw_torque(raw_torque);
}

uint16_t read_raw_torque() {
    return perspection_adc_read_vpropi1(halHandle);
}

double normalize_raw_torque(uint16_t raw_torque) {
    return (((double)raw_torque - torque_zero) / TORQUE_RANGE);
}

// TI bullshit

interrupt void mainISR(void) {

}
