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

#include "dev/comms.h"

#include "dev/leds.h"

#include <stdio.h>
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
PROCESS_THREAD(example_broadcast_process, ev, data)
{
  static struct etimer et;

  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  linkaddr_t nodeAddr;
  nodeAddr.u8[0] = CTRL_ADDR_A;
  nodeAddr.u8[1] = CTRL_ADDR_B;
  linkaddr_set_node_addr(&nodeAddr);

  initMoveNetwork(&broadcast, &broadcast_call);

  static struct moveData_t testData;
  testData.tDir = 0;
  testData.tSpeed = 0;
  testData.rAngle = 0;
  testData.rSpeed = 0;

  while(1) {

    /* Delay 1 second */
    etimer_set(&et, CLOCK_SECOND/200);

    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    
    broadcastMoveData(&testData, &broadcast);
    leds_on(LEDS_GREEN);    
    printf("sent data from controller %d.%d -- tDir: %d tSpeed: %d rAngle: %d rSpeed: %d\n",
            linkaddr_node_addr.u8[0], linkaddr_node_addr.u8[1],
            testData.tDir, testData.tSpeed, testData.rAngle, testData.rSpeed);
    leds_off(LEDS_GREEN);
    testData.tDir++;
    testData.tSpeed++;
    testData.rAngle++;
    testData.rSpeed++;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
