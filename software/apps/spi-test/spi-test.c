#include "contiki.h"
#include "random.h"
#include "spi-arch.h"
#include "dev/spi.h"
#include "dev/ioc.h"
#include "dev/leds.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "gpio.h"

#include <stdio.h>

static struct etimer periodic_timer;

/*---------------------------------------------------------------------------*/
PROCESS(spi_test_process, "spi example");
AUTOSTART_PROCESSES(&spi_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(spi_test_process, ev, data)
{
  PROCESS_BEGIN();

  etimer_set(&periodic_timer, CLOCK_SECOND / 2);

  //spi-initialization
  spix_init(SPI_DEFAULT_INSTANCE);
  spix_set_mode(SPI_DEFAULT_INSTANCE, SSI_CR0_FRF_MOTOROLA, 0, 0, 16);
  spix_cs_init(GPIO_C_NUM, 2);

  static uint16_t send = 1;
  static uint16_t recv = 0;

  while(1) {
	PROCESS_YIELD();

	if (etimer_expired(&periodic_timer)) {
        SPIX_FLUSH(SPI_DEFAULT_INSTANCE);

        // Write some real data, read some dummy data
        SPIX_WAITFORTxREADY(SPI_DEFAULT_INSTANCE);
        SPI_CS_CLR(GPIO_C_NUM, 2);
        SPIX_BUF(SPI_DEFAULT_INSTANCE) = send;
        SPIX_WAITFOREOTx(SPI_DEFAULT_INSTANCE);
        SPI_CS_SET(GPIO_C_NUM, 2);

        // Delay to make sure the slave is ready
        clock_delay_usec(10);

        // Write a dummy packet, receive data
        SPIX_WAITFORTxREADY(SPI_DEFAULT_INSTANCE);
        SPI_CS_CLR(GPIO_C_NUM, 2);
        SPIX_BUF(SPI_DEFAULT_INSTANCE) = 42;
        SPIX_WAITFOREOTx(SPI_DEFAULT_INSTANCE);
        SPI_CS_SET(GPIO_C_NUM, 2);

        // Delay to make sure the slave is ready
        clock_delay_usec(10);

        recv = SPIX_BUF(SPI_DEFAULT_INSTANCE);
        recv = SPIX_BUF(SPI_DEFAULT_INSTANCE);

        if(recv == 2) {
            leds_on(LEDS_RED);
            leds_off(LEDS_GREEN);
            leds_off(LEDS_BLUE);
        } else if(recv == 4) {
            leds_off(LEDS_RED);
            leds_on(LEDS_GREEN);
            leds_off(LEDS_BLUE);
        } else if(recv == 6) {
            leds_off(LEDS_RED);
            leds_off(LEDS_GREEN);
            leds_on(LEDS_BLUE);
        } else {
            leds_off(LEDS_RED);
            leds_off(LEDS_GREEN);
            leds_off(LEDS_BLUE);
        }

        send++;
        if(send > 3) {
            send = 1;
        }

        etimer_restart(&periodic_timer);
    }
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
