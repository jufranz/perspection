#include "contiki.h"
#include "sys/etimer.h"
#include "dev/adc.h"
#include "dev/leds.h"
#include "dev/uart.h"
#include "dev/serial-line.h"
#include "dev/quadrature.h"

#include <stdio.h>

static struct etimer periodic_timer_quadrature_read;

/*---------------------------------------------------------------------------*/
PROCESS(haptics_process, "Haptics");
AUTOSTART_PROCESSES(&haptics_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(haptics_process, ev, data) {

	PROCESS_BEGIN();

    //adc_init();
    quadrature_init();
	etimer_set(&periodic_timer_quadrature_read, CLOCK_SECOND / 5);

	while(1) {
		PROCESS_YIELD();

		if (etimer_expired(&periodic_timer_quadrature_read)) {
            /*int16_t adc_raw = adc_get(SOC_ADC_ADCCON_CH_AIN3, SOC_ADC_ADCCON_REF_AVDD5, SOC_ADC_ADCCON_DIV_512);*/
            /*if(adc_raw > 16000) {*/
                /*leds_on(LEDS_RED);*/
            /*} else {*/
                /*leds_off(LEDS_RED);*/
            /*}*/

            printf("%ld\r\n", (int32_t)quadrature_get_position());

			etimer_restart(&periodic_timer_quadrature_read);
		}
	}

	PROCESS_END();
}

