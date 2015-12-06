#ifndef COMMS_H_
#define COMMS_H_

#include "contiki.h"
#include "net/rime/rime.h"
#include "dev/leds.h"

#include <stdbool.h>

// CHANNEL IDs
#define GIMBAL_CHANNEL 110
#define MOVE_CHANNEL 110

// ATUM NODE IDs
#define HEADSET_ADDR_A 123
#define HEADSET_ADDR_B 211

#define BODY_ADDR_A 111
#define BODY_ADDR_B 222

#define CAMERA_ADDR_A 234
#define CAMERA_ADDR_B 234

#define CTRL_ADDR_A 101
#define CTRL_ADDR_B 202

/*------------------------------------------------------------*/
/*--------- ROBOT GIMBAL DATA STRUCTURES AND FUNCTIONS -------*/
/*------------------------------------------------------------*/

#define BOARD_MOUNTED_ON_HEADSET_NORMALLY 0

// Sent over broadcast for the following struct
struct gimbalData_t {
    /*
    README: the following degree measurements are
            based on everything being angle zero when the
            IMU is sitting flat on a table. For the time
            being there is no way to reorient the ranges
            such that zero angles are when the IMU is oriented
            such that it rests against a wall perpendicular to
            the ground.
    */

    /*
    README: the data that is contained in this struct
            is not limited by any range other than the range
            imposed by the IMU itself. The assumption is that
            the code on the C2000 provides features that limits
            the range of movement of the BLDC motors. The purpose
            of the comms library is to relay properly scaled data.
    */

    // yaw angle (heading)
    // 0-360 degrees, scaled to 0 - ENCODER_RESOLUTION
    int16_t gYaw;

    // pitch angle
    // if BOARD_MOUNTED_ON_HEADSET_NORMALLY,
    // -90 - +90 degrees,
    // else if BOARD_MOUNTED_90_DEGREES_FROM_NORMAL_MOUNTING_POSITION,
    // -180 - +180 degrees,
    // scaled to -0.5*ENCODER_RESOLUTION - +0.5*ENCODER_RESOLUTION
    int16_t gPitch;
};

// packet structure:
//   23-12: Yaw/Heading, signed
//   11-0:  Pitch, signed

// GIMBALDATA specifies number of bytes being
// sent over broadcast for the following struct
#define GIMBALDATA_LEN 4

#define GYAW_OFFSET 16
#define GPITCH_OFFSET 0

typedef union {
    char c[GIMBALDATA_LEN];
    uint32_t u32;
} gimbalPacket_t;

// The following functions scale the IMU data to the highest
// possible resolution that the encoders can understand.
// The resolution is that 1 degree = 16LSB in the register
// thus 360 degrees = 5760 LSB

#define ENCODER_RES_PPR 2048
#define IMU_360_DEG_VAL 5760
int16_t scaleForEncoder(int16_t d);

// Function to set up channel and the callback struct.
// channel number is defined int the header file
void initGimbalNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb);

// Function for HEADSET to broadcast gimbal yaw
// and pitch data to the robot boards. just pass
// in the struct pointer and it will packaget the data
void broadcastGimbalData(struct gimbalData_t* d, struct broadcast_conn* bcc);

// Function for robot boards to parse and unpack
// gimbal data from HEADSET to robot boards.
// pass in a pointer to the desired struct variable
// into which to unpack.
void unpackGimbalData(struct gimbalData_t* d);

/*------------------------------------------------------------*/
/*-------- ROBOT MOVEMENT DATA STRUCTURES AND FUNCTIONS ------*/
/*------------------------------------------------------------*/

// MOVEDATA specifies number of bytes being
// sent over broadcast for the following struct
#define MOVEDATA_LEN 5
struct moveData_t {
    // translational speed
    // 0-127
    uint8_t tSpeed;

    // translational direction
    // 0-360 degrees
    uint16_t tDir;

    // rotational speed
    // 0-127
    uint8_t rSpeed;

    // rotational angle
    // 0-360, or 0-511 decoded to 0-360 range
    uint16_t rAngle;

    // scissor direction
    // 0 or 1, up or down
    uint8_t sDir;

    // scissor speed
    // 0-127
    uint8_t sSpeed;
};

// packet structure:
//   33-39: tSpeed, unsigned
//   24-32: tDir, unsigned
//   17-23: rSpeed, unsigned
//   8-16: rAngle, unsigned
//   7: sDir, unsigned
//   0-6: sSpeed, unsigned

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

// Function to set up channel and the callback struct.
// channel number is defined in the header file
void initMoveNetwork(struct broadcast_conn* bcc, const struct broadcast_callbacks* bcb);

// Function for CTRL to broadcast movement data
// to the robot boards. just pass in the struct
// pointer and it will package the data
void broadcastMoveData(struct moveData_t* d, struct broadcast_conn* bcc);

// Function for robot boards to parse and unpack
// movement data from CTRL to robot boards. pass
// in a pointer to the desired struct variable
// into which to unpack
void unpackMoveData(struct moveData_t* d);

// ADD contiki/core/lib/crc16.h if need checksum

#endif

