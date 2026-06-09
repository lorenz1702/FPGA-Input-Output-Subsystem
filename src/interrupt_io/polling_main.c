#include <xio.h>
#include <string.h>
#include "xparameters.h"

// TODO: Define the UART_BASE_ADDRESS.
#define UART_BASE_ADDRESS XPAR_MDM_1_BASEADDR

#define UART_RX_FIFO 	0x00
#define UART_TX_FIFO 	0x04
#define UART_STATUS  	0x08
#define UART_CTRL		0x0C
// Read -- Check Full -- Write Xx

// Register RX TX STATUS CFG

// TODO: Define the UART register offset. Hint: Look for the register map in the product guide
#define UART_STATUS_TX_EMPT (1<<2)
#define UART_STATUS_TX_FULL (1<<3)

// TODO: Define the bit masks for the appropriate status flags. Hint: Look for the status registers in the product guide

u8 is_full(){
	return XIo_In32(UART_BASE_ADDRESS + UART_STATUS) & 0b1000;
}

u8 is_empty()
{
	return (XIo_In32(UART_BASE_ADDRESS + UART_STATUS) & 0b1) ^ 0b1;
}

void print(char *s) {
	// TODO: Write C code to transmit the string using UART.
	for(int i=0; i<strlen(s); i++)
	{
		while(is_full())
		{
			;
		}
		XIo_Out32(UART_BASE_ADDRESS + UART_TX_FIFO, s[i]);
	}



}

// XIo_In32 for input

int main(void) {
	u32 status = 0;
	printf("hello");
	char s[] = "Hello World, this is a demonstrator application for polled io!\r\n";

	print(s);

	while(1) {
		// TODO: Write C code to echo received characters.
		while(is_empty()){
			;
		}
 		u8 value = XIo_In32(UART_BASE_ADDRESS + UART_RX_FIFO);
		XIo_Out32(UART_BASE_ADDRESS + UART_TX_FIFO, value);
	}

	// Exit normally
	return 0;
}

// Lab goals
// 1. output
// 2. Echo --> Write in console, Receive MSg and write back
