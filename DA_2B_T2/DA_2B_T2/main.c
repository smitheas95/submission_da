/*
 * DA_2B_T2.c
 * Created: 3/9/2019 3:38:11 PM
 * Author : Eric Smith 
 
 Goal of assignment is to use GPIO Interrupts
 Use INT0 (PD2 pin/LED3) Interrupt mechanism 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
    DDRB |= (1 << DDB2); // DIRECTION IS SET FOR PORTB2 AS OUTPUT 
	PORTB |= (1 << PORTB2); // PULL-UP RESISTOR IS TURNED ON FOR PORTB2
	DDRD &= (0 << DDD2); // DIRECTION IS SET FOR PORTD2 AS INPUT
	PORTD |= (1 << PORTD2); // PULL-UP RESISTOR IS TURNED ON FOR PORTD2
	EICRA = 0x00; // INTERRUPT IS SET/ACTIVATED ON LOW LEVEL
	
	EIMSK = (1 << INT0); // ENABLE EXTERNAL INTERRUPT 
	sei (); // ENABLES GLOBAL INTERRUPT 
	
    while (1); // WAIT HERE FOR INTERRUPT SITUATION 
    }
	
	ISR (INT0_vect) // ISR FOR EXTERNAL INTERRUPT 
	{
		PORTB &= (0 << PORTB2); // LED IS TURNED ON 
		_delay_ms(1250); // 1.25 SECOND DELAY (SAME AS DESIGN ASSIGNMENT 2A TIME DELAY)
		PORTB |= (1 << PORTB2); // LED IS TURNED ON AFTER MANUAL INTERRUPT
	}
	

