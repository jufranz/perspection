// Includes

#include "contiki.h"
#include "clock.h"
#include "net/rime/rime.h"
#include "random.h"

#include "dev/comms.h"
#include "dev/leds.h"
#include "dev/spi_wrapper.h"

#include <stdio.h>

// Defines

#define BODY_MAIN_DEBUG 0

#define MAX_YAW 1792 // Should be around 315 degrees
#define MIN_YAW 256  // Should be around 45 degrees

#define LAST_YAW_UNINIT 9000
#define YAW_COUNTS_PER_REV 2047
#define YAW_FLIP_THRESHOLD 1500

// Globals

static struct broadcast_conn broadcast;

int16_t lastYaw = LAST_YAW_UNINIT;
int16_t revolutionsDone = 0;

// Contiki process declarations

PROCESS(init_linkaddr_process, "Initialize linkaddr Address");
PROCESS(init_network_process, "Initialize Broadcast Channel");
AUTOSTART_PROCESSES(&init_linkaddr_process);

// Helper functions

int32_t getAbsoluteYawFromRawYaw(int16_t rawYaw) {
    if(lastYaw == LAST_YAW_UNINIT) {
        lastYaw = rawYaw;
        return rawYaw;
    }

    int16_t yawDelta = (rawYaw - lastYaw);
    if(yawDelta > YAW_FLIP_THRESHOLD) {
        revolutionsDone--;
    } else if(yawDelta < -YAW_FLIP_THRESHOLD) {
        revolutionsDone++;
    }

    lastYaw = rawYaw;

    return ((uint32_t)rawYaw + ((uint32_t)revolutionsDone * YAW_COUNTS_PER_REV));
}

// Receiving startup commands from the controller

static startupData_t recvStartupData;
static void startup_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_BLUE);

#if BODY_MAIN_DEBUG
    printf("Got startup data\r\n");
#endif

    unpackStartupData(&recvStartupData);

    // First send the enable/disable command to the C2000
    spi_wrapper_send_startup_control(recvStartupData.shouldBeOn);

    // Then acknowledge the startup data by sending it back to the controller
    broadcastStartupData(&recvStartupData, &broadcast);

    leds_off(LEDS_BLUE);
}

// Receiving movement commands from the controller

static moveData_t recvMoveData;
static void movement_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_RED | LEDS_GREEN);

    unpackMoveData(&recvMoveData);

#if BODY_MAIN_DEBUG
    printf("Dir: %d, Speed: %d, rspeed: %d\r\n", recvMoveData.tDir, recvMoveData.tSpeed, recvMoveData.rSpeed);
#endif

    // Sending the motion command off to the C2000
    spi_wrapper_send_body_control(recvMoveData.tDir, recvMoveData.tSpeed);

    // Sending the rotational speed command off to the C2000
    spi_wrapper_send_rotation_control(recvMoveData.rSpeed);

    leds_off(LEDS_RED | LEDS_GREEN);
}

// Receiving gimbal position commands from the headset

static gimbalData_t recvGimbalData;
static void gimbal_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_GREEN | LEDS_BLUE);

    unpackGimbalData(&recvGimbalData);

    int32_t yawToSend = getAbsoluteYawFromRawYaw(recvGimbalData.gYaw);

    // Limit and zero yaw
    if(yawToSend > MAX_YAW) yawToSend = MAX_YAW;
    if(yawToSend < MIN_YAW) yawToSend = MIN_YAW;
    yawToSend -= MIN_YAW;

#if BODY_MAIN_DEBUG
    printf("Yaw: %d, Pitch: %d, Sent Yaw: %d\n", recvGimbalData.gYaw, recvGimbalData.gPitch, yawToSend);
#endif

    spi_wrapper_send_gimbal_pos((uint16_t)yawToSend);

    leds_off(LEDS_GREEN | LEDS_BLUE);
}

// Receiving packets and sending them off for processing

static void broadcast_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    if(from->u8[0] == HEADSET_ADDR_A && from->u8[1] == HEADSET_ADDR_B) {
        if(didGetGimbalData()) {
            gimbal_recv(c, from);
        }
    } else if(from->u8[0] == CTRL_ADDR_A && from->u8[1] == CTRL_ADDR_B) {
        if(didGetStartupData()) {
            startup_recv(c, from);
        } else if(didGetMoveData()) {
            movement_recv(c, from);
        }
    }
}
static const struct broadcast_callbacks broadcast_call = { broadcast_recv };

// Link address init process

PROCESS_THREAD(init_linkaddr_process, ev, data) {
    PROCESS_BEGIN();

    spi_wrapper_init();

    /*quadrature_init();*/
    /*set_up_pwm();*/

    static linkaddr_t nodeAddr;
    nodeAddr.u8[0] = BODY_ADDR_A;
    nodeAddr.u8[1] = BODY_ADDR_B;
    linkaddr_set_node_addr(&nodeAddr);

    process_start(&init_network_process, NULL);

    PROCESS_END();
}

// Network init process

PROCESS_THREAD(init_network_process, ev, data) {
    PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

    PROCESS_BEGIN();

    initStartupNetwork(&broadcast, &broadcast_call);
    initMoveNetwork(&broadcast, &broadcast_call);
    // NOTE: For some reason calling all 3 of these fucks
    // stuff up, but calling any pair is fine. Since they
    // all do the same thing right now, I'm just leaving
    // this one out.
    //initGimbalNetwork(&broadcast, &broadcast_call);

    PROCESS_END();
}

