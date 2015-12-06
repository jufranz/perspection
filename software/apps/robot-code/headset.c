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
#include "dev/clock_wrapper.h"

#include <stdio.h>

#define HEADSET_MAIN_DEBUG 0
#define WAIT_FOR_IMU_POWERED 0
#define SEPARATE_CALIBRATION_STEP 1

void blink_for(uint8_t led, uint8_t j, uint16_t len){
  uint8_t i;
  for(i = 0; i < j; i++){
    leds_on(led);
    clock_wrapper_delay_msec(len);
    leds_off(led);
    clock_wrapper_delay_msec(len);
  }
}

/*---------------------------------------------------------------------------*/
PROCESS(init_wireless_process, "Start wireless comms");
PROCESS(init_imu_process, "Start IMU and initialization settings");
PROCESS(calibrate_imu_process, "Calibrate sensors before running");
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

  blink_for(LEDS_BLUE, 3, 100);
  
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
  leds_off(LEDS_ALL);

  #if WAIT_FOR_IMU_POWERED
  //turn on this flag if experiencing issues initialising imu...
  clock_wrapper_delay_msec(500);
  #endif

  if(!bno055_init()){
    while(1){
      #if HEADSET_MAIN_DEBUG
      printf("failure to initialize. restart device.\n");
      #endif
      
      blink_for(LEDS_RED, 1, 100);
    }
  }else{
    //if shit is gucci, we turn on our desired IMU settings
    //and run our main processes

    bno055_set_mode(BNO055_OPERATION_MODE_NDOF_FMC_OFF);

    //once everything is set up, start IMU process
    //or start IMU calibration check process
    //or start both simultaneously
    #if SEPARATE_CALIBRATION_STEP
    process_start(&calibrate_imu_process, NULL);
    #else
    process_start(&obtain_orientation_process, NULL);
    #endif
  }

  PROCESS_END();
}



PROCESS_THREAD(calibrate_imu_process, ev, data) {
  PROCESS_BEGIN();

  leds_off(LEDS_ALL);

  while(1) { 
    bno055_vector_t euler_data = bno055_get_vector(BNO055_EULER_VECTOR);
    
    #if HEADSET_MAIN_DEBUG
    printf("x: %d\ty: %d\tz: %d\n", euler_data.x/16, euler_data.y/16, euler_data.z/16);
    #endif
    
    bno055_calibration_t cal = bno055_get_calibration();
    if(cal.gyro_cal) leds_on(LEDS_RED);
    if(cal.accel_cal) leds_on(LEDS_GREEN);
    if(cal.mag_cal) leds_on(LEDS_BLUE);

    if(cal.gyro_cal && cal.accel_cal && cal.mag_cal) break;
    clock_wrapper_delay_msec(10);
  }
  
  blink_for(LEDS_ALL, 8, 60);

  process_start(&obtain_orientation_process, NULL);
  
  PROCESS_END();
}



PROCESS_THREAD(obtain_orientation_process, ev, data) {
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)
  static struct etimer et;

  PROCESS_BEGIN();

  static struct gimbalData_t headData;

  leds_off(LEDS_ALL);

  while(1) {
    etimer_set(&et, CLOCK_SECOND/100);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
   
    leds_on(LEDS_BLUE | LEDS_GREEN);
    
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
    
    leds_off(LEDS_BLUE | LEDS_GREEN);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
