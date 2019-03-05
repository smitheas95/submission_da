/*
 * DA_2A_C.c
 *
 * Created: 3/4/2019 8:44:34 PM
 * Author : Eric Smith
 (ATMEGA328P XPLAINED MINI BOARD WOULD NOT HOOK UP WITH ATMEL STUDIO 7, POSSIBLY BROKEN)
 */ 

#define F_CPU 16000000UL // NOTE THAT CLOCK WILL RUN AT 16MHz

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRB = 0x04; // PORTB SET AS OUTPUT
	
	while(1) // INFINITE LOOP
	{
		PORTB = (1 << 2); // PB2 SET HIGH
		_delay_ms(435); // REPRESENTS TIME THAT LED IS ON DUE TO 0.725 * THE 60% DC
		
		PORTB = (1 << 2); // OUTPUT DISPLAY 
		_delay_ms(290); // TIME THAT LED IS ON DUE TO 0.725 - 0.435 (REPRESENTS 40% DC)
	}
		return 0;
	
}

