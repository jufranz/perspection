#include "dev/comms.h"
#include <string.h>

// Startup stuff

void initStartupNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb) {
    broadcast_open(bcc, STARTUP_CHANNEL, bcb);
}

void broadcastStartupData(startupData_t* d, struct broadcast_conn* bcc) {
    startupPacket_t packet;
    d->type = STARTUP_DATA_TYPE;
    packet.data = *d;

    packetbuf_copyfrom(&packet.c, sizeof(startupData_t));
    broadcast_send(bcc);
}

bool didGetStartupData() {
    char* packet = (char*)packetbuf_dataptr();
    return (*packet == STARTUP_DATA_TYPE);
}

void unpackStartupData(startupData_t* d) {
    startupPacket_t packet;
    memcpy(packet.c, packetbuf_dataptr(), sizeof(startupData_t));

    d->type = packet.data.type;
    d->shouldBeOn = packet.data.shouldBeOn;
}

// Gimbal stuff

void initGimbalNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb) {
    broadcast_open(bcc, GIMBAL_CHANNEL, bcb);
}

void broadcastGimbalData(gimbalData_t* d, struct broadcast_conn* bcc) {
    gimbalPacket_t packet;
    d->type = GIMBALDATA_TYPE;
    packet.data = *d;

    packetbuf_copyfrom(&packet.c, sizeof(gimbalData_t));
    broadcast_send(bcc);
}

bool didGetGimbalData() {
    char* packet = (char*)packetbuf_dataptr();
    return (*packet == GIMBALDATA_TYPE);
}

void unpackGimbalData(gimbalData_t* d) {
    gimbalPacket_t packet;
    memcpy(packet.c, packetbuf_dataptr(), sizeof(gimbalData_t));

    d->type = packet.data.type;
    d->gYaw = packet.data.gYaw;
    d->gPitch = packet.data.gPitch;
}

int16_t scaleForEncoder(int16_t d) {
    return (int16_t)((double)d* (double)ENCODER_RES_PPR / (double)IMU_360_DEG_VAL);
}

// Move stuff

void initMoveNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb) {
    broadcast_open(bcc, MOVE_CHANNEL, bcb);
}

void broadcastMoveData(moveData_t* d, struct broadcast_conn* bcc) {
    movePacket_t packet;
    d->type = MOVEDATA_TYPE;
    packet.data = *d;

    packetbuf_copyfrom(&packet.c, sizeof(moveData_t));
    broadcast_send(bcc);
}

bool didGetMoveData() {
    char* packet = (char*)packetbuf_dataptr();
    return (*packet == MOVEDATA_TYPE);
}

void unpackMoveData(moveData_t* d) {
    movePacket_t packet;
    memcpy(packet.c, packetbuf_dataptr(), sizeof(moveData_t));

    d->type = packet.data.type;
    d->tSpeed = packet.data.tSpeed;
    d->tDir = packet.data.tDir;
    d->rSpeed = packet.data.rSpeed;
    d->rAngle = packet.data.rAngle;
    d->sDir = packet.data.sDir;
    d->sSpeed = packet.data.sSpeed;
}

