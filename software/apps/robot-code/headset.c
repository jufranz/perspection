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
#include "dev/bno055.h"
#include "sys/clock.h"

#include "dev/comms.h"

#include "dev/leds.h"

#include <stdio.h>

void delay(uint16_t msec){
  int i;
  for(i = 0; i < msec; i++){
    clock_delay_usec(1000);
  };
}

/*---------------------------------------------------------------------------*/
PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  return;
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  delay(500);

  if(!bno055_init()){
    leds_on(LEDS_RED);
  }

  bno055_set_mode(BNO055_OPERATION_MODE_NDOF_FMC_OFF);
  delay(1);
  bno055_set_axis_map_config(BNO055_ZAXIS, BNO055_YAXIS, BNO055_XAXIS);
  delay(1);
  bno055_set_axis_map_sign(BNO055_POSITIVE, BNO055_POSITIVE, BNO055_NEGATIVE);
  static struct moveData_t testData;

  static linkaddr_t nodeAddr;
  nodeAddr.u8[0] = CTRL_ADDR_A;//HEADSET_ADDR_A;
  nodeAddr.u8[1] = CTRL_ADDR_B;//HEADSET_ADDR_B;
  linkaddr_set_node_addr(&nodeAddr);

  initMoveNetwork(&broadcast, &broadcast_call);
  //initGimbalNetwork(&broadcast, &broadcast_call);

  while(1) {

    /* Delay 1 second */
    etimer_set(&et, CLOCK_SECOND/75);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
   
    leds_on(LEDS_GREEN);
    bno055_vector_t euler_data = bno055_get_vector(BNO055_EULER_VECTOR);
    //testData.rAngle = euler_data.y/16;
    //testData.rAngle = (uint16_t)(((double)(((int16_t)euler_data.y/16)+180)*511.0)/360.0);
    testData.rAngle = (uint16_t)(((double)(euler_data.z/16)*511.0)/360.0);
    printf("sent: %d , x(pitch): %d, y(roll): %d, z(yaw): %d\n", testData.rAngle & 0x1FF, euler_data.x/16, euler_data.y/16, euler_data.z/16);
    broadcastMoveData(&testData, &broadcast);
    //broadcastGimbalData(&broadcast);
    leds_off(LEDS_GREEN);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
