#include "dev/comms.h"

// Startup stuff

void initStartupNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb) {
    broadcast_open(bcc, STARTUP_CHANNEL, bcb);
}

void broadcastStartupData(struct startupData_t* d, struct broadcast_conn* bcc) {
    startupPacket_t data;
    data.type = STARTUP_DATA_TYPE;
    data.u8 = d->shouldBeOn;

    packetbuf_copyfrom(&data.c, STARTUP_DATA_PACKET_LEN);
    broadcast_send(bcc);
}

bool didGetStartupData() {
    char* packet = (char*)packetbuf_dataptr();
    return (*packet == STARTUP_DATA_TYPE);
}

void unpackStartupData(struct startupData_t* d) {
    startupPacket_t data;
    char* packet = (char*)packetbuf_dataptr();

    uint8_t i;
    for(i = 0; i < STARTUP_DATA_PACKET_LEN; i++){
        data.c[i] = packet[i];
    }

    d->shouldBeOn = (uint8_t)data.u8;
}

// Gimbal stuff

void initGimbalNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb) {
    broadcast_open(bcc, GIMBAL_CHANNEL, bcb);
}

void broadcastGimbalData(struct gimbalData_t* d, struct broadcast_conn* bcc) {
    gimbalPacket_t data;
    data.type = GIMBALDATA_TYPE;
    data.u32 = ((uint32_t)d->gYaw) << GYAW_OFFSET;
    data.u32 |= ((uint32_t)d->gPitch) & 0x00FF;

    packetbuf_copyfrom(&data.c, GIMBALDATA_PACKET_LEN);
    broadcast_send(bcc);
}

bool didGetGimbalData() {
    char* packet = (char*)packetbuf_dataptr();
    return (*packet == GIMBALDATA_TYPE);
}

void unpackGimbalData(struct gimbalData_t* d) {
    gimbalPacket_t data;
    char* packet = (char*)packetbuf_dataptr();

    uint8_t i;
    for(i = 0; i < GIMBALDATA_PACKET_LEN; i++){
        data.c[i] = packet[i];
    }

    d->gYaw = (uint16_t)(data.u32 >> GYAW_OFFSET);
    d->gPitch = (uint16_t)(data.u32 >> GPITCH_OFFSET);
}

int16_t scaleForEncoder(int16_t d) {
    return (int16_t)((double)d* (double)ENCODER_RES_PPR / (double)IMU_360_DEG_VAL);
}

// Move stuff

void initMoveNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb) {
    broadcast_open(bcc, MOVE_CHANNEL, bcb);
}

void broadcastMoveData(struct moveData_t* d, struct broadcast_conn* bcc) {
    movePacket_t data;

    data.type = MOVEDATA_TYPE;
    data.u64 = ((uint64_t)d->tSpeed  & 0x0000007F) << TSPEED_OFFSET;
    data.u64 |= ((uint64_t)d->tDir   & 0x000001FF) << TDIR_OFFSET;
    data.u64 |= ((uint64_t)d->rSpeed & 0x0000007F) << RSPEED_OFFSET;
    data.u64 |= ((uint64_t)d->rAngle & 0x000001FF) << RANGLE_OFFSET;
    data.u64 |= ((uint64_t)d->sDir   & 0x00000001) << SDIR_OFFSET;
    data.u64 |= ((uint64_t)d->sSpeed & 0x0000007F) << SSPEED_OFFSET;

    packetbuf_copyfrom(&data.c, MOVEDATA_PACKET_LEN);
    broadcast_send(bcc);
}

bool didGetMoveData() {
    char* packet = (char*)packetbuf_dataptr();
    return (*packet == MOVEDATA_TYPE);
}

void unpackMoveData(struct moveData_t* d) {
    movePacket_t data;
    char* packet = (char*)packetbuf_dataptr();

    uint8_t i;
    for(i = 0; i < MOVEDATA_PACKET_LEN; i++){
        data.c[i] = packet[i];
    }

    d->tSpeed = (uint8_t)((data.u64  & 0xFE00000000) >> TSPEED_OFFSET);
    d->tDir = (uint16_t)((data.u64   & 0x01FF000000) >> TDIR_OFFSET);
    d->rSpeed = (uint8_t)((data.u64  & 0x0000FE0000) >> RSPEED_OFFSET);
    d->rAngle = (uint16_t)((data.u64 & 0x000001FF00) >> RANGLE_OFFSET);
    d->sDir = (uint8_t)((data.u64    & 0x0000000080) >> SDIR_OFFSET);
    d->sSpeed = (uint8_t)((data.u64  & 0x000000007F) >> SSPEED_OFFSET);
}

