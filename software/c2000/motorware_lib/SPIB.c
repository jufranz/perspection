/*
 * SPIB.c
 *
 *  Created on: Nov 20, 2015
 *      Author: john
 */
#include "SPIB.h"
#include <math.h>
#include "drv8301.h"

SPIB_Handle SPIB_init(void *pMemory,const size_t numBytes)
{
  SPIB_Handle handle;


  if(numBytes < sizeof(SPIB_Obj))
    return((SPIB_Handle)NULL);


  // assign the handle
  handle = (SPIB_Handle)pMemory;

  SPIB_resetRxTimeout(handle);
  SPIB_resetEnableTimeout(handle);


  return(handle);
} // end of DRV8301_init() function

void SPIB_setGpioHandle(SPIB_Handle handle,GPIO_Handle gpioHandle)
{
  SPIB_Obj *obj = (SPIB_Obj *)handle;

  // initialize the gpio interface object
  obj->gpioHandle = gpioHandle;

  return;
} // end of DRV8301_setGpioHandle() function


void SPIB_setGpioNumber(SPIB_Handle handle,GPIO_Number_e gpioNumber)
{
 SPIB_Obj *obj = (SPIB_Obj *)handle;

  // initialize the gpio interface object
  obj->gpioNumber = gpioNumber;

  return;
} // end of DRV8301_setGpioNumber() function


void SPIB_setSpiHandle(SPIB_Handle handle,SPI_Handle spiHandle)
{
  SPIB_Obj *obj = (SPIB_Obj *)handle;

  // initialize the serial peripheral interface object
  obj->spiHandle = spiHandle;

  return;
} // end of DRV8301_setSpiHandle() function


uint16_t SPIB_readSpi(SPIB_Handle handle)
{
  SPIB_Obj *obj = (SPIB_Obj *)handle;
  uint16_t ctrlWord = 0;
//  const uint16_t data = 0;
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


void SPIB_writeSpi(SPIB_Handle handle, const uint16_t data)
{
  SPIB_Obj *obj = (SPIB_Obj *)handle;

  // reset the Rx fifo pointer to zero
  SPI_resetRxFifo(obj->spiHandle);
  SPI_enableRxFifo(obj->spiHandle);

  // write the command (time N)
  SPI_write(obj->spiHandle,data);


  return;
}


// end of file


