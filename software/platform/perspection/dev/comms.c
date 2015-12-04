#include "dev/comms.h"

void initGimbalNetwork(struct broadcast_conn *bcc, const struct broadcast_callbacks *bcb){
  broadcast_open(bcc, GIMBAL_CHANNEL, bcb);
}

void initMoveNetwork(struct broadcast_conn *bcc, const struct broadcast_callbacks *bcb){
  broadcast_open(bcc, MOVE_CHANNEL, bcb);
}

void broadcastMoveData(struct moveData_t *d, struct broadcast_conn *bcc){
  movePacket_t data;
  data.u64 = ((uint64_t)d->tSpeed & 0x0000007F) << TSPEED_OFFSET;
  data.u64 |= ((uint64_t)d->tDir & 0x000001FF) << TDIR_OFFSET;
  data.u64 |= ((uint64_t)d->rSpeed & 0x0000007F) << RSPEED_OFFSET;
  data.u64 |= ((uint64_t)d->rAngle & 0x000001FF) << RANGLE_OFFSET; 
  data.u64 |= ((uint64_t)d->sDir & 0x00000001) << SDIR_OFFSET; 
  data.u64 |= ((uint64_t)d->sSpeed & 0x0000007F) << SSPEED_OFFSET;

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

  d->tSpeed = (uint8_t)((data.u64 & 0xFE00000000) >> TSPEED_OFFSET);
  d->tDir = (uint16_t)((data.u64 & 0x01FF000000) >> TDIR_OFFSET);
  d->rSpeed = (uint8_t)((data.u64 & 0x0000FE0000) >> RSPEED_OFFSET);
  d->rAngle = (uint16_t)(data.u64 & 0x000001FF00) >> RANGLE_OFFSET;
  d->sDir = (uint8_t)(data.u64 & 0x0000000080) >> SDIR_OFFSET;
  d->sSpeed = (uint8_t)(data.u64 & 0x000000007F) >> SSPEED_OFFSET;
}

void broadcastGimbalData(struct broadcast_conn *bcc){
  packetbuf_copyfrom("poop", 4);
  broadcast_send(bcc);
}
