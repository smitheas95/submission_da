/*
 * DA_2C_T3.c
 *
 * Created: 3/24/2019 11:00:45 AM
 * Author : ERIC SMITH 
 * TIMER0 - CTC MODE 
 */ 

#define F_CPU16000000UL      
#include <avr/io.h>          
#include <avr/interrupt.h>   
#include <util/delay.h>      
#define LED 2
uint8_t OVFCount=0; // COUNTER OVERFLOW HOLDS VARIABLE 


int main(void)
{
	DDRB |= (1<<DDB2);  // PD6 SET AS OUTPUT
	TCNT0 = 0;  // TIME COUNTER SET AT ZERO
	OCR0A = 128; // OUTPUT COMPARE REGISTER
	TCCR0A |= (1 << WGM21); // SET TO CTC MODE
	TIMSK0 |= (1 << OCIE2A); // COMPARE MATCH 
	TCCR0B |= (1 << CS02) | (1 << CS00); // PRESCALAR SET AT 1024

	sei(); // ENABLE INTERRUPTS

	while(1)
	{
	}
}

ISR (TIMER0_COMPA_vect)
{
	while ((TIFR0 & 0x02) == 0);
	TIFR0 = 0x02; // CLEAR TIMER0 COMPARE OVERFLOW FLAG
	OVFCount++; // COUNT 
	
	if (OVFCount <= 27)  // MEET DESIRED TIME TO BE ON 
	{
		PORTB = (0 << LED);
	}
	else
	PORTB = (1<<LED);

	if (OVFCount == 45) // MEET DESIRED TIME TO BE OFF 
	{
		
		OVFCount=0;
	}
}


