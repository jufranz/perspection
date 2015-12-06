/* bno055 test yo
 * -----------
 * Does shit
 *
 */

#include "contiki.h"
#include "random.h"
#include "sys/clock.h"

#include "dev/leds.h"
#include "dev/bno055.h"
#include "dev/clock_wrapper.h"

#include <stdio.h>

#define DEBUG 1

void delay(uint16_t msec){
  int i;
  for(i = 0; i < msec; i++){
    clock_delay_usec(1000);
  };
}

/*---------------------------------------------------------------------------*/
PROCESS(bno055_test_process, "BNO055 example");
AUTOSTART_PROCESSES(&bno055_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(bno055_test_process, ev, data)
{
  //static struct etimer et;

  PROCESS_BEGIN();
  leds_set(LEDS_BLUE);
 
  clock_wrapper_delay_msec(500);

  if(!bno055_init()) {
    while(1){
      printf("uh oh...\n");
    }
  }
  bno055_set_mode(BNO055_OPERATION_MODE_NDOF);
  leds_set(0);
  while(1) { 
    /* Delay 1 second */
    //etimer_set(&et, CLOCK_SECOND * 1);
    //PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    bno055_vector_t euler_data = bno055_get_vector(BNO055_EULER_VECTOR);
    printf("x: %d\ty: %d\tz: %d\n", euler_data.x/16, euler_data.y/16, euler_data.z/16);
    bno055_calibration_t cal = bno055_get_calibration();
    if(cal.gyro_cal) leds_on(LEDS_RED);
    if(cal.accel_cal) leds_on(LEDS_GREEN);
    if(cal.mag_cal) leds_on(LEDS_BLUE);
    clock_wrapper_delay_msec(10);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
