/*
 * DA_2C_T3.c
 *
 * Created: 3/24/2019 6:08:43 AM
 * Author : eas7w
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


int main(void)
{
    DDRB |= (1 << DDB2); // PB2 AS OUTPUT
	OCR0A = 63; ; // LOAD COMPARE REGISTER
	TCCR0A |= (1 << WGM21); // SET TO CTC MODE
	TIMSK0 |= (1 << OCIE0A); // SET INTERRUPT ON COMPARE MATCH
	TCCR0B |= (1 << CS22); // SET PRESCALER TO 64 AND STARTS PWM
	sei(); // INTERRUPT ENABLED 
	
    while (1) // MAIN LOOP
    {
    }
}
	ISR (TIMER0_COMPA_vect)
{
	PORTB ^= (1 << DDRB2); // OUTPUT DESIRED 
}


