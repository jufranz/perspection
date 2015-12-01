#include "contiki.h"
#include "random.h"
#include "spi-arch.h"
#include "dev/spi.h"
#include "gpio.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(spi_test_process, "spi example");
AUTOSTART_PROCESSES(&spi_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(spi_test_process, ev, data)
{
  static struct etimer et;

  //PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  //spi-initialization
  spi_init();
  spix_set_mode(0, SSI_CR0_FRF_MOTOROLA, 0, 0, 16);
  spix_cs_init(GPIO_B_NUM , 4);
  

  static uint16_t send = 105;

  while(1) { 
    /* Delay 1 second */
    //etimer_set(&et, CLOCK_SECOND * 1);
    //PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));
    SPI_CS_CLR(GPIO_B_NUM, 4);
    SPI_WRITE(send);
    SPI_CS_SET(GPIO_B_NUM, 4);
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
