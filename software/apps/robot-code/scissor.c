#include "contiki.h"
#include "net/rime/rime.h"
#include "random.h"
#include "clock.h"
#include "dev/comms.h"
#include "dev/leds.h"

#include <stdio.h>
#include <stdint.h>

//DIR(PHASE pin of DRV8801) connected to Atum B4
//PWM(ENABLE pin of DRV8801) connected to Atum B3

void set_up_single_driver_gpio(uint32_t gpio_port_base, uint32_t gpio_pin_num);
void set_up_pwm();
void set_duty_cycle(double new_duty_cycle);
void scissorMotorControl(double direction, double speed);

static struct moveData_t recvData;
static void
movement_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
	unpackMoveData(&recvData);
	scissorMotorControl(recvData.sDir, recvData.sSpeed);
	
}

static void
broadcast_recv(struct broadcast_conn *c, const linkaddr_t *from)
{
	if(from->u8[0] == SCISSOR_ADDR_A && from->u8[1] == SCISSOR_ADDR_B)
	{
		movement_recv(c, from);
		return;
	}
}
static const struct broadcast_callbacks broadcast_call = {broadcast_recv};
static struct broadcast_conn broadcast;

PROCESS_THREAD(init_linkaddr_process, ev, data)
{
  PROCESS_BEGIN();

  set_up_single_driver_gpio(B, 3);
  set_up_single_driver_gpio(B,4);

  static linkaddr_t nodeAddr;
  nodeAddr.u8[0] = SCISSOR_ADDR_A;
  nodeAddr.u8[1] = SCISSOR_ADDR_B;
  linkaddr_set_node_addr(&nodeAddr);

  process_start(&init_network_process, NULL);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(init_network_process, ev, data)
{
  PROCESS_EXITHANDLER(broadcast_close(&broadcast);)

  PROCESS_BEGIN();

  initMoveNetwork(&broadcast, &broadcast_call);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/

void set_up_pwm() {
    pwm_gpt2_pwm1_init();
    pwm_gpt2_pwm1_config_gpio(B, 4);
    pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm1_start();

    pwm_gpt2_pwm2_init();
    pwm_gpt2_pwm2_config_gpio(B, 4);
    pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    pwm_gpt2_pwm2_start();

    set_duty_cycle(0.0);
}

void scissorMotorControl(HAL_Handle halHandle, double direction, double speed) {
    double dirInRads = (direction * PI) / 180.0;
    double dutyCycle1 = (speed * cos(((150.0 * PI) / 180.0) - dirInRads));

    uint16_t direction1 = (dutyCycle1 > 0.0) ? 1 : 0;

    dutyCycle1 = (dutyCycle1 < 0.0) ? (dutyCycle1 * -1.0) : dutyCycle1;

    HAL_setHbridge1Direction(halHandle, direction1);
    HAL_setHbridge1PwmDutyCycle(halHandle, dutyCycle1);
}


void set_up_single_driver_gpio(uint32_t gpio_port_num, uint32_t gpio_pin_num) {
    GPIO_SOFTWARE_CONTROL(GPIO_PORT_TO_BASE(gpio_port_num), GPIO_PIN_MASK(gpio_pin_num));
    GPIO_SET_OUTPUT(GPIO_PORT_TO_BASE(gpio_port_num), GPIO_PIN_MASK(gpio_pin_num));
    ioc_set_over(gpio_port_num, gpio_pin_num, IOC_OVERRIDE_OE);
}


void set_duty_cycle(double new_duty_cycle) {
    haptics_duty_cycle = new_duty_cycle;
    if(haptics_duty_cycle < -1.0) {
        haptics_duty_cycle = -1.0;
    } else if(haptics_duty_cycle > 1.0) {
        haptics_duty_cycle = 1.0;
    }

    if(haptics_duty_cycle < 0.0) {
        pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
        pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, -haptics_duty_cycle);
    } else if(haptics_duty_cycle > 0.0) {
        pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, haptics_duty_cycle);
        pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    } else {
        pwm_gpt2_pwm1_set_timing(PWM_PERIOD_MS, 0.0);
        pwm_gpt2_pwm2_set_timing(PWM_PERIOD_MS, 0.0);
    }
}
