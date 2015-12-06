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
 *         Code for broadcasting headset IMU data
 * \author
 *         Jason Leung <jasleung@umich.edu>
 */

#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"

#include "clock.h"
#include "sys/clock.h"

#include "dev/bno055.h"
#include "dev/comms.h"
#include "dev/leds.h"

#include <stdio.h>

void delay(uint16_t msec){
  int i;
  for(i = 0; i < msec; i++){
    clock_delay_usec(1000);
  };
}

#define HEADSET_MAIN_DEBUG 1

/*---------------------------------------------------------------------------*/
PROCESS(init_wireless_process, "Start wireless comms");
PROCESS(init_imu_process, "Start IMU and initialization settings");
PROCESS(obtain_orientation_process, "Loop for obtaining orientation data");
AUTOSTART_PROCESSES(&init_wireless_process);
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
//no need for a receive function because this device does not need to listen
//for packets
static const struct broadcast_callbacks broadcast_call = {NULL};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
PROCESS_THREAD(init_wireless_process, ev, data){
  PROCESS_BEGIN();
  
  static linkaddr_t nodeAddr;
  nodeAddr.u8[0] = HEADSET_ADDR_A;
  nodeAddr.u8[1] = HEADSET_ADDR_B;
  linkaddr_set_node_addr(&nodeAddr);

  initGimbalNetwork(&broadcast, &broadcast_call);
  
  //once network initialized, start IMU initialization
  process_start(&init_imu_process, NULL);

  PROCESS_END();
}



PROCESS_THREAD(init_imu_process, ev, data) {
  PROCESS_BEGIN();
  leds_off(LEDS_RED);

  delay(500);

  if(!bno055_init()){
    leds_on(LEDS_RED);
  }
  
  bno055_set_mode(BNO055_OPERATION_MODE_NDOF_FMC_OFF);

  //once everything is set up, start IMU process
  //or start IMU calibration check process
  //or start both simultaneously
  process_start(&obtain_orientation_process, NULL);

  PROCESS_END();
}



PROCESS_THREAD(obtain_orientation_process, ev, data) {
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
  static struct etimer et;

  PROCESS_BEGIN();

  static struct gimbalData_t headData;

  while(1) {
    etimer_set(&et, CLOCK_SECOND/100);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
   
    leds_on(LEDS_GREEN);
    
    bno055_vector_t euler_data = bno055_get_vector(BNO055_EULER_VECTOR);
    
    headData.gYaw = scaleForEncoder(euler_data.z);
    #if BOARD_MOUNTED_ON_HEADSET_NORMALLY
    headData.gPitch = scaleForEncoder(euler_data.x);
    #else
    headData.gPitch = scaleForEncoder(euler_data.y);
    #endif

    #if HEADSET_MAIN_DEBUG
    printf("Yaw: %d, Pitch: %d, xD: %d, yD: %d, zD: %d, x: %d, y: %d, z: %d\n", 
          headData.gYaw, headData.gPitch, 
          euler_data.x/16, euler_data.y/16, euler_data.z/16, 
          euler_data.x, euler_data.y, euler_data.z);
    #endif

    broadcastGimbalData(&headData, &broadcast);
    
    leds_off(LEDS_GREEN);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
