/*
 * DA_2A_C.c
 *
 * Created: 3/4/2019 9:00:33 PM
 * Author : Eric Smith
 (ATMEGA328P XPLAINED MINI BOARD WOULD NOT HOOK UP WITH ATMEL STUDIO 7, POSSIBLY BROKEN)
 */ 
#define F_CPU 16000000UL // CLOCK WILL RUN AT 16MHz

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// SETTING PORTB AS OUTPUT 
	DDRB |= (1 << 2);
	PORTB |= (1 << 2);
	
	// SETTING PORTC AS INPUT
	DDRC &= (0 << 2);
	PORTC |= (1 << 2); // PULL-UP ENABLED (TURN ON THE PULL UP TRANSISTOR)
	
    while (1) 
    {
		if (!(PINC & (1 << PINC))) // CHECKING FOR COMPLIMENT SITUATION AND IF PINC IS HIGH 
		{
			PORTB &= ~(1 << 2); // LED WILL TURN ON DUE TO 'ZERO' BEING SENT 
			_delay_ms(1250); // CREATES THE 1.25 SECOND DELAY 
		}
			else
				PORTB |= (1 << 2); // PORTB2 STAYS HIGH
    }
				return 0;
}

