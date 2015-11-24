
#include "contiki.h"
#include "dev/leds.h"
#include "dev/quadrature.h"

#define SECTION_1 30.0
#define SECTION_2 90.0
#define SECTION_3 170.0

static struct etimer periodic_timer_red;

/*---------------------------------------------------------------------------*/
PROCESS(blink_process, "Quadratre Test");
AUTOSTART_PROCESSES(&blink_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_process, ev, data) {
	PROCESS_BEGIN();

    quadrature_init();

	etimer_set(&periodic_timer_red, CLOCK_SECOND / 10);

	while(1) {
		PROCESS_YIELD();

		if (etimer_expired(&periodic_timer_red)) {
			etimer_restart(&periodic_timer_red);
            double position = quadrature_get_position();
            if(position > -SECTION_1 && position < SECTION_1) {
                leds_on(LEDS_RED);
                leds_off(LEDS_GREEN);
                leds_off(LEDS_BLUE);
            } else if(position > -SECTION_2 && position < SECTION_2) {
                leds_off(LEDS_RED);
                leds_on(LEDS_GREEN);
                leds_off(LEDS_BLUE);
            } else if(position > -SECTION_3 && position < SECTION_3) {
                leds_off(LEDS_RED);
                leds_off(LEDS_GREEN);
                leds_on(LEDS_BLUE);
            }
        }
	}

	PROCESS_END();
}
