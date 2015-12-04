/*
 * Arduino.c
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */
#include "Arduino.h"
#include <math.h>
#include "sw/drivers/drvic/drv8301/src/32b/f28x/f2806x/drv8301.h"

Arduino_Handle Arduino_init(void *pMemory,const size_t numBytes)
{
  Arduino_Handle handle;


  if(numBytes < sizeof(Arduino_Obj))
    return((Arduino_Handle)NULL);


  // assign the handle
  handle = (Arduino_Handle)pMemory;

  Arduino_resetRxTimeout(handle);
  Arduino_resetEnableTimeout(handle);


  return(handle);
} // end of DRV8301_init() function

void Arduino_setGpioHandle(Arduino_Handle handle,GPIO_Handle gpioHandle)
{
  Arduino_Obj *obj = (Arduino_Obj *)handle;

  // initialize the gpio interface object
  obj->gpioHandle = gpioHandle;

  return;
} // end of DRV8301_setGpioHandle() function


void Arduino_setGpioNumber(Arduino_Handle handle,GPIO_Number_e gpioNumber)
{
 Arduino_Obj *obj = (Arduino_Obj *)handle;

  // initialize the gpio interface object
  obj->gpioNumber = gpioNumber;

  return;
} // end of DRV8301_setGpioNumber() function


void Arduino_setSpiHandle(Arduino_Handle handle,SPI_Handle spiHandle)
{
  Arduino_Obj *obj = (Arduino_Obj *)handle;

  // initialize the serial peripheral interface object
  obj->spiHandle = spiHandle;

  return;
} // end of DRV8301_setSpiHandle() function


uint16_t Arduino_readSpi(Arduino_Handle handle)
{
  Arduino_Obj *obj = (Arduino_Obj *)handle;
  uint16_t ctrlWord;
  const uint16_t data = 0;
  volatile uint16_t readWord;
  static volatile uint16_t WaitTimeOut = 0;
  volatile SPI_FifoStatus_e RxFifoCnt = SPI_FifoStatus_Empty;


  // reset the Rx fifo pointer to zero
  SPI_resetRxFifo(obj->spiHandle);
  SPI_enableRxFifo(obj->spiHandle);

/*NEED TO CHANGE IT FROM WRITING FIRST TO WAITING FOR THE MASTER TO COMMAND IT*/
  // write the command
  SPI_write(obj->spiHandle,ctrlWord);
  // dummy write to return the reply from the 8301
  SPI_write(obj->spiHandle,0x0000);

  // wait for two words to populate the RX fifo, or a wait timeout will occur
  while((RxFifoCnt < SPI_FifoStatus_2_Words) && (WaitTimeOut < 0xffff))
  {
    RxFifoCnt = SPI_getRxFifoStatus(obj->spiHandle);

      if(++WaitTimeOut > 0xfffe)
      {
          obj->RxTimeOut = true;
      }
  }
  /*NEED TO CHANGE IT FROM WRITING FIRST TO WAITING FOR THE MASTER TO COMMAND IT*/

  // Read two words, the dummy word and the data
  readWord = SPI_readEmu(obj->spiHandle); //not necessarily sure we need this
  readWord = SPI_readEmu(obj->spiHandle);

  return(readWord);
}


void Arduino_writeSpi(Arduino_Handle handle, const uint16_t data)
{
  Arduino_Obj *obj = (Arduino_Obj *)handle;

  // reset the Rx fifo pointer to zero
  SPI_resetRxFifo(obj->spiHandle);
  SPI_enableRxFifo(obj->spiHandle);

  // write the command (time N)
  SPI_write(obj->spiHandle,data);


  return;
}


// end of file


