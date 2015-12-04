#include "spi_wrapper.h"
#include "spi-arch.h"
#include "dev/spi.h"
#include "gpio.h"

// Defines which pin to use for SPI CS
#define CS_PORT_NUM GPIO_C_NUM
#define CS_PIN_NUM 2

// Defines for the opcodes of each command
#define BODY_CONTROL_OP  0x0001
#define GIMBAL_POS_OP    0x0002
#define HAPTIC_TORQUE_OP 0x0003
#define ENCODER_POS_OP   0x0004
#define BODY_MOTORS_OP   0x0005

// Defines how many microseconds to wait between SPI frames
#define INTER_FRAME_DELAY 10

void spi_wrapper_init() {
    spix_init(SPI_DEFAULT_INSTANCE);
    spix_set_mode(SPI_DEFAULT_INSTANCE, SSI_CR0_FRF_MOTOROLA, 0, 0, 16);
    spix_cs_init(CS_PORT_NUM, CS_PIN_NUM);

    SPIX_FLUSH(SPI_DEFAULT_INSTANCE);
}

uint16_t spi_wrapper_txrx_word(uint16_t tx_word) {
    // Wait until the SPI peripheral is ready
    SPIX_WAITFORTxREADY(SPI_DEFAULT_INSTANCE);

    // Set the CS low to enable the C2000's SPI
    SPI_CS_CLR(GPIO_C_NUM, 2);

    // Write the data to send into the SPI TX FIFO
    SPIX_BUF(SPI_DEFAULT_INSTANCE) = tx_word;

    // Wait for the transfer to complete
    SPIX_WAITFOREOTx(SPI_DEFAULT_INSTANCE);

    // Set the CS high to disable the C2000's SPI
    SPI_CS_SET(GPIO_C_NUM, 2);

    // Delay to make sure there's enough time for the
    // C2000 to process this frame before the next one
    clock_delay_usec(INTER_FRAME_DELAY);

    // Read the word that the C2000 sent out of the SPI RX FIFO
    uint16_t rx_word = SPIX_BUF(SPI_DEFAULT_INSTANCE);

    // Return that word
    return rx_word;
}

void spi_wrapper_send_body_control(uint16_t direction, uint8_t speed) {
    // Send a header indicating that the Atum is sending body control data
    spi_wrapper_txrx_word(BODY_CONTROL_OP);

    // Send the direction
    spi_wrapper_txrx_word(direction);

    // Send the speed
    spi_wrapper_txrx_word((uint16_t)speed);
}

void spi_wrapper_send_gimbal_pos(uint16_t position) {
    // Send a header indicating that the Atum is sending gimbal position data
    spi_wrapper_txrx_word(GIMBAL_POS_OP);

    // Send the desired position
    spi_wrapper_txrx_word(position);
}

void spi_wrapper_send_haptic_torque(uint16_t torque) {
    // Send a header indicating that the Atum is sending haptic torque data
    spi_wrapper_txrx_word(HAPTIC_TORQUE_OP);

    // Send the desired torque
    spi_wrapper_txrx_word(torque);
}

uint16_t spi_wrapper_get_encoder_pos() {
    // Send a header indicating that the Atum is requesting the encoder position
    spi_wrapper_txrx_word(ENCODER_POS_OP);

    // Get the encoder position from the C2000
    return spi_wrapper_txrx_word(0xFFFF);
}

body_motor_torques_t spi_wrapper_get_body_motor_torques() {
    body_motor_torques_t body_motor_torques;

    // Send a header indicating that the Atum is requesting the body motor torques
    spi_wrapper_txrx_word(BODY_MOTORS_OP);

    // Read back the torque of motor 1
    body_motor_torques.motor_1 = spi_wrapper_txrx_word(0xFFFF);

    // Read back the torque of motor 2
    body_motor_torques.motor_2 = spi_wrapper_txrx_word(0xFFFF);

    // Read back the torque of motor 3
    body_motor_torques.motor_3 = spi_wrapper_txrx_word(0xFFFF);

    return body_motor_torques;
}

