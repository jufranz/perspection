#ifndef SPI_WRAPPER_H_
#define SPI_WRAPPER_H_

#include "contiki.h"

// A struct to hold the body motor torques
typedef struct {
    uint16_t motor_1;
    uint16_t motor_2;
    uint16_t motor_3;
} body_motor_torques_t;

// Initializes the SPI wrapper
void spi_wrapper_init();

// Sends a 16-bit word and receives a 16-bit word
uint16_t spi_wrapper_txrx_word(uint16_t tx_word);

// Sends a robot body control command to the C2000
void spi_wrapper_send_body_control(uint16_t direction, uint8_t speed);

// Sends a gimbal position command to the C2000
void spi_wrapper_send_gimbal_pos(uint16_t position);

// Sends a haptic torque command to the C2000
void spi_wrapper_send_haptic_torque(uint16_t torque);

// Retrieves the encoder position from the C2000
uint16_t spi_wrapper_get_encoder_pos();

// Retrieves the torques on each robot body motor from the C2000
body_motor_torques_t spi_wrapper_get_body_motor_torques();

#endif
