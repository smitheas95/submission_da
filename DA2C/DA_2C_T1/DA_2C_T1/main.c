/*
 * DA_2C_T1.c
 *
 * Created: 3/24/2019 4:46:43 AM
 * Author : eas7w
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    unsigned char count = 0; // COUNT FOR KEEPING TRACK OF TIMER0
	DDRB |= (1 << 2); // CONNECTION OF LED TO PIN B2
	PORTB = 0; // PIN B2 LED OFF 
	
	// NORMAL MODE & TIMER0 WITH PRESCALER 64
	while (1) 
		TCCR0A = 0;
		TCCR0B |= (1 << CS01) | (1 << CS00);
		
		TCNT0 = 0; // COUNTER INITIALIZATION 
		
		while ( ( TIFR0 & 0x1) == 0) // WAIT FOR OVERFLOW FLAG
		TCCR0B = 0; // DISABLE TIMER0
		TIFR0 |= 1; // CLR OVERFLOW FLAG 
	
		if (count == 20)
		{
			PORTB ^= 0x04; // TOGGLE PIN B2 
			count = 0; // RESET COUNTER 
		}
			else
			count++; // INCREMENT COUNTER 
	}
