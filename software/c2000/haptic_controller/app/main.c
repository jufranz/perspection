#include "main_position.h"
#include "perspection_adc.h"
#include <math.h>

#ifdef FLASH
#pragma CODE_SECTION(mainISR, "ramfuncs");
#pragma CODE_SECTION(spiISR, "ramfuncs");
#endif

#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;
#endif

// Limits and defines

#define PWM_FREQUENCY 20000.0
#define PWM_PERIOD_MS (1000.0 / PWM_FREQUENCY)

#define POS_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define POS_DRIVER_CTL_PIN_NUM 3
#define NEG_DRIVER_CTL_PORT_NUM GPIO_B_NUM
#define NEG_DRIVER_CTL_PIN_NUM 4

#define TORQUE_MAX 1300.0 // Calibrated to the hardware
#define TORQUE_MIN 0.0
#define TORQUE_RANGE (TORQUE_MAX - TORQUE_MIN)

#define TORQUE_DIRECTION_POSITIVE 1
#define TORQUE_DIRECTION_NEGATIVE 0

#define DUTY_CYCLE_MAX_ADJUSTMENT 2.0
#define DUTY_CYCLE_FILTER_LENGTH 10

// Global state

HAL_Handle halHandle;
USER_Params gUserParams;

double haptics_duty_cycle;
double duty_cycle_filter[DUTY_CYCLE_FILTER_LENGTH];
uint16_t duty_cycle_filter_index;
bool isSystemEnabled;
uint16_t currentTorqueDir;
double lastPosition;

// Functions

void adjust_duty_cycle(double desired_torque);
void set_duty_cycle(double new_duty_cycle);
void init_duty_cycle_filter();
void add_duty_cycle_to_filter(double duty_cycle);
double get_duty_cycle_filter_value();

void processSpiMessages();
void startupControl(HAL_Handle halHandle, bool shouldBeRunning);
void hapticTorqueControl(HAL_Handle halHandle, uint16_t desiredTorque);

double get_current_torque();
uint16_t read_raw_torque();
double normalize_raw_torque(uint16_t raw_torque);

// Torque as a function of position
// Position is in degrees, torque should be -1.0 to 1.0

double torque_from_motion(double position, double velocity) {
    // Spring
    double offsetPosition = position - 180.0;
    double k = 120.0;   // Spring constant
    double c = 0.0003;  // Damping constant
    return (offsetPosition / -k) - (velocity * c);

    // Justn damping
//    return -(velocity * c);

// Wall
//    if(position > 45.0) {
//        return -0.5;
//    } else {
//        return 0;
//    }

//    return 0.0;
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
    // Only used if running from FLASH
    // Note that the variable FLASH is defined by the project
#ifdef FLASH
    // Copy time critical code and Flash setup code to RAM
    // The RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the linker files.
    memCopy((uint16_t *) &RamfuncsLoadStart, (uint16_t *) &RamfuncsLoadEnd, (uint16_t *) &RamfuncsRunStart);
#endif

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

    // disable the gimbal PWMs to get their interrupts
    HAL_disablePwm(halHandle);

    // enable SPI A slave and SPI interrupts
    HAL_enableSpiInt(halHandle);
    HAL_writeSpiSlaveData(halHandle, 30); // Just some junk for the TX buffer, probably don't need

    // ayyyydc
    perspection_adc_init(halHandle);

    // Start up a timer to calculate angular velocity
    HAL_startTimer(halHandle, 2);

    // reset shit
    haptics_duty_cycle = 0.0;
    isSystemEnabled = false;
    lastPosition = 0.0;

    for (;;) {
//        HAL_turnLedOn(halHandle, (GPIO_Number_e)HAL_Gpio_LED2);

        processSpiMessages();

        double position = (360.0 * (double)HAL_getQepPosnCounts(halHandle)) / (double) HAL_getQepPosnMaximum(halHandle);

        uint32_t timeDiff = 0xFFFFFFFF - HAL_readTimerCnt(halHandle, 2);
        HAL_reloadTimer(halHandle, 2);
        double velocity = (position - lastPosition) / ((double)timeDiff / ((double)gUserParams.systemFreq_MHz * 1000000.0));

        double desired_torque = torque_from_motion(position, velocity);
        if (desired_torque < -1.0) {
            desired_torque = -1.0;
        } else if (desired_torque > 1.0) {
            desired_torque = 1.0;
        }

        adjust_duty_cycle(desired_torque);
        lastPosition = position;

//        HAL_turnLedOff(halHandle, (GPIO_Number_e)HAL_Gpio_LED2);
    }
}

