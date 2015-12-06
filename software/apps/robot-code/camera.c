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

#define CAMERA_MAIN_DEBUG 0

// Contiki process declarations

PROCESS(init_linkaddr_process, "Initialize linkaddr Address");
PROCESS(init_network_process, "Initialize Broadcast Channel");
AUTOSTART_PROCESSES(&init_linkaddr_process);

// Receiving startup commands from the controller

static struct startupData_t recvStartupData;
static void startup_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_BLUE);

    unpackStartupData(&recvStartupData);

    // First send the enable/disable command to the C2000
    spi_wrapper_send_startup_control(recvStartupData.shouldBeOn);

    // Then acknowledge the startup data by sending it back to the controller
    broadcastStartupData(&recvStartupData);

    leds_off(LEDS_BLUE);
}

// Receiving gimbal position commands from the headset

static struct gimbalData_t recvGimbalData;
static void gimbal_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_GREEN | LEDS_BLUE);

    unpackGimbalData(&recvGimbalData);

#if CAMERA_MAIN_DEBUG
    printf("360 scaled to 5760 -- Yaw: %d, Pitch: %d\n", recvGimbalData.gYaw, recvGimbalData.gPitch);
#endif

    // TODO: Magic shit

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
static struct broadcast_conn broadcast;

// Link address init process

PROCESS_THREAD(init_linkaddr_process, ev, data) {
    PROCESS_BEGIN();

    spi_wrapper_init();

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
    initGimbalNetwork(&broadcast, &broadcast_call);

    PROCESS_END();
}

