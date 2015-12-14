// Includes

#include "contiki.h"
#include "clock.h"
#include "net/rime/rime.h"
#include "random.h"

#include "dev/comms.h"
#include "dev/leds.h"
#include "dev/spi_wrapper.h"

#include <stdio.h>
#include <stdbool.h>

// Defines

#define CAMERA_MAIN_DEBUG 0

#define MAX_PITCH 425  // Should be around +80 degrees
#define MIN_PITCH -375  // Should be around -80 degrees

#define LAST_PITCH_UNINIT 9000
#define PITCH_COUNTS_PER_REV 2047
#define PITCH_FLIP_THRESHOLD 1500

// Globals

static struct broadcast_conn broadcast;

int16_t lastPitch = LAST_PITCH_UNINIT;
int16_t revolutionsDone = 0;
static bool shouldGo = false;

// Contiki process declarations

PROCESS(init_linkaddr_process, "Initialize linkaddr Address");
PROCESS(init_network_process, "Initialize Broadcast Channel");
AUTOSTART_PROCESSES(&init_linkaddr_process);

// Helper functions

int32_t getAbsolutePitchFromRawPitch(int16_t rawPitch) {
    if(lastPitch == LAST_PITCH_UNINIT) {
        lastPitch = rawPitch;
        return rawPitch;
    }

    int16_t pitchDelta = (rawPitch - lastPitch);
    if(pitchDelta > PITCH_FLIP_THRESHOLD) {
        revolutionsDone--;
    } else if(pitchDelta < -PITCH_FLIP_THRESHOLD) {
        revolutionsDone++;
    }

    lastPitch = rawPitch;

    return ((uint32_t)rawPitch + ((uint32_t)revolutionsDone * PITCH_COUNTS_PER_REV));
}

// Receiving startup commands from the controller

static startupData_t recvStartupData;
static void startup_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_BLUE);

#if CAMERA_MAIN_DEBUG
    printf("Got startup data\r\n");
#endif

    unpackStartupData(&recvStartupData);
    shouldGo = recvStartupData.shouldBeOn;

    // First send the enable/disable command to the C2000
    spi_wrapper_send_startup_control(recvStartupData.shouldBeOn);

    // Then acknowledge the startup data by sending it back to the controller
    broadcastStartupData(&recvStartupData, &broadcast);

    leds_off(LEDS_BLUE);
}

// Receiving gimbal position commands from the headset

static gimbalData_t recvGimbalData;
static void gimbal_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_GREEN | LEDS_BLUE);

    unpackGimbalData(&recvGimbalData);

    int32_t pitchToSend = getAbsolutePitchFromRawPitch(recvGimbalData.gPitch);

    // Limit and zero pitch
    if(pitchToSend > MAX_PITCH) pitchToSend = MAX_PITCH;
    if(pitchToSend < MIN_PITCH) pitchToSend = MIN_PITCH;
    pitchToSend -= MIN_PITCH;
    pitchToSend = ((MAX_PITCH - MIN_PITCH) - pitchToSend);

#if CAMERA_MAIN_DEBUG
    printf("Yaw: %d, Pitch: %d, Sent Pitch: %d\n", recvGimbalData.gYaw, recvGimbalData.gPitch, pitchToSend);
#endif

    spi_wrapper_send_gimbal_pos((uint16_t)pitchToSend);

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
        }
    }
}
static const struct broadcast_callbacks broadcast_call = { broadcast_recv };

// Link address init process

PROCESS_THREAD(init_linkaddr_process, ev, data) {
    PROCESS_BEGIN();

    spi_wrapper_init();

    static linkaddr_t nodeAddr;
    nodeAddr.u8[0] = CAMERA_ADDR_A;
    nodeAddr.u8[1] = CAMERA_ADDR_B;
    linkaddr_set_node_addr(&nodeAddr);

    process_start(&init_network_process, NULL);

    PROCESS_END();
}

// Network init process

PROCESS_THREAD(init_network_process, ev, data) {
    PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

    PROCESS_BEGIN();

    initStartupNetwork(&broadcast, &broadcast_call);
    initGimbalNetwork(&broadcast, &broadcast_call);

    PROCESS_END();
}

