/* i2c test yo
 * -----------
 * Reads registers 0x00 - 0x04, prints over serial
 *
 */
#define BNO_ADDR 0x28

#include "contiki.h"
#include "random.h"
#include "i2c.h"

#include "dev/leds.h"

#include <stdio.h>
/*---------------------------------------------------------------------------*/
PROCESS(i2c_test_process, "I2C example");
AUTOSTART_PROCESSES(&i2c_test_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(i2c_test_process, ev, data)
{
  static struct etimer et;

  //PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  //i2c initialization
  i2c_init(I2C_SDA_PORT, I2C_SDA_PIN, I2C_SCL_PORT, I2C_SCL_PIN, I2C_SCL_FAST_BUS_SPEED);
  i2c_master_enable();
  static uint8_t rcv_buf;
  static uint8_t snd_buf = 0x00;

  while(1) { 
    /* Delay 1 second */
    etimer_set(&et, CLOCK_SECOND * 1);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));

    leds_toggle(LEDS_RED);
    i2c_single_send(BNO_ADDR, snd_buf);
    i2c_single_receive(BNO_ADDR, &rcv_buf);
    printf("%x: %x\n", snd_buf, rcv_buf);
    snd_buf++;
    if(snd_buf > 4) snd_buf = 0;
  }

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
