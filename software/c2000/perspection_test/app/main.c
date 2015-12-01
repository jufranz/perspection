// system includes
#include <math.h>
#include "main.h"

#ifdef FLASH
#pragma CODE_SECTION(mainISR, "ramfuncs");
#endif

// Include header files used in the main function

// **************************************************************************
// the defines

#define LED_BLINK_FREQ_Hz   5

// **************************************************************************
// the globals

uint_least16_t gCounter_updateGlobals = 0;

bool Flag_Latch_softwareUpdate = true;

CTRL_Handle ctrlHandle;

#ifdef F2802xF
#pragma DATA_SECTION(halHandle, "rom_accessed_data");
#endif
HAL_Handle halHandle;

#ifdef F2802xF
#pragma DATA_SECTION(gUserParams, "rom_accessed_data");
#endif
USER_Params gUserParams;

HAL_PwmData_t gPwmData = { _IQ(0.0), _IQ(0.0), _IQ(0.0) };

HAL_AdcData_t gAdcData;

_iq gMaxCurrentSlope = _IQ(0.0);

#ifdef FAST_ROM_V1p6
CTRL_Obj *controller_obj;
#else
#ifdef F2802xF
#pragma DATA_SECTION(ctrl, "rom_accessed_data");
#endif
CTRL_Obj ctrl;				//v1p7 format
#endif

uint16_t gLEDcnt = 0;

volatile MOTOR_Vars_t gMotorVars = MOTOR_Vars_INIT;

#ifdef FLASH
// Used for running BackGround in flash, and ISR in RAM
        extern uint16_t *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;

#ifdef F2802xF
        extern uint16_t *econst_start, *econst_end, *econst_ram_load;
        extern uint16_t *switch_start, *switch_end, *switch_ram_load;
#endif

#endif

#ifdef DRV8301_SPI
// Watch window interface to the 8301 SPI
DRV_SPI_8301_Vars_t gDrvSpi8301Vars;
#endif

#ifdef DRV8305_SPI
// Watch window interface to the 8305 SPI
DRV_SPI_8305_Vars_t gDrvSpi8305Vars;
#endif

// **************************************************************************
// the functions
uint16_t rdata = 0;
uint16_t sdata = 0;
unsigned int ints = 0;

void main(void) {
    uint_least8_t estNumber = 0;

#ifdef FAST_ROM_V1p6
    uint_least8_t ctrlNumber = 0;
#endif

    // Only used if running from FLASH
    // Note that the variable FLASH is defined by the project
#ifdef FLASH
    // Copy time critical code and Flash setup code to RAM
    // The RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
    // symbols are created by the linker. Refer to the linker files.
    memCopy((uint16_t *)&RamfuncsLoadStart,(uint16_t *)&RamfuncsLoadEnd,(uint16_t *)&RamfuncsRunStart);

#ifdef F2802xF
    //copy .econst to unsecure RAM
    if(*econst_end - *econst_start)
    {
        memCopy((uint16_t *)&econst_start,(uint16_t *)&econst_end,(uint16_t *)&econst_ram_load);
    }

    //copy .switch ot unsecure RAM
    if(*switch_end - *switch_start)
    {
        memCopy((uint16_t *)&switch_start,(uint16_t *)&switch_end,(uint16_t *)&switch_ram_load);
    }
#endif

#endif

    // initialize the hardware abstraction layer
    halHandle = HAL_init(&hal, sizeof(hal));

    // check for errors in user parameters
    USER_checkForErrors(&gUserParams);

    // store user parameter error in global variable
    gMotorVars.UserErrorCode = USER_getErrorCode(&gUserParams);

    // do not allow code execution if there is a user parameter error
    if (gMotorVars.UserErrorCode != USER_ErrorCode_NoError) {
        for (;;) {
            gMotorVars.Flag_enableSys = false;
        }
    }

    // initialize the user parameters
    USER_setParams(&gUserParams);

    // set the hardware abstraction layer parameters
    HAL_setParams(halHandle, &gUserParams);

    // initialize the controller
#ifdef FAST_ROM_V1p6
    ctrlHandle = CTRL_initCtrl(ctrlNumber, estNumber);  		//v1p6 format (06xF and 06xM devices)
    controller_obj = (CTRL_Obj *) ctrlHandle;
#else
    ctrlHandle = CTRL_initCtrl(estNumber,&ctrl,sizeof(ctrl));	//v1p7 format default
#endif

    {
        CTRL_Version version;

        // get the version number
        CTRL_getVersion(ctrlHandle, &version);

        gMotorVars.CtrlVersion = version;
    }

    // set the default controller parameters
    CTRL_setParams(ctrlHandle, &gUserParams);

    // setup faults
    HAL_setupFaults(halHandle);

    // initialize the interrupt vector table
    HAL_initIntVectorTable(halHandle);

    // enable the ADC interrupts
    HAL_enableAdcInts(halHandle);

    // enable the SPI interrupts
    HAL_enableSpiInt(halHandle);

    // enable global interrupts
    HAL_enableGlobalInts(halHandle);

    // enable debug interrupts
    HAL_enableDebugInt(halHandle);

    // disable the PWM
    HAL_disablePwm(halHandle);

#ifdef DRV8301_SPI
    // turn on the DRV8301 if present
    HAL_enableDrv(halHandle);
    // initialize the DRV8301 interface
    HAL_setupDrvSpi(halHandle, &gDrvSpi8301Vars);
#endif

    // enable DC bus compensation
//    CTRL_setFlag_enableDcBusComp(ctrlHandle, true);
    sdata = 0;
    rdata = 0;
    for (;;) {
        //sdata = HAL_spiIntStatus(halHandle);
        //if(sdata != 0)
        //sdata = 100;
        //HAL_writeSPIB(halHandle, sdata);
        //rdata = HAL_readArduinoData(halHandle);
    } // end of for(;;) loop

} // end of main() function

interrupt void mainISR(void) {

} // end of mainISR() function

interrupt void spiISR(void) {
    rdata = HAL_readSpiSlaveData(halHandle);
    ints++;
    return;
}

//@} //defgroup
// end of file

