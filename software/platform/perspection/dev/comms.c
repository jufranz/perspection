#include "dev/comms.h"

void initGimbalNetwork(struct broadcast_conn *bcc, const struct broadcast_callbacks *bcb){
  broadcast_open(bcc, GIMBAL_CHANNEL, bcb);
}

void initMoveNetwork(struct broadcast_conn *bcc, const struct broadcast_callbacks *bcb){
  broadcast_open(bcc, MOVE_CHANNEL, bcb);
}

void broadcastMoveData(struct moveData_t *d, struct broadcast_conn *bcc){
  movePacket_t data;
  data.u32 = ((uint32_t)d->tSpeed & 0x0000007F) << 25;
  data.u32 |= ((uint32_t)d->tDir & 0x000001FF) << 16;
  data.u32 |= ((uint32_t)d->rSpeed & 0x0000007F) << 9;
  data.u32 |= ((uint32_t)d->rAngle & 0x000001FF);

  packetbuf_copyfrom(&data.c, MOVEDATA_LEN);
  broadcast_send(bcc);
}

void unpackMoveData(struct moveData_t *d){
  movePacket_t data;
  char *packet = (char *)packetbuf_dataptr();
  uint8_t i = 0;
  for(i; i < MOVEDATA_LEN; i++){
    data.c[i] = packet[i];
  }

  d->tSpeed = (uint8_t)((data.u32 & 0xFE000000) >> 25);
  d->tDir = (uint8_t)((data.u32 & 0x01FF0000) >> 16);
  d->rSpeed = (uint8_t)((data.u32 & 0x0000FE00) >> 9);
  d->rAngle = (uint8_t)(data.u32 & 0x000001FF);
}

void broadcastGimbalData(struct broadcast_conn *bcc){
  packetbuf_copyfrom("poop", 4);
  broadcast_send(bcc);
}
