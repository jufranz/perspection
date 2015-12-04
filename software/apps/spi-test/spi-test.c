#include "contiki.h"
#include "random.h"
#include "dev/ioc.h"
#include "dev/leds.h"
#include "dev/spi_wrapper.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "gpio.h"

#define NUM_TRANSACTIONS 100000

#include <stdio.h>

/*static struct etimer periodic_timer;*/

/*---------------------------------------------------------------------------*/
PROCESS(spi_test_process, "spi example");
AUTOSTART_PROCESSES(&spi_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(spi_test_process, ev, data)
{
  PROCESS_BEGIN();

  /*etimer_set(&periodic_timer, CLOCK_SECOND / 10);*/

  spi_wrapper_init();

  static uint16_t send = 0;
  static uint16_t recv = 0;
  static uint32_t totalTransactions = 0;
  static uint32_t totalFailures = 0;

  while(1) {
    /*PROCESS_YIELD();*/

    /*if (etimer_expired(&periodic_timer)) {*/
        // Write some real data, read some dummy data
        spi_wrapper_txrx_word(send);
        // Read the data from the C2000 and check it
        recv = spi_wrapper_txrx_word(0xffff);

        /*printf("Sent %d, Got %d\r\n", send, recv);*/

        if(recv == send + 1) {
            // We're good
            leds_off(LEDS_RED);
            leds_on(LEDS_GREEN);
            leds_off(LEDS_BLUE);
        } else {
            // Something messed up
            leds_on(LEDS_RED);
            leds_off(LEDS_GREEN);
            leds_off(LEDS_BLUE);
            totalFailures++;
        }

        // Increment the send data
        send++;
        if(send == 0xFFFF) {
            send = 0;
        }

        // Increment the number of transactions and check if we need to report anything
        totalTransactions++;
        if(totalTransactions == NUM_TRANSACTIONS) {
            printf("%d transactions with %d errors\r\n", (int)totalTransactions, (int)totalFailures);
            totalTransactions = 0;
            totalFailures = 0;
        }

        /*etimer_restart(&periodic_timer);*/
    /*}*/
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
