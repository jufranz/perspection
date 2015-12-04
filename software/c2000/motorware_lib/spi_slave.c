/*
 * spi_slave.c
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */

#include <math.h>
#include "spi_slave.h"

SPI_Slave_Handle SPI_Slave_init(void *pMemory, const size_t numBytes) {
    SPI_Slave_Handle handle;

    if (numBytes < sizeof(SPI_Slave_Obj))
        return ((SPI_Slave_Handle) NULL);

    // assign the handle
    handle = (SPI_Slave_Handle) pMemory;

    SPI_Slave_resetRxTimeout(handle);
    SPI_Slave_resetEnableTimeout(handle);

    return (handle);
} // end of SPI_Slave_init() function

void SPI_Slave_setGpioHandle(SPI_Slave_Handle handle, GPIO_Handle gpioHandle) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    // initialize the gpio interface object
    obj->gpioHandle = gpioHandle;

    return;
} // end of SPI_Slave_setGpioHandle() function

void SPI_Slave_setGpioNumber(SPI_Slave_Handle handle, GPIO_Number_e gpioNumber) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    // initialize the gpio interface object
    obj->gpioNumber = gpioNumber;

    return;
} // end of SPI_Slave_setGpioNumber() function

void SPI_Slave_setSpiHandle(SPI_Slave_Handle handle, SPI_Handle spiHandle) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    // initialize the serial peripheral interface object
    obj->spiHandle = spiHandle;

    return;
} // end of SPI_Slave_setSpiHandle() function

uint16_t SPI_Slave_readSpi(SPI_Slave_Handle handle, uint16_t* buf) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;
    uint16_t wordsRead = 0;

    while(SPI_getRxFifoStatus(obj->spiHandle) != SPI_FifoStatus_Empty) {
        buf[wordsRead] = SPI_read(obj->spiHandle);
        wordsRead++;
    }

    // reset the Rx fifo pointer to zero NOT SURE IF I NEED THIS
    SPI_clearRxFifoInt(obj->spiHandle);
    SPI_resetRxFifo(obj->spiHandle);
    SPI_enableRxFifo(obj->spiHandle);
    SPI_enableInt(obj->spiHandle);

    return wordsRead;
} // end of SPI_Slave_readSpi() function

void SPI_Slave_writeSpi(SPI_Slave_Handle handle, const uint16_t data) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    // reset the Rx fifo pointer to zero
//    SPI_resetRxFifo(obj->spiHandle);
//    SPI_enableRxFifo(obj->spiHandle);

    // write the command (time N)
    SPI_write(obj->spiHandle, data);

    return;
} // end of SPI_Slave_writeSpi() function


void SPI_Slave_clearTxFifo(SPI_Slave_Handle handle) {
    SPI_Slave_Obj *obj = (SPI_Slave_Obj *) handle;

    SPI_resetTxFifo(obj->spiHandle);
} // end of SPI_Slave_clearTxFifo() function

// end of file

