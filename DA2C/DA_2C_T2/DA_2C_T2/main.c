/*
 * DA_2C_T2.c
 *
 * Created: 3/24/2019 5:37:50 AM
 * Author : eas7w
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int count;

int main(void)
{
    count = 0; // COUNT IS INITIALIZED  
	DDRB |= (1 << 2); // CONNECTION OF LED TO PIN B2
	
	// NORMAL MODE & TIMER0 WITH PRESCALER OF 64
	TCCR0A = 0;
	TCCR0B |= (1 << CS00) | (1 << CS01);
	
	TCNT0 = 0; // TIME COUNTER INITIALIZATION
	TIMSK0 |= (1 << TOIE0); // OVERFLOW INTERRUPT ENABLED 
	sei(); // GLOBAL INTERRUPT ENABLED 
	
    while (1); // INFINITE LOOP
    
}

ISR (TIMER0_OVF_vect) // INTERRUPT SERVICE ROUTINE 
{
	if (count == 20)
	{
		PORTB ^= (1 << 2); // TOGGLE PIN B5
		count = 0; // COUNT REINITIALIZED 
	}
			else
			count++; // INCREMENT COUNT 
			
}

