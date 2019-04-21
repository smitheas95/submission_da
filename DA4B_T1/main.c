/*
 * DA4B_T1.c
 *
 * Created: 4/21/2019 12:37:30 AM
 * Author : ERIC SMITH 
 
 1. Write an AVR C program to control the speed of the Stepper Motor using a
 potentiometer connected to PC0. Use a timer in CTC mode to control the delay.
 */ 

#define F_CPU 16000000UL

// NEEDED LIBRARIES 
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void read_adc(void); 
void adc_init(void);


volatile int OVFCOUNT; 
volatile int RPMVALUE;
volatile double	float_value;
volatile unsigned int adc_value;

int start_value = 1699; // TIMER 1 INITIALIZED 
float c = 1699; // OFFSETS AFFINE TRANSFORMATION 
char outs[20]; // CHARACTER OUTS, 20 

int main(void)
{
    adc_init(); // ADC INITIALIZATION 
	_delay_ms(150); // WAIT A BIT 
	
	TCCR1B	|= (1<<WGM12)|(1<<CS11); // CTC MODE, PPRESCALER FOR 8 
	TIMSK1 |= (1<<OCIE1A); // MASK INTERRUPT 
	
	OCR1A = start_value; // 20,000us
	DDRD = 0xFF; // PORTD AS OUTPUT 
	OVFCOUNT = 0; // GLOBAL OVERFLOW COUNTER SET TO 0 
	
	sei(); // GLOABL INTERRUPT 
	
    while (1) 
    {
		// THIS LOOP CONSISTS OF AFFINE TRANSFORMATION 
		// KEY CALCULATION (PWM): (39999-1699) * adc_value / (1024-0) + 1699
		read_adc();
		
		float_value = adc_value;
		RPMVALUE = (float_value * 37.4033) + c;
		OCR1A = RPMVALUE; // NEWEST TIME MEASUREMENT LOADED 
    }
}

void adc_init(void)
{
	ADMUX = (0<<REFS1)|    // Reference Selection Bits
	(1<<REFS0)|    // AVcc - external cap at AREF
	(0<<ADLAR)|    // ADC Left Adjust Result
	(0<<MUX2)|     // Analog Channel Selection Bits
	(0<<MUX1)|     // ADC0 (PC0 PIN23)
	(0<<MUX0);
	ADCSRA = (1<<ADEN)|    // ADC ENable
	(0<<ADSC)|     // ADC Start Conversion
	(0<<ADATE)|    // ADC Auto Trigger Enable
	(0<<ADIF)|     // ADC Interrupt Flag
	(0<<ADIE)|     // ADC Interrupt Enable
	(1<<ADPS2)|    // ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);
}

void read_adc(void)
{
	unsigned char i = 4;
	adc_value = 0;
	while (i--)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		adc_value+= ADC;
		_delay_ms(100);
	}
	adc_value = adc_value / 4;  // AVG FEW SAMPLES 
}

ISR(TIMER1_COMPA_vect)
{
	OVFCOUNT++; // OVERFLOW FLAG COUNTER INCREMENT 
	int count; // LOCAL COUNTER INITIALIZED 
	count = OVFCOUNT; // GO HAND IN HAND, BOTH COUNT SIMILARLY 
	
	// 8 NECESSARY STEPS 
	
	if(count == 1){
		PORTD = 0xE;
	}
	
	if(count == 2) {
		PORTD = 0xC;
	}
	
	if(count == 3) {
		PORTD = 0xD;
	}
	
	if(count == 4) {
		PORTD = 0x9;
	}
	
	if(count == 5) {
		PORTD = 0xB;
	}
	
	if(count == 6) {
		PORTD = 0x3;
	}
	
	if(count == 7) {
		PORTD = 0x7;
	}
	
	if(count == 8) {
		PORTD = 0x6;
	}
	// COUNTER RESET IF COMPLETED 
	if(count == 8){
		OVFCOUNT = 0; // STEPPER COUNTER RESTART 
	}
}
