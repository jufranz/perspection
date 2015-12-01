/*
 * spi_slave.h
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */

#ifndef SPI_SLAVE_H_
#define SPI_SLAVE_H_

//! \file   drivers/drvic/SPI_Slave/src/32b/f28x/f2806x/SPI_Slave.h
//! \brief  Contains public interface to various functions related
//!         to the SPI_Slave object
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

//! \brief Defines the SPI_Slave object
//!
typedef struct _SPI_Slave_Obj_ {
    SPI_Handle spiHandle;            //!< the handle for the serial peripheral interface
    GPIO_Handle gpioHandle;          //!< the gpio handle that is connected to the SPI_Slave enable pin
    GPIO_Number_e gpioNumber;        //!< the gpio number that is connected to the SPI_Slave enable pin
    bool RxTimeOut;                  //!< the timeout flag for the RX fifo
    bool enableTimeOut;              //!< the timeout flag for SPI_Slave enable
} SPI_Slave_Obj;

//! \brief Defines the SPI_Slave handle
//!
typedef struct _SPI_Slave_Obj_ *SPI_Slave_Handle;

// the function prototype
//! \brief     Initializes the DRV8301 object
//! \param[in] pMemory   A pointer to the memory for the DRV8301 object
//! \param[in] numBytes  The number of bytes allocated for the DRV8301 object, bytes
//! \return    The DRV8301 object handle
extern SPI_Slave_Handle SPI_Slave_init(void *pMemory, const size_t numBytes);

//! \brief     Resets the enable timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void SPI_Slave_resetEnableTimeout(SPI_Slave_Handle handle) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    obj->enableTimeOut = false;

    return;
}

//! \brief     Resets the RX fifo timeout flag
//! \param[in] handle   The DRV8301 handle
static inline void SPI_Slave_resetRxTimeout(SPI_Slave_Handle handle) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    obj->RxTimeOut = false;

    return;
}

//! \brief     Reads data from the SPI_Slave register
//! \param[in] handle   The SPI_Slave handle
//! \param[in] regName  The register name
//! \return    The data value
extern uint16_t SPI_Slave_readSpi(SPI_Slave_Handle handle);

//! \brief     Sets the GPIO handle in the SPI_Slave
//! \param[in] handle     The SPI_Slave handle
//! \param[in] gpioHandle The GPIO handle to use
void SPI_Slave_setGpioHandle(SPI_Slave_Handle handle, GPIO_Handle gpioHandle);

//! \brief     Sets the GPIO number in the SPI_Slave
//! \param[in] handle     The SPI_Slave handle
//! \param[in] gpioHandle The GPIO number to use
void SPI_Slave_setGpioNumber(SPI_Slave_Handle handle, GPIO_Number_e gpioNumber);

//! \brief     Sets the SPI handle in the SPI_Slave
//! \param[in] handle     The SPI_Slave handle
//! \param[in] spiHandle  The SPI handle to use
void SPI_Slave_setSpiHandle(SPI_Slave_Handle handle, SPI_Handle spiHandle);

//! \brief     Writes data to the SPI_Slave register
//! \param[in] handle   The SPI_Slave handle
//! \param[in] regName  The register name
//! \param[in] data     The data value
extern void SPI_Slave_writeSpi(SPI_Slave_Handle handle, const uint16_t data);

//@}  // ingroup

#endif /* SPI_SLAVE_H_ */
