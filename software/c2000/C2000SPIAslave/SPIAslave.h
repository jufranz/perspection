/*
 * SPIAslave.h
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */

#ifndef SPIAslave_H_
#define SPIAslave_H_

//! \file   drivers/drvic/SPIAslave/src/32b/f28x/f2806x/SPIAslave.h
//! \brief  Contains public interface to various functions related
//!         to the SPIAslave object
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

//! \brief Defines the SPIAslave object
//!
typedef struct _SPIAslave_Obj_
{
  SPI_Handle       spiHandle;                  //!< the handle for the serial peripheral interface
  GPIO_Handle      gpioHandle;                 //!< the gpio handle that is connected to the SPIAslave enable pin
  GPIO_Number_e    gpioNumber;                 //!< the gpio number that is connected to the SPIAslave enable pin
  bool             RxTimeOut;                  //!< the timeout flag for the RX fifo
  bool             enableTimeOut;              //!< the timeout flag for SPIAslave enable
} SPIAslave_Obj;


//! \brief Defines the SPIAslave handle
//!
typedef struct _SPIAslave_Obj_ *SPIAslave_Handle;


// the function prototype
//! \brief     Initializes the DRV8301 object
//! \param[in] pMemory   A pointer to the memory for the DRV8301 object
//! \param[in] numBytes  The number of bytes allocated for the DRV8301 object, bytes
//! \return    The DRV8301 object handle
extern SPIAslave_Handle SPIAslave_init(void *pMemory,const size_t numBytes);

//! \brief     Resets the enable timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void SPIAslave_resetEnableTimeout(SPIAslave_Handle handle)
{
  SPIAslave_Obj *obj = (SPIAslave_Obj *)handle;

  obj->enableTimeOut = false;

  return;
}


//! \brief     Resets the RX fifo timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void SPIAslave_resetRxTimeout(SPIAslave_Handle handle)
{
  SPIAslave_Obj *obj = (SPIAslave_Obj *)handle;

  obj->RxTimeOut = false;

  return;
}



//! \brief     Reads data from the SPIAslave register
//! \param[in] handle   The SPIAslave handle
//! \param[in] regName  The register name
//! \return    The data value
extern uint16_t SPIAslave_readSpi(SPIAslave_Handle handle);

//! \brief     Sets the GPIO handle in the SPIAslave
//! \param[in] handle     The SPIAslave handle
//! \param[in] gpioHandle  The GPIO handle to use
void SPIAslave_setGpioHandle(SPIAslave_Handle handle,GPIO_Handle gpioHandle);


//! \brief     Sets the GPIO number in the SPIAslave
//! \param[in] handle     The SPIAslave handle
//! \param[in] gpioHandle  The GPIO number to use
void SPIAslave_setGpioNumber(SPIAslave_Handle handle,GPIO_Number_e gpioNumber);


//! \brief     Sets the SPI handle in the SPIAslave
//! \param[in] handle     The SPIAslave handle
//! \param[in] spiHandle  The SPI handle to use
void SPIAslave_setSpiHandle(SPIAslave_Handle handle,SPI_Handle spiHandle);


//! \brief     Writes data to the SPIAslave register
//! \param[in] handle   The SPIAslave handle
//! \param[in] regName  The register name
//! \param[in] data     The data value
extern void SPIAslave_writeSpi(SPIAslave_Handle handle,const uint16_t data);

//@}  // ingroup


#endif /* SPIAslave_H_ */
