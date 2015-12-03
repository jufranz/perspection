#include "contiki.h"
#include "random.h"
#include "spi-arch.h"
#include "dev/spi.h"
#include "dev/ioc.h"
#include "dev/leds.h"
#include "sys/etimer.h"
#include "sys/clock.h"
#include "gpio.h"

/*#define SPI0_CPRS_CPSDVSR 8*/
#define NUM_TRANSACTIONS 100000

#include <stdio.h>

static struct etimer periodic_timer;

/*---------------------------------------------------------------------------*/
PROCESS(spi_test_process, "spi example");
AUTOSTART_PROCESSES(&spi_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(spi_test_process, ev, data)
{
  PROCESS_BEGIN();

  etimer_set(&periodic_timer, CLOCK_SECOND / 10);

  // SPI init
  spix_init(SPI_DEFAULT_INSTANCE);
  spix_set_mode(SPI_DEFAULT_INSTANCE, SSI_CR0_FRF_MOTOROLA, 0, 0, 16);
  spix_cs_init(GPIO_C_NUM, 2);

  static uint16_t send = 0;
  static uint16_t recv = 0;
  static uint32_t totalTransactions = 0;
  static uint32_t totalFailures = 0;

  while(1) {
    /*PROCESS_YIELD();*/

    /*if (etimer_expired(&periodic_timer)) {*/
        // Write some real data, read some dummy data
        SPIX_WAITFORTxREADY(SPI_DEFAULT_INSTANCE);
        SPI_CS_CLR(GPIO_C_NUM, 2);
        SPIX_BUF(SPI_DEFAULT_INSTANCE) = send;
        SPIX_WAITFOREOTx(SPI_DEFAULT_INSTANCE);
        SPI_CS_SET(GPIO_C_NUM, 2);

        // Delay to make sure the slave is ready
        clock_delay_usec(10);

        // Flush the receive buffer
        SPIX_FLUSH(SPI_DEFAULT_INSTANCE);

        // Write a dummy packet, receive data
        SPIX_WAITFORTxREADY(SPI_DEFAULT_INSTANCE);
        SPI_CS_CLR(GPIO_C_NUM, 2);
        SPIX_BUF(SPI_DEFAULT_INSTANCE) = 0xFFFF;
        SPIX_WAITFOREOTx(SPI_DEFAULT_INSTANCE);
        SPI_CS_SET(GPIO_C_NUM, 2);

        // Delay to make sure the slave is ready
        clock_delay_usec(10);

        // Read the data from the C2000 and check it
        recv = SPIX_BUF(SPI_DEFAULT_INSTANCE);

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
            printf("%d transactions with %d errors\r\n", totalTransactions, totalFailures);
            totalTransactions = 0;
            totalFailures = 0;
        }

        /*etimer_restart(&periodic_timer);*/
    /*}*/
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
