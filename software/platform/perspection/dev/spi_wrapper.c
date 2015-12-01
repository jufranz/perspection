#include "spi_wrapper.h"
#include "spi-arch.h"
#include "dev/spi.h"
#include "gpio.h"

#define CS_port GPIO_B_NUM
#define CS_pin 4


void spi_wrapper_init(){
    //spi-initialization
    spi_init();
    spix_set_mode(0, SSI_CR0_FRF_MOTOROLA, 0, 0, 16);
    //I SET THE CS PIN TO B4, THIS CAN BE CHANGED TO WHATEVER IS REQUIRED
    spix_cs_init(CS_port, CS_pin);
} //end of spi_wrapper_init

unsigned short spi_TxRx(unsigned short data){
    unsigned short ret_data = 0;
    SPI_CS_CLR(CS_port, CS_pin);
    SPI_WRITE(num_msg);
    SPI_READ(ret_data);
    SPI_CS_SET(CS_port, CS_pin);  
    return ret_data;
}

void spi_wrapper_TxRx(void* input, unsigned short size, 
                        unsigned short *num_rcv, unsigned short *rbuff){
    //the number of messages we need to send
    unsigned short num_snd = size/16 + 1;
    unsigned int i = 0, j = 0;
    unsigned short sdata = 0;
    unsigned short dummy = 0;

    //send a message to the slave with the size of our data
    //get the number of shorts we want to get back
    *num_rcv = spi_TxRx(num_msg);

    //generate a dynamic array to dump the received data into
    rbuff = (unsigned short*) malloc(*num_rcv);

    for(i = 0, j = 0; (i < num_snd) || (j < *num_rcv); i++, j++){
        
        if(i < num_snd)
            data = 0xFF & (input >> (i*16));
        else
            data = 0xFF; //dummy data

        if( j < *num_rcv)
            rbuff[j] = spi_TxRx(sdata);
        else
            dummy = spi_TxRx(sdata);
    }

    return;

    //do some stuff to cast this to whatever data type you want to recieve the data in

} //end of spi_wrapper_send
