// Includes

#include "contiki.h"
#include "clock.h"
#include "net/rime/rime.h"
#include "random.h"

#include "dev/adc.h"
#include "dev/comms.h"
#include "dev/gpio.h"
#include "dev/leds.h"

#include <math.h>
#include <stdio.h>

// Defines

#define CONTROLLER_MAIN_DEBUG 1

#define SAMPLES_PER_SEC 50
#define ADC_CHANNEL_X SOC_ADC_ADCCON_CH_AIN4 // BLUE WIRE
#define ADC_CHANNEL_Y SOC_ADC_ADCCON_CH_AIN3 // GREEN WIRE
#define ADC_CHANNEL_SCISSOR SOC_ADC_ADCCON_CH_AIN5

// Globals

static struct broadcast_conn broadcast;

static uint8_t hasHeadsetAckedEnable = 0;
static uint8_t hasRobotBodyAckedEnable = 0;
static uint8_t hasCameraAckedEnable = 0;

// Contiki process declarations

PROCESS(init_wireless_and_control_process, "Init wireless and control process");
PROCESS(control_broadcast_process, "Control broadcast process");
AUTOSTART_PROCESSES(&init_wireless_and_control_process);

// Helper functions

static int16_t isCloseToCenter(int16_t i) {
    if(i > -150 && i < 150) return 0;
    else return i;
}

/*static int16_t isOutOfBounds(int16_t i) {*/
    /*if(i > 32764) return 32764;*/
    /*else if(i < 0) return 0;*/
    /*else return i;*/
/*}*/

// Receiving packets

static void broadcast_recv(struct broadcast_conn* c, const linkaddr_t* from) {
    leds_on(LEDS_RED);

    if(from->u8[0] == HEADSET_ADDR_A && from->u8[1] == HEADSET_ADDR_B) {
        if(didGetStartupData()) {
            // Got an enable acknowledge from the headset
            hasHeadsetAckedEnable = 1;
#if CONTROLLER_MAIN_DEBUG
            printf("Got enable ack from headset\r\n");
#endif
        }
    } else if(from->u8[0] == BODY_ADDR_A && from->u8[1] == BODY_ADDR_B) {
        if(didGetStartupData()) {
            // Got an enable acknowledge from the robot body
            hasRobotBodyAckedEnable = 1;
#if CONTROLLER_MAIN_DEBUG
            printf("Got enable ack from robot body\r\n");
#endif
        }
    } else if(from->u8[0] == CAMERA_ADDR_A && from->u8[1] == CAMERA_ADDR_B) {
        if(didGetStartupData()) {
            // Got an enable acknowledge from the camera
            hasCameraAckedEnable = 1;
#if CONTROLLER_MAIN_DEBUG
            printf("Got enable ack from camera\r\n");
#endif
        }
    }

    leds_off(LEDS_RED);

    return;
}
static const struct broadcast_callbacks broadcast_call = { broadcast_recv };

// Initializing the wireless stuff and sending enable signals to the other boards

PROCESS_THREAD(init_wireless_and_control_process, ev, data) {
    PROCESS_BEGIN();

    linkaddr_t nodeAddr;
    nodeAddr.u8[0] = CTRL_ADDR_A;
    nodeAddr.u8[1] = CTRL_ADDR_B;
    linkaddr_set_node_addr(&nodeAddr);
    initStartupNetwork(&broadcast, &broadcast_call);

    static struct etimer startup_timer;
    static startupData_t startupData;
    startupData.shouldBeOn = 1;

#if CONTROLLER_MAIN_DEBUG
    printf("Startup signal broadcasting, waiting for ACKs\r\n");
#endif

    while(hasHeadsetAckedEnable == 0 || hasRobotBodyAckedEnable == 0 || hasCameraAckedEnable == 0) {
        broadcastStartupData(&startupData, &broadcast);

        etimer_set(&startup_timer, CLOCK_SECOND / 2);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&startup_timer));
    }

#if CONTROLLER_MAIN_DEBUG
    printf("All boards enabled\r\n");
#endif

    // Once everybody has acknowledged the enable, start the control process
    process_start(&control_broadcast_process, NULL);

    PROCESS_END();
}

// Reading values from the pots and sending movement commands to the robot

PROCESS_THREAD(control_broadcast_process, ev, data) {
    PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

    PROCESS_BEGIN();

    initMoveNetwork(&broadcast, &broadcast_call);

    static struct etimer et;
    static moveData_t testData;
    static int16_t ctrlX;
    static int16_t ctrlY;

    testData.tDir = 0;
    testData.tSpeed = 100;
    testData.rAngle = 0;
    testData.rSpeed = 0;
    testData.sDir = 1;
    testData.sSpeed = 125;

<<<<<<< HEAD
    static int16_t ctrlX;
    static int16_t ctrlY;
    static int16_t ctrlScissor;

=======
>>>>>>> 15a8eb84e12a87a7a3bd7d84f07dbb91690d8f64
    while(1) {
        etimer_set(&et, CLOCK_SECOND / SAMPLES_PER_SEC);
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

        // It says AVDD5 but the reference voltage is actually 3V3
        // 32300 - 80, midpoint 17142
        ctrlX = isCloseToCenter(adc_get(ADC_CHANNEL_X, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512) - 17142);
        // 32764 - 800, midpoint 16872
        ctrlY = isCloseToCenter(adc_get(ADC_CHANNEL_Y, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512) - 16832);
<<<<<<< HEAD
        ctrlScissor = isOutOfBounds(adc_get(ADC_CHANNEL_SCISSOR, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512)) / 128;
        
=======
        /*ctrlScissor = isOutOfBounds(adc_get(ADC_CHANNEL_SCISSOR, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512)) / 128;*/
>>>>>>> 15a8eb84e12a87a7a3bd7d84f07dbb91690d8f64

#if CONTROLLER_MAIN_DEBUG
        /*printf("scissor: %d\n", ctrlScissor);*/
        printf("X: %d, Y: %d\r\n", ctrlX, ctrlY);
#endif

        // XY control
        if(ctrlX == 0 && ctrlY == 0) {
            // All 9 bits are 1's, indicates no direction
            testData.tDir = 511;
            testData.tSpeed = 0;
        } else {
            testData.tDir = (uint16_t)((atan2((double)ctrlY, (double)ctrlX) * 180 / M_PI) + 180) % 360;
            testData.tSpeed = (uint8_t)((uint32_t)sqrt(pow((double)ctrlY, 2) + pow((double)ctrlX, 2))/(uint32_t)133);
            if(testData.tSpeed > 127) testData.tSpeed = 127;
        }
        if(ctrlScissor <= 127){
            testData.sDir = 0;
            testData.sSpeed = 127 - ctrlScissor;
        } else {
            testData.sDir = 1;
            testData.sSpeed = ctrlScissor - 128;
        }

        /*if(ctrlScissor <= 127){*/
          /*testData.sDir = 0;*/
          /*testData.sSpeed = 127 - ctrlScissor;*/
        /*} else {*/
          /*testData.sDir = 1;*/
          /*testData.sSpeed = ctrlScissor - 128;*/
        /*}*/

#if CONTROLLER_MAIN_DEBUG
        printf("degrees: %d, speed: %d\r\n", testData.tDir, testData.tSpeed);
        printf("sdegree: %d, sspeed: %d\r\n", testData.sDir, testData.sSpeed);
#endif

        leds_on(LEDS_RED | LEDS_GREEN);
        broadcastMoveData(&testData, &broadcast);
        leds_off(LEDS_RED | LEDS_GREEN);
    }

    PROCESS_END();
}

