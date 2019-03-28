/*
 * DA_3A_T1.c
 *
 * Created: 3/27/2019 6:25:30 PM
 * Author : ERIC SMITH
 */ 

#define F_CPU 8000000UL // 8MHz

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUDRATE 9600 // DEFINITION REGARDING BAUDRATE 
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1) // CONFIRMATION OF BAUDRATE PRESCALER 

volatile int Count; // ESTABLISHMENT OF INTEGER COUNT NEEDED

int n; // VARIABLE N INTEGER
float PI; // FLOAT PI REPRESENTATION 
char outs[30]; // CHARACTER ARRAY USED TO STORE RESPECTIVE AMOUNT 
char str[] = "UNLV IS THE BEST"; // STRING TO BE DISPLAYED
char empty[] = " "; // EMPTY STRING FOR SPACE 

void USART_init( unsigned int ubrr ); // VOID FUNCTION
void USART_TX_string(char *data); // VOID FUNCTION 

int main(void)
{
	Count = 0; // COUNT SET AT ZERO 
	
	USART_init(BAUD_PRESCALLER); // FOR USART, SETS BAUD PRESCALER 
	USART_TX_string("Connected!\r\n"); // FOR USART, SETS TEXT STRING 
	TIMSK0 |= (1 << TOIE0); // SETS INTERRUPT ACTIVATION 
	sei(); // ENABLES GLOBAL INTERRUPT 
	TCCR0A = 0x00; // NORMAL MODE REGARDING TIMER
	TCCR0B = 0x05; 
	
	while(1);
}

void USART_TX_string(char *data) // VOID FUNCTION FOR STRING 
{
	
	while (*data != '\0') {
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = *data;
		data++;
		
	}
}

	void USART_init(unsigned int ubrr // VOID FUNCTION FOR USART_INIT
	{
		
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0); // INTERRUPT FOR TX ENABLED 
	UCSR0C = (3 << UCSZ00); // ASYNCHRONOUS  
	
	}

	ISR (TIMER0_OVF_vect) // FLAG INTERRUPT FOR TV0V
	{
		
	while (Count < 61) // LOOP WHEN LESS THAN 61
	{
		if ((TIFR0 & 0x01)  == 1)
		{
			TIFR0 = 0x01;
			Count++;
		}
	}
	
     if (Count > 60) // PERFORM/EXECUTE WHEN COUNT GREATER THAN 60
	 {
		 USART_TX_string(str); // PRINT STRING 
		 USART_TX_string(empty); // BLANK SPACE PRINTED 
		 
		 n = rand(); // RANDOM NUMBER GENERATED 
		 PI = 3.1415; // CHOSE PI
		 
		dtostrf(PI, 6, 6, outs); // DOUBLE VALUE PASSED IS CONVERTED IN VAL INTO ASCII REPRESENTATION TO BE STORED UNDER S 
		USART_TX_string(outs); 
		USART_TX_string(empty);
		
		snprintf(outs, sizeof(outs), "%5d\r\n"); // CONVERTS FLOATING VALUE 
		
		USART_TX_string(outs); // WRITES STRING 
		USART_TX_string(empty);
		USART_TX_string(str); 
		USART_TX_string(empty); // BLANK SPACE TO SERIAL 
		
		Count = 0; // RESETS COUNTER 
	}
	}
	