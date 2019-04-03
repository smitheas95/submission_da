/*
 * DA_3B_T1.c
 *
 * Created: 3/31/2019 9:35:23 AM
 * Author : ERIC SMITH
 
 The goal of the assignment is to modify the above codes to do the following:
 1. Write a C AVR program that will monitor the LM34/35 connected to an Analog pin
 (PC5) to display the temperature in F on the serial terminal every 1 sec. Use a timer
 with interrupt for the 1 sec delay. Use a FTDI chip for serial to USB conversion.
 2. Use the ATMEL Studio Data Visualizer or any Charting program to display the values
 in time.
 */ 

#define F_CPU 16000000UL // 16 MHz 
#define BAUDRATE 9600 // SET BAUD RATE 9600 
#define BAUD_PRESCALLER ((((F_CPU / BAUDRATE * 16UL)))-1) // BAUD PRESCALER 

// LIBRARY 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void read_adc(void); // Function Declarations
void adc_init(void);
void USART_init( unsigned int ubrr );
void USART_tx_string( char *data ); 

volatile unsigned int adc_temp;
char outs[20]; // ARRAY 

int main(void) {
	adc_init(); // INITIALIZE ADC )
	USART_init(BAUD_PRESCALLER); // INITIALIZE USART 
	USART_tx_string("Connected!\r\n"); 
	_delay_ms(125); // WAIT PERIOD 
	
	while(1) // WHILE LOOP 
	{
		read_adc();
		_delay_ms(1000); // WAIT PERIOD 
	}
}
void adc_init(void)
{
	// SET UP AND ENABLE ADC 
	ADMUX = (0<<REFS1)| // REFERENCE SELECTION BITS 
	(1<<REFS0)| // AVcc - external cap at AREF
	(0<<ADLAR)| // ADC Left Adjust 
	// SET FOR PC5 
	(1<<MUX2)| // ANALOG CHANNEL SELECTION BITS 
	(0<<MUX1)| 
	(1<<MUX0);
	
	ADCSRA = (1<<ADEN)| // ADC ENABLE 
	(0<<ADSC)| // ADC Start Conversion
	(0<<ADATE)| // ADC AUTO TRIGGER ENABLE 
	(0<<ADIF)| // ADC INTERRUPT FLAG 
	(0<<ADIE)| // ADC INTERRUPT ENABLE 
	(1<<ADPS2)| // ADC PRESCALER SELECT BITS 
	(0<<ADPS1)|
	(1<<ADPS0);
	
	// USING TIMER1 
	TIMSK1 = (1<<TOIE1); // ENABLE OVERFLOW INTERRUPT 
	TCCR1B |= (1<<CS11)|(1<<CS10); // PRESCALER 
	TCNT1 = 49911; // CALCULATED/NEEDED VALUE 
}
/* READ ADC PINS */
// METHOD 
void read_adc(void)
{
	unsigned char i =4;
	adc_temp = 0;
	while (i--) {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		adc_temp+= ADC;
		_delay_ms(50);
	}
	adc_temp = adc_temp / 4; // AVG. FEW SAMPLES 
	int tempf= (adc_temp*5*100)/1024;
	snprintf(outs,sizeof(outs),"%3d\r\n", tempf); // KEY PRINT FUNCTION 
	USART_tx_string(outs);
}
void USART_init( unsigned int ubrr ) {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0); // ENABLE RECEIVER, TRANSMITTER & RX INTERRUPT 
	UCSR0C = (3 << UCSZ00); // ASYNCHRONOUS 
}
/* SEND A STRING TO THE RS-232 */
void USART_tx_string( char *data ) {
	while ((*data != '\0')) {
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}
	
	ISR(TIMER1_OVF_vect)
	{
		read_adc(); // ADC FUNCTION CALLED 
		snprintf(outs,sizeof(outs), "%3d\r\n", adc_temp); // KEY PRINT FUNCTION 
		USART_tx_string(outs); // STRING OUTPUT 
		_delay_ms(1000);
		TCNT1 = 49911; // TIMER COUNTER RESET 
	}
	

