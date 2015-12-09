/*
 * SPIB.h
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */

#ifndef SPIB_H_
#define SPIB_H_

//! \file   drivers/drvic/SPIB/src/32b/f28x/f2806x/SPIB.h
//! \brief  Contains public interface to various functions related
//!         to the SPIB object
//!
//! (C) Copyright 2015, Texas Instruments, Inc.


// **************************************************************************
// the includes

// drivers
#include "spi.h"
#include "gpio.h"


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the typedefs

//! \brief Defines the SPIB object
//!
typedef struct _SPIB_Obj_
{
  SPI_Handle       spiHandle;                  //!< the handle for the serial peripheral interface
  GPIO_Handle      gpioHandle;                 //!< the gpio handle that is connected to the SPIB enable pin
  GPIO_Number_e    gpioNumber;                 //!< the gpio number that is connected to the SPIB enable pin
  bool             RxTimeOut;                  //!< the timeout flag for the RX fifo
  bool             enableTimeOut;              //!< the timeout flag for SPIB enable
} SPIB_Obj;


//! \brief Defines the SPIB handle
//!
typedef struct _SPIB_Obj_ *SPIB_Handle;


// the function prototype
//! \brief     Initializes the DRV8301 object
//! \param[in] pMemory   A pointer to the memory for the DRV8301 object
//! \param[in] numBytes  The number of bytes allocated for the DRV8301 object, bytes
//! \return    The DRV8301 object handle
extern SPIB_Handle SPIB_init(void *pMemory,const size_t numBytes);

//! \brief     Resets the enable timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void SPIB_resetEnableTimeout(SPIB_Handle handle)
{
  SPIB_Obj *obj = (SPIB_Obj *)handle;

  obj->enableTimeOut = false;

  return;
}


//! \brief     Resets the RX fifo timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void SPIB_resetRxTimeout(SPIB_Handle handle)
{
  SPIB_Obj *obj = (SPIB_Obj *)handle;

  obj->RxTimeOut = false;

  return;
}



//! \brief     Reads data from the SPIB register
//! \param[in] handle   The SPIB handle
//! \param[in] regName  The register name
//! \return    The data value
extern uint16_t SPIB_readSpi(SPIB_Handle handle);

//! \brief     Sets the GPIO handle in the SPIB
//! \param[in] handle     The SPIB handle
//! \param[in] gpioHandle  The GPIO handle to use
void SPIB_setGpioHandle(SPIB_Handle handle,GPIO_Handle gpioHandle);


//! \brief     Sets the GPIO number in the SPIB
//! \param[in] handle     The SPIB handle
//! \param[in] gpioHandle  The GPIO number to use
void SPIB_setGpioNumber(SPIB_Handle handle,GPIO_Number_e gpioNumber);


//! \brief     Sets the SPI handle in the SPIB
//! \param[in] handle     The SPIB handle
//! \param[in] spiHandle  The SPI handle to use
void SPIB_setSpiHandle(SPIB_Handle handle,SPI_Handle spiHandle);


//! \brief     Writes data to the SPIB register
//! \param[in] handle   The SPIB handle
//! \param[in] regName  The register name
//! \param[in] data     The data value
void SPIB_writeSpi(SPIB_Handle handle,const uint16_t data);

//@}  // ingroup


#endif /* SPIB_H_ */
