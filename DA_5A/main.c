/*
 * DA_5A.c
 *
 * Created: 4/27/2019 9:19:57 PM
 * Author : Eric Smith
 
 Interface the provided NRF24L01+ RF Module to the ATmega328p using the SPI
 interface. Using the earlier developed code for ADC, transmit the ADC value of the
 internal temperature sensor, or LM35 sensor between two RF Modules. The
 ATmega328p interfacing the RF Modules should alternate between TX and RX modes
 every 0.5 secs (hopefully they are not both at TX and RX modes in the same interval).
 The temperature of both ATmega328p’s should be displayed on both ATmega328p’s.
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

// NEDDED LIBRARIES 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// SET UP UART FOR PRINTF(); 
#ifndef BAUD
#define BAUD 9600
#endif
#include "inctest/STDIO_UART.h"

// NRF24L01+ LIBRARY INCLUDED 
#include "inctest/nrf24l01.h"
#include "inctest/nrf24l01-mnemonics.h"
#include "inctest/spi.h"


// IRQ ISR
volatile bool message_received = false;
volatile bool status = false;

// CLICHE MESSAGE TO SEND
char tx_message[32]; // ARRAY STRING DEFINED 

int main(void)
{
	strcpy(tx_message, " Hi, This message is from Eric Smith!"); // COPY STRING INTO ARRAY 
	// UART INITIALIZED 
	uart_init();
	
	// Initialize nRF24L01+ and print configuration info
	nrf24_init();
	
	// PRINT_CONFIGU(); 
	// BEGIN LISTENING TO INCOMING MESSAGES 
	nrf24_start_listening();
	status = nrf24_send_message(tx_message);
	if (status == true)
	{
		printf("Connection Established\n");
	}
	while(1)
	{
		if(message_received)
		{
			// MESSAGE TO BE RECEIVED, PRINT IT
			message_received = false; // Reset to false
			printf("Received Temperature: %s\n", nrf24_read_message());
			// RESPONSE AS A MESSAGE 
			_delay_ms(500);
			// PERFORM ADC EXECUTION, STORE IN TX_MESSAGE 
			status = nrf24_send_message(tx_message);
			if(status == true)
			{
				printf("Temperature Transmitted\n");
			}
		}
	}
}

// IRQ pin INTERRUPT 
ISR(INT0_vect)
{
	message_received = true;
}




