/*
 * Copyright (c) 2007, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 */

/**
 * \file
 *         Testing the broadcast layer in Rime
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"
#include "clock.h"
#include <math.h>
#include "dev/adc.h"
#include "dev/comms.h"
#include "dev/gpio.h"
#include "adc.h"

#include "dev/leds.h"

#include <stdio.h>

#define ADC_PIN_NUM 3
#define ADC_PORT_NUM GPIO_A_NUM
// GREEN WIRE
#define ADC_CHANNEL_Y SOC_ADC_ADCCON_CH_AIN3
// BLUE WIRE
#define ADC_CHANNEL_X SOC_ADC_ADCCON_CH_AIN4
// YELLOW WIRE
#define ADC_CHANNEL_POS SOC_ADC_ADCCON_CH_AIN5

/*---------------------------------------------------------------------------*/
PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  /*leds_on(LEDS_RED);
  printf("broadcast message received from %d.%d: '%s'\n",
         from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
  leds_off(LEDS_RED);*/
  return;
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/


static int16_t isCloseToCenter(int16_t i){
  if(i > -150 && i < 150) return 0;
  else return i;
}


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  //initializing ADC
  adc_init();

  linkaddr_t nodeAddr;
  nodeAddr.u8[0] = CTRL_ADDR_A;
  nodeAddr.u8[1] = CTRL_ADDR_B;
  linkaddr_set_node_addr(&nodeAddr);

  initMoveNetwork(&broadcast, &broadcast_call);

  static struct moveData_t testData;
  testData.tDir = 0;
  testData.tSpeed = 100;
  testData.rAngle = 0;
  testData.rSpeed = 0;
  testData.sDir = 1;
  testData.sSpeed = 125;

  static int16_t ctrlX;
  static int16_t ctrlY;
  static int16_t pos;

  while(1) {

    /* Delay 1 second */
    etimer_set(&et, CLOCK_SECOND/200);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    //it says AVDD5 but actually use 3V3 input.
    //32300 - 80, midpoint 17142
    ctrlX = isCloseToCenter(adc_get(ADC_CHANNEL_X, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512) - 17142);
    //32764 - 800, midpoint 16872
    ctrlY = isCloseToCenter(adc_get(ADC_CHANNEL_Y, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512) - 16832);
    pos = adc_get(ADC_CHANNEL_POS, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512);

    //printf("X: %d, Y: %d ", ctrlX, ctrlY);

    if(ctrlX == 0 && ctrlY == 0) {
      //all 9 bits are 1's. indicates no direction
      testData.tDir = 511;
      testData.tSpeed = 0;
    }
    else {
      testData.tDir = (uint16_t)((atan2((double)ctrlY, (double)ctrlX) * 180 / M_PI) + 180) % 360;
      testData.tSpeed = (uint8_t)((uint32_t)sqrt(pow((double)ctrlY, 2) + pow((double)ctrlX, 2))/(uint32_t)133);
      if(testData.tSpeed > 127) testData.tSpeed = 127;
    }

    if(pos < 0) pos = 0;
    testData.rAngle = (uint16_t)((((int32_t)pos) * 0x1FF) / 0x7FFF);

    printf("degrees: %d, speed: %d pos: %d\r\n", testData.tDir, testData.tSpeed, testData.rAngle);

    leds_on(LEDS_BLUE);
    broadcastMoveData(&testData, &broadcast);
    leds_off(LEDS_BLUE);

    unpackMoveData(&testData);
    printf("degrees: %d, speed: %d pos: %d\r\n", testData.tDir, testData.tSpeed, testData.rAngle);
    printf("\r\n");
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
