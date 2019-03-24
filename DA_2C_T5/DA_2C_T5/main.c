/*
 * DA_2C_T5.c
 *
 * Created: 3/24/2019 11:04:02 AM
 * Author : ERIC SMITH 
 */ 

#define F_CPU16000000UL      
#include <avr/io.h>          
#include <avr/interrupt.h>   
#include <util/delay.h>      
#define LED 
uint8_t OVFCount=0;         

int main(void)
{
	DDRB |= (1<<DDB2);  // PB2 SET AS OUTPUT
	TIMSK0 |= (1<< TOIE0);
	TCNT0=0;  // COUNTER 
	
	sei(); // INTERRUPTS ENABLED 

	TCCR0A = 0; // 
	TCCR0B |= (1<< CS02) | (1<<CS00); // PRESCALAR SET AT 1024

	while(1)
	{
	}
}

ISR (TIMER0_OVF_vect)
{
	while (1)
	{
		TOP:
		OVFCount=0;
		
		if (!(PINC & (1<<PINC1)))
		{
			while(1)
			{
				while((TIFR0 & 0X01) == 0); // OVERFLOW FLAG
				TCNT0 = 0x00;
				TIFR0 = 0x01; // TIME OVERFLOW FLAG CLEARED 
				OVFCount++; // COUNT 
				
				if(OVFCount <= 100) // MEET DESIRED TIME TO BE ON 
				{
					PORTB = (0 << 2);
				}
				else{
					PORTB = (1 << 2);
					goto TOP;
				}
			}

		}
	}
}

