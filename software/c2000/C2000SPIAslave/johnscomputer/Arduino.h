/*
 * Arduino.h
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

//! \file   drivers/drvic/Arduino/src/32b/f28x/f2806x/Arduino.h
//! \brief  Contains public interface to various functions related
//!         to the Arduino object
//!
//! (C) Copyright 2015, Texas Instruments, Inc.


// **************************************************************************
// the includes

// drivers
#include "sw/drivers/spi/src/32b/f28x/f2806x/spi.h"
#include "sw/drivers/gpio/src/32b/f28x/f2806x/gpio.h"


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the typedefs

//! \brief Defines the Arduino object
//!
typedef struct _Arduino_Obj_
{
  SPI_Handle       spiHandle;                  //!< the handle for the serial peripheral interface
  GPIO_Handle      gpioHandle;                 //!< the gpio handle that is connected to the Arduino enable pin
  GPIO_Number_e    gpioNumber;                 //!< the gpio number that is connected to the Arduino enable pin
  bool             RxTimeOut;                  //!< the timeout flag for the RX fifo
  bool             enableTimeOut;              //!< the timeout flag for Arduino enable
} Arduino_Obj;

#define SPDPOS 0x04
#define MOTORS 0x02
#define CUTTER 0x03
#define ENCODER 0x05

typedef struct _Perspection_Struct_
{
	//gimbal controls
	//Bits 0-15 are Speed command
	//Bits 16-31 are position command
	//command value is 0x04
	uint32_t SpdPos;

	//robot data (for haptics)
	//command value is 0x05
	uint32_t encoder; //this is just temp

	//controller data (for robot)
	//Bits 0-7 are speed,
	//bits 8-15 are PWMA
	//bits 16-23 are PWMB
	//bits 24-31 are PWMC
	//command value is 0x02
	uint32_t Motors;
	//command value is 0x03
	uint16_t cutter;

	uint16_t SPI_INPUT[16];

	//this variable 0 when SPI is not currently using the data in this struct
	//this is 1 when spi is using it
	uint16_t in_use;

} Perspection_Struct;


//! \brief Defines the Arduino handle
//!
typedef struct _Arduino_Obj_ *Arduino_Handle;


// the function prototype
//! \brief     Initializes the DRV8301 object
//! \param[in] pMemory   A pointer to the memory for the DRV8301 object
//! \param[in] numBytes  The number of bytes allocated for the DRV8301 object, bytes
//! \return    The DRV8301 object handle
extern Arduino_Handle Arduino_init(void *pMemory,const size_t numBytes);

//! \brief     Resets the enable timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void Arduino_resetEnableTimeout(Arduino_Handle handle)
{
  Arduino_Obj *obj = (Arduino_Obj *)handle;

  obj->enableTimeOut = false;

  return;
}


//! \brief     Resets the RX fifo timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void Arduino_resetRxTimeout(Arduino_Handle handle)
{
  Arduino_Obj *obj = (Arduino_Obj *)handle;

  obj->RxTimeOut = false;

  return;
}



//! \brief     Reads data from the Arduino register
//! \param[in] handle   The Arduino handle
//! \param[in] regName  The register name
//! \return    The data value
extern uint16_t Arduino_readSpi(Arduino_Handle handle);

//! \brief     Sets the GPIO handle in the Arduino
//! \param[in] handle     The Arduino handle
//! \param[in] gpioHandle  The GPIO handle to use
void Arduino_setGpioHandle(Arduino_Handle handle,GPIO_Handle gpioHandle);


//! \brief     Sets the GPIO number in the Arduino
//! \param[in] handle     The Arduino handle
//! \param[in] gpioHandle  The GPIO number to use
void Arduino_setGpioNumber(Arduino_Handle handle,GPIO_Number_e gpioNumber);


//! \brief     Sets the SPI handle in the Arduino
//! \param[in] handle     The Arduino handle
//! \param[in] spiHandle  The SPI handle to use
void Arduino_setSpiHandle(Arduino_Handle handle,SPI_Handle spiHandle);


//! \brief     Writes data to the Arduino register
//! \param[in] handle   The Arduino handle
//! \param[in] regName  The register name
//! \param[in] data     The data value
extern void Arduino_writeSpi(Arduino_Handle handle,const uint16_t data);

//@}  // ingroup


#endif /* ARDUINO_H_ */
