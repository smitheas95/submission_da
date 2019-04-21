/*
 * DA4B_T2.c
 *
 * Created: 4/21/2019 1:49:04 AM
 * Author : ERIC SMITH 
 
 2. Write an AVR C program to control the position of the Servo Motor using a
 potentiometer connected to PC0. When pot value is 0 the servo is at position 0 deg.
 and when pot value is max (approx. 5V) the servo is at position 180 deg.
 */ 

#define F_CPU 16000000UL

// NEEDED LIBRARIES 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

void read_adc(void);
void adc_init(void);

void USART_init( unsigned int ubrr );
void USART_tx_string( char *data );

volatile int PWMVALUE; // PWM VALUE 
volatile unsigned int adc_value; // ADC VALUE 
volatile double	float_value; // FLOAT VALUE 

float c = 97; // AFFINE TRANSFORMATION, OFFSET NEEDED 
char outs[20]; // CHARACTER OUTS, 20 

int main(void)
{
	
	TCCR1A |= (1 << COM1A1)|(1 << COM1B1)|(1 << WGM11); // TIMER 1 CONFIGURATED  
	TCCR1B|= (1 << WGM13)|(1 << WGM12)|(1 <<  CS11)|(1 << CS10); // PRESCALAR 64, WGM MODE 14, NON-INVERTED PWM
	
	ICR1 = 4999; // KEY NUMBER 
	// SERVO MOTOR OPERATION STANDARD AT 20ms 
	DDRB |= (1<<PORTB1);
	
	adc_init(); // ADC INITIALIZED 
	
	USART_init(BAUD_PRESCALLER);  // USART INITIALIZED 
	USART_tx_string("Connected!\r\n"); 
	
	_delay_ms(150); // WAIT A BIT 
	
	while(1)
	{
		read_adc();
		
		// KEY CALCULATION: adc_value * (535-97) / (1024 - 0) + 97
		
		float_value = adc_value;
		PWMVALUE = (float_value*0.4277343) + c;
		
		snprintf(outs,sizeof(outs),"%3d\r\n", PWMVALUE);  // PRINT 
		USART_tx_string(outs);
		
		OCR1A = PWMVALUE; 
		_delay_ms(150); // WAIT A BIT 
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
		_delay_ms(50);
	}
	adc_value = adc_value / 4;  // AVG FEW SAMPLES 
}

void USART_tx_string( char *data )
{
	while ((*data != '\0'))
	{
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}

void USART_init( unsigned int ubrr )
{
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0);     // Enable RX, TX & RX interrupt
	UCSR0C = (3 << UCSZ00);    // ASYNCHRONOUS 8 N 1
}



