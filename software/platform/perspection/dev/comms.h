#ifndef COMMS_H_
#define COMMS_H_

#include "contiki.h"
#include "net/rime/rime.h"
#include "dev/leds.h"
#include <stdbool.h>

#define GIMBAL_CHANNEL 110
#define MOVE_CHANNEL 110


#define HEADSET_ADDR_A 123
#define HEADSET_ADDR_B 211

#define BODY_ADDR_A 111
#define BODY_ADDR_B 222

#define CAMERA_ADDR_A 234 
#define CAMERA_ADDR_B 234

#define CTRL_ADDR_A 101
#define CTRL_ADDR_B 202

#define MOVEDATA_LEN 5
struct moveData_t {
  //translational speed
  uint8_t tSpeed;
  //translational direction
  uint16_t tDir;
  //rotational speed
  uint8_t rSpeed;
  //rotational angle
  uint16_t rAngle;
  //scissor direction
  uint8_t sDir;
  //scissor speed
  uint8_t sSpeed;
};

//ADD contiki/core/lib/crc16.h if need checksum

//packet structure:
//  33-39: tSpeed
//  24-32: tDir
//  17-23: rSpeed
//  8-16: rAngle
//  7: sDir
//  0-6: sSpeed
#define TSPEED_OFFSET 33
#define TDIR_OFFSET 24
#define RSPEED_OFFSET 17
#define RANGLE_OFFSET 8
#define SDIR_OFFSET 7
#define SSPEED_OFFSET 0

typedef union {
  char c[MOVEDATA_LEN];
  uint64_t u64;
} movePacket_t;

void initGimbalNetwork(struct broadcast_conn *bcc, 
      const struct broadcast_callbacks *bcb);
void initMoveNetwork(struct broadcast_conn *bcc, 
      const struct broadcast_callbacks *bcb);

//function for CTRL to broadcast movement data
//to the robot boards. just pass in the struct 
//pointer and it will package the data
void broadcastMoveData(struct moveData_t *d, struct broadcast_conn *bcc);

//function for robot boards to parse and unpack
//movement data from CTRL to robot boards. pass
//in a pointer to the desired struct variable
//into which to unpack
void unpackMoveData(struct moveData_t *d);

void broadcastGimbalData(struct broadcast_conn *bcc);

#endif
