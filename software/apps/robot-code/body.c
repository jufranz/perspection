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
#include "dev/spi_wrapper.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(init_linkaddr_process, "Initialize linkaddr Address");
PROCESS(init_network_process, "Initialize Broadcast Channel");
AUTOSTART_PROCESSES(&init_linkaddr_process);
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
static struct moveData_t recvData;
static void
movement_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  leds_on(LEDS_RED);
  unpackMoveData(&recvData);

  /*printf("Dir: %d, Speed: %d, Pos: %d\r\n", recvData.tDir, recvData.tSpeed, recvData.rAngle);*/
  spi_wrapper_send_body_control(recvData.tDir, recvData.tSpeed);
  spi_wrapper_send_gimbal_pos(recvData.rAngle);

  leds_off(LEDS_RED);
}
/*---------------------------------------------------------------------------*/
static void
gimbal_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  leds_on(LEDS_GREEN);
  /*
  printf("%d.%d: received gimbal broadcast from %d,%d: %s\n", linkaddr_node_addr.u8[0],
        linkaddr_node_addr.u8[1], from->u8[0], from->u8[1], (char *)packetbuf_dataptr());
  */
  leds_off(LEDS_GREEN);
}
/*---------------------------------------------------------------------------*/
static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
  if(from->u8[0] == HEADSET_ADDR_A && from->u8[1] == HEADSET_ADDR_B){
    gimbal_recv(c, from);
    return;
  }
  if(from->u8[0] == CTRL_ADDR_A && from->u8[1] == CTRL_ADDR_B){
    movement_recv(c, from);
    return;
  }
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
PROCESS_THREAD(init_linkaddr_process, ev, data)
{
  PROCESS_BEGIN();

  spi_wrapper_init();

  static linkaddr_t nodeAddr;
  nodeAddr.u8[0] = BODY_ADDR_A;
  nodeAddr.u8[1] = BODY_ADDR_B;
  linkaddr_set_node_addr(&nodeAddr);

  process_start(&init_network_process, NULL);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(init_network_process, ev, data)
{
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  initMoveNetwork(&broadcast, &broadcast_call);
  initGimbalNetwork(&broadcast, &broadcast_call);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
