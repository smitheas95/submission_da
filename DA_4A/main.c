/*
 * DA_4A.c
 *
 * Created: 4/13/2019 4:15:36 PM
 * Author : Eric Smith
 */ 

#define F_CPU 16000000UL

// NEEDED LIBRARIES 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

// UART BAUDRATE 
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

// DECLARATION OF KEY FUNCTIONS 
void adc_init(void);
void read_adc(void);

void USART_init( unsigned int ubrr );
void USART_tx_string( char *data );

char outs[20];

volatile unsigned int adc_temp; 
volatile unsigned int adc_value;

int main(void)
{
	adc_init(); // ADC INITIALIZATION
	
	USART_init(BAUD_PRESCALLER); // USART INITIALIZATION 
	USART_tx_string("Connected!\r\n"); 
	
	_delay_ms(250); // WAIT A LITTLE BIT 
	
	// INITIALIZING PWM (PULSE WIDTH MODULATION) 
	DDRD = 0xFF;  // OUTPUT THE PWM, SET PORTD AS OUTPUT DIRECTION 
	
	TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // SET NEEDED BITS HIGH ( WGM21, WGM20, COM2A1, COM2B1 ) 
	TCCR2B = _BV(WGM22) | _BV(CS20) | _BV(CS21) | _BV(CS22); // SET BIT WGM22 TO HIGH (FAST PWM MODE 7 RESET COUNTER) , SET CS20 TO HIGH
	
	OCR2A = 255; // SET FOR WHEN COUNTER HITS 255, IT RESETS 
	OCR2B = 0; // REPRESENTS DUTY CYCLE
	
	// PIN CHANGE INITILAIZER INTERRUPT 
	PCMSK1 |= (1 << PCINT10); // ENABLE PCINT10 
	PCICR |= (1 << PCIE1); // SET PIN CHANGE INTERRUPT, ENABLE REGISTER 1 
	
	sei(); // GLOBAL INTERRUPT SET
	
	while (1) // WHILE LOOP NEEDED 
	{
		read_adc();
		_delay_ms(250
		
		adc_value = adc_value / 4;
		snprintf(outs,sizeof(outs),"%3d\r\n", adc_value);  // PRINT 
		USART_tx_string(outs); // ADC VALUE PRINTED 
		OCR2B = adc_value; // ADC VALUE REPLACED
	}
}

void adc_init(void)
{
	// SETUP & ENABLE ADC 
	ADMUX = (0<<REFS1)| // REFERENCE SELECTION BITS 
	(1<<REFS0)|    // AVcc - EXTERNAL CAP AT AREF 
	(0<<ADLAR)|    // ADC LEFT ADJUST RESULT 
	
	// ADJUST MUX 
	(0<<MUX2)|     // ANALOG CHANNEL SELECTION BITS 
	(0<<MUX1)|     // ADC0 - (PC0 PIN27)
	(0<<MUX0);
	ADCSRA = (1<<ADEN)|    // ADC ENABLE 
	(0<<ADSC)|     // ADC START CONVERSION ADC 
	(0<<ADATE)|    // ADC AUTO TRIGGER ENABLE 
	(0<<ADIF)|     // ADC INTERRUPT FLAG 
	(0<<ADIE)|     // ADC INTERRUPT ENABLE 
	(1<<ADPS2)|    // ADC PRESCALER SELECT BITS 
	(0<<ADPS1)|
	(1<<ADPS0);
}

void read_adc(void)
{
	unsigned char i = 4;
	adc_temp = 0;
	while (i--)
	{
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		adc_temp+= ADC;
		_delay_ms(100); // DELAY 
	}
	adc_value = adc_value / 4;  // FEW SAMPLES SAMPLED 
}

// SEND STRING TO RS-232
void USART_tx_string( char *data )
{
	while ((*data != '\0'))
	{
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}

// INIT USART (RS-232)
void USART_init( unsigned int ubrr )
{
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0); // ENABLE RX, TX & RX INTERRUPT 
	UCSR0C = (3 << UCSZ00); // ASYNCHRONOUS 8 N 1 
}

ISR(PCINT1_vect)
{
	DDRD ^= 0xFF; // XOR DIRECTION REGISTER, TURN MKOTOR ON/OFF XOR
	_delay_ms(1000); // BOUNCE GND 
	
	char check = " Pin Change ";
	USART_tx_string(check); // PRINT AT SAME TIME OF PIN CHANGE 
}