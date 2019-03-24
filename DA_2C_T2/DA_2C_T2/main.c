/*
 * DA_2C_T2.c
 *
 * Created: 3/24/2019 10:58:34 AM
 * Author : ERIC SMITH
 * TIMER0 - OVF_VECT
 */ 

#define F_CPU16000000UL 
#include <avr/io.h>          
#include <avr/interrupt.h>   
#include <util/delay.h>      
#define LED 
uint8_t OVFCount=0;  // COUNTER OVERFLOW HOLDS VARIABLE 


int main(void)
{
	DDRB |= (1<<DDB2);  // PB2 SET AS OUTPUT
	TIMSK0 |= (1<< TOIE0);
	TCNT0=0; // TIME COUNTER SET TO ZERO
	
	sei(); // ENABLE INTERRUPTS

	TCCR0A = 0; // NORMAL MODE SET 
	TCCR0B |= (1<< CS02) | (1<<CS00); // PRESCALAR SET AT 1024
	
	while(1)
	{

	}
}

ISR (TIMER0_OVF_vect) 
{
	while ((TIFR0 & 0x01)==0);
	TIFR0 = 0x01; //TIMER0 COMPARE OVERFLOW FLAG CLEARED 
	
	OVFCount++; // COUNT 
	
	if (OVFCount <= 14) // MEET DESIRED TIME ON 
	{
		PORTB = (0 << LED);
	}
	else
	PORTB=(1<<LED);
	
	if(OVFCount == 23) // MEET DESIRED TIME OFF 
	{
		OVFCount=0;
	}
}


