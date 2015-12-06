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

#define SAMPLES_PER_SEC 100
#define ADC_CHANNEL_X SOC_ADC_ADCCON_CH_AIN4 // BLUE WIRE
#define ADC_CHANNEL_Y SOC_ADC_ADCCON_CH_AIN3 // GREEN WIRE
#define ADC_CHANNEL_SCISSOR SOC_ADC_ADCCON_CH_AIN5 

#define CONTROLLER_MAIN_DEBUG 0

// Contiki process declarations

PROCESS(example_broadcast_process, "Broadcast example");
AUTOSTART_PROCESSES(&example_broadcast_process);

// Helper functions

static int16_t isCloseToCenter(int16_t i) {
    if(i > -150 && i < 150) return 0;
    else return i;
}

static int16_t isOutOfBounds(int16_t i) {
    if(i > 32764) return 32764;
    else if(i < 0) return 0;
    else return i;
}

// Receiving packets

static void broadcast_recv(struct broadcast_conn* c, const linkaddr_t* from) {
#if CONTROLLER_MAIN_DEBUG
    leds_on(LEDS_RED);
    printf("broadcast message received from %d.%d: '%s'\n", from->u8[0], from->u8[1], (char*)packetbuf_dataptr());
    leds_off(LEDS_RED);
#endif

    return;
}
static const struct broadcast_callbacks broadcast_call = { broadcast_recv };
static struct broadcast_conn broadcast;

// Reading values from the pots and sending movement commands to the robot

PROCESS_THREAD(example_broadcast_process, ev, data) {
    PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

    PROCESS_BEGIN();

    linkaddr_t nodeAddr;
    nodeAddr.u8[0] = CTRL_ADDR_A;
    nodeAddr.u8[1] = CTRL_ADDR_B;
    linkaddr_set_node_addr(&nodeAddr);

    initMoveNetwork(&broadcast, &broadcast_call);

    static struct etimer et;
    static struct moveData_t testData;
    testData.tDir = 0;
    testData.tSpeed = 100;
    testData.rAngle = 0;
    testData.rSpeed = 0;
    testData.sDir = 1;
    testData.sSpeed = 125;

    static int16_t ctrlX;
    static int16_t ctrlY;

    while(1) {
        etimer_set(&et, CLOCK_SECOND / SAMPLES_PER_SEC);

        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

        // It says AVDD5 but the reference voltage is actually 3V3
        // 32300 - 80, midpoint 17142
        ctrlX = isCloseToCenter(adc_get(ADC_CHANNEL_X, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512) - 17142);
        // 32764 - 800, midpoint 16872
        ctrlY = isCloseToCenter(adc_get(ADC_CHANNEL_Y, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512) - 16832);
        ctrlScissor = isOutOfBounds(adc_get(ADC_CHANNEL_SCISSOR, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512)) / 128;
        
#if CONTROLLER_MAIN_DEBUG
        printf("scissor: %d\n", ctrlScissor);
        printf("X: %d, Y: %d ", ctrlX, ctrlY);
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
    +      testData.sDir = 0;
    +      testData.sSpeed = 127 - ctrlScissor;
    +    } else {
    +      testData.sDir = 1;
    +      testData.sSpeed = ctrlScissor - 128;
    +    }

#if CONTROLLER_MAIN_DEBUG
        printf("degrees: %d, speed: %d\r\n", testData.tDir, testData.tSpeed);
#endif

        leds_on(LEDS_RED | LEDS_GREEN);
        broadcastMoveData(&testData, &broadcast);
        leds_off(LEDS_RED | LEDS_GREEN);

        unpackMoveData(&testData);
    }

    PROCESS_END();
}

