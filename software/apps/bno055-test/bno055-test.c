/* bno055 test yo
 * -----------
 * Does shit
 *
 */

#include "contiki.h"
#include "random.h"
#include "dev/bno055.h"

#include "dev/leds.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(bno055_test_process, "BNO055 example");
AUTOSTART_PROCESSES(&bno055_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(bno055_test_process, ev, data)
{
  //static struct etimer et;

  PROCESS_BEGIN();

  if(!bno055_init()) {
    printf("uh oh...\n");
  }
  bno055_set_mode(BNO055_OPERATION_MODE_NDOF);
  while(1) { 
    /* Delay 1 second */
    //etimer_set(&et, CLOCK_SECOND * 1);
    //PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    bno055_vector_t euler_data = bno055_get_vector(BNO055_EULER_VECTOR);
    printf("x: %d\ty: %d\tz: %d\n", euler_data.x, euler_data.y, euler_data.z);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
