/*
 * DA_2C_T1.c
 *
 * Created: 3/24/2019 10:53:22 AM
 * Author : ERIC SMITH
 * NORMAL MODE - TIMER0 - 60% DUTY CYCLE 
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LED 

int main()
{
	uint8_t OVFCount= 0;

	DDRB |= 1 << LED; // PORTB2 CONFIGURATION 
	TCNT0 = 0x00; 
	
	
	TCCR0B=(1<<CS02)|(1<<CS00); // PRESCALAR SET UP FOR  1024

	while(1)
	{
		while((TIFR0 & 0x01) == 0); // FLAG FOR OVERFLOW 
		TCNT0=  0x00;
		TIFR0 = 0x01; // OVERFLOW FLAG CLEAR SITUATION 
		OVFCount++; 
		
		if (OVFCount <= 27) // MEET DESIRED TIME TO STAY ON 
		{
			PORTB= (0 << LED);
		}
		else
		PORTB=(1 << LED);
		
		if(OVFCount == 45) // MEET DESIRED TIME TO BE OFF  
		{
			OVFCount = 0;
		}
	}
	return 0;
}