void processSpiMessages() {
    HAL_Obj *obj = (HAL_Obj *) halHandle;

    if (obj->hasNewStartupControlData) {
        startupControl(halHandle, obj->startupControlData);
        obj->hasNewStartupControlData = false;
    }
}

void startupControl(HAL_Handle halHandle, bool shouldBeRunning) {
    HAL_Obj *obj = (HAL_Obj *) halHandle;

    isSystemEnabled = shouldBeRunning;

    if (!shouldBeRunning) {
        // Reset stuff so we don't jump around acting on old data on the next startup
        obj->hasNewHapticTorqueControlData = false;
    }
}

// Helpful function definitions

void set_duty_cycle(double new_duty_cycle) {
    add_duty_cycle_to_filter(new_duty_cycle);
    haptics_duty_cycle = get_duty_cycle_filter_value();
    if (haptics_duty_cycle < -1.0) {
        haptics_duty_cycle = -1.0;
    } else if (haptics_duty_cycle > 1.0) {
        haptics_duty_cycle = 1.0;
    }

    if (haptics_duty_cycle < 0.0) {
        currentTorqueDir = TORQUE_DIRECTION_NEGATIVE;
        HAL_setAuxHbridgePwmDutyCycle(halHandle, -haptics_duty_cycle);
    } else if (haptics_duty_cycle > 0.0) {
        currentTorqueDir = TORQUE_DIRECTION_POSITIVE;
        HAL_setAuxHbridgePwmDutyCycle(halHandle, haptics_duty_cycle);
    } else {
        HAL_setAuxHbridgePwmDutyCycle(halHandle, 0.0);
    }

    HAL_setAuxHbridgeDirection(halHandle, currentTorqueDir);
}

void init_duty_cycle_filter() {
    duty_cycle_filter_index = 0;
    uint16_t i;
    for (i = 0; i < DUTY_CYCLE_FILTER_LENGTH; i++) {
        duty_cycle_filter[i] = 0.0;
    }
}

void add_duty_cycle_to_filter(double duty_cycle) {
    duty_cycle_filter[duty_cycle_filter_index] = duty_cycle;
    duty_cycle_filter_index++;
    if (duty_cycle_filter_index >= DUTY_CYCLE_FILTER_LENGTH) {
        duty_cycle_filter_index = 0;
    }
}

double get_duty_cycle_filter_value() {
    double duty_cycle_average = 0.0;
    uint16_t i;
    for (i = 0; i < DUTY_CYCLE_FILTER_LENGTH; i++) {
        duty_cycle_average += duty_cycle_filter[i];
    }
    return (duty_cycle_average / (double) DUTY_CYCLE_FILTER_LENGTH);
}

double get_current_torque() {
    uint16_t raw_torque = read_raw_torque();

    if (currentTorqueDir == TORQUE_DIRECTION_NEGATIVE) {
        return -normalize_raw_torque(raw_torque);
    } else {
        return normalize_raw_torque(raw_torque);
    }
}

uint16_t read_raw_torque() {
    return perspection_adc_read_aux_vpropi(halHandle);
}

double normalize_raw_torque(uint16_t raw_torque) {
    return (((double)raw_torque) / TORQUE_RANGE);
}

// TI bullshit

interrupt void mainISR(void) {

}

interrupt void qepISR(void) {

}
