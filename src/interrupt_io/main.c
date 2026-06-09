#include <xio.h>
#include <string.h>
#include "xparameters.h"
#include <mb_interface.h>
// TODO: Define the UART_BASE_ADDRESS.
#define UART_BASE_ADDRESS XPAR_MDM_1_BASEADDR

#define UART_RX_FIFO 	0x00
#define UART_TX_FIFO 	0x04
#define UART_STATUS  	0x08
#define UART_CTRL		0x0C

#define UART_STATUS_RX_VALID 0x01 // Bit 0

// UART CONTROL BITS
#define UART_CTRL_ENABLE_INTERRUPT 0x10
// More information in MicroBlaze product guide!
// void ISR() __attribute__((interrupt_handler));
u32 count=0;


void ISR(void)
{
    // 1. Status-Register read
    u32 status = XIo_In32(UART_BASE_ADDRESS + UART_STATUS);

	// 2. check if interrupt happend do to rx
    if (status & UART_STATUS_RX_VALID) {
        
        // 3. data read
        u8 value = XIo_In32(UART_BASE_ADDRESS + UART_RX_FIFO);
        
        // 4. (optional) data back as echo
        XIo_Out32(UART_BASE_ADDRESS + UART_TX_FIFO, value);
        
        count++;
    }
}

int main(void) {

	// TODO: Enable the UART to generate interrupts
	XIo_Out32(UART_BASE_ADDRESS + UART_CTRL, UART_CTRL_ENABLE_INTERRUPT);
	// TODO: Enable microblaze to respond to interrupts
	microblaze_enable_interrupts();
	microblaze_register_handler(&ISR, nullptr);
	while(1) {

		; // Useful work goes here

	}

	// TODO: Disable Interrupts

	// Exit normally
	return 0;
}
