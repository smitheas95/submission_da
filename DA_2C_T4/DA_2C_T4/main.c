/*
 * DA_2C_T4.c
 *
 * Created: 3/24/2019 11:02:13 AM
 * Author : ERIC SMITH
 * SWITCH 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
uint8_t OVFCount= 0; // OVERFLOW COUNTER

int main(void)
{
	
	TCCR0B = (1 << CS02)|(1 << CS00); // PRESCALAR SET AT 1024
	DDRB |= (1 << 2);  // SET PORT B AS OUTPUT
	PORTB |= (1 << 2);  // PORTB2 AS OUTPUT 
	DDRC &= (0<<2);  // SET PINC C AS INPUT
	PORTC |= (1<<2);  
	
	// 1.25 SECONDS  
    while (1) 
    {
	TOP: // LABEL 
	  OVFCount = 0;
	 
	  if (!(PINC & (1  <<PINC1)))
	  { 
		while(1)
	{
	while((TIFR0 & 0X01)==0); // OVERFLOW FLAG SITUATION 
	
	TCNT0 = 0X00;
	TIFR0 = 0X01; // TIME OVERFLOW FLAG CLEARED 
	OVFCount++; // COUNT INCREMENT 
	
	if(OVFCount<=100)          //MEET DESIRED TIME TO BE ON 
	{
	PORTB = (0 << 2);
	}
	else{
		
	PORTB=(1<<2);
	
	goto TOP;
	}
	}
		}
	
	}
		return 0;
	} 

