#ifndef ATUM_PWM_H_
#define ATUM_PWM_H_
/*HOW THIS SHIT IS GOING TO WORK
		THIS SHIT WORKS BY INPUTTING A DATA TYPE OF ANY DATATYPE BETWEEN 0 AND 64 BITS AND SIZE 
	IN BITS TO THE SEND FUNCTION. THE FUNCTION WILL THEN BREAK THIS INPUTTED DATA INTO 
	16 BIT CHUNKS AND SEND EACH CHUNK ONE BY ONE UNTIL IT'S DONE. THE FIRST 16 BIT 
	MESSAGE THAT IS SENT WILL TELL THE SLAVE HOW MANY CHUNKS IT NEEDS TO WAIT FOR.

	THE RECIEVER SIDE OF THIS FUNCTION WON'T RETURN UNTIL ALL THE BITS HAVE BEEN SENT OVER,
	SO THE RECIEVER USER WILL JUST HAVE TO RECIEVE.
*/



//call this before your main loop
//sets up to run with 16 bit messages, 0 phase, 0 polarity, active on high
void spi_wrapper_init();

/*
This function sends and receives data back over SPI to a slave
	input: the data structure you want to send over
	size: the size of that data structure
	num_rcv: the number of 16 bit chunks received
	rbuff: a unsigned short buffer for reading in a data structure from the slave
	
	NOTE: Each chunk is 2 BYTES (16 bits) NOT 1 (8 bits)
	WARNING: YOU WILL NEED TO FREE RBUFF AFTER YOU ARE DONE CASTING IT TO WHATEVER 
		YOU CASTED IT TO. DYNAMIC MEMORY WAS ALLOCATED FOR IT
*/
void spi_wrapper_TxRx(void* input, unsigned short size, 
                        unsigned short *num_rcv, unsigned short *rbuff);


}


#endif
