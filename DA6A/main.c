/*
 * DA6A.c
 *
 * Created: 5/6/2019 8:08:36 PM
 * Author : ERIC SMITH
 
 Interface the provided MPU-6050 6-DOF IMU Sensor to the ATmega328p using the
 I2C interface. Using the earlier developed code for UART, display the accelerometer
 and gyro data to the UART Terminal. Extra credits for 1) visualizing the
 accelerometer and gyro values (10 points), and 2) Apply Kalman Filtering on at least
 one sensor data and display the filtered value.
 */ 

#define F_CPU 16000000UL
#ifndef F_CPU
#endif

// NEEDED LIBRARIES 
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>										
#include <stdio.h>										

#include "MPUlibraries/MPU6050_def.h" // MPU 6050REGISTER DEFINE FILE
#include "MPUlibraries/i2c_master.h" // I2C MASTER HEADER FILE	
#include "MPUlibraries/uart.h"	// USART HEADER FILE

#define MPU6050_WRITE 0xD0
#define MPU6050_READ 0xD1

// KEY FLOAT VARIABLES 
float Acc_x;
float Acc_y;
float Acc_z;

float Gyro_x;
float Gyro_y;
float Gyro_z;

int main(void){
	char buffer[20], float_[10];
	char* PAX = "X Acceleration = ";
	char* PAY = "Y Acceleration = ";
	char* PAZ = "Z Acceleration = ";
	char* PGX = "X Gyro Position = ";
	char* PGY = "Y Gyro Position = ";
	char* PGZ = "Z Gyro Position = ";
	float Xa;
	float Ya;
	float Za;
	float Xg;
	float Yg;
	float Zg;
	init_uart(9600);
	i2c_init();
	init_MPU6050();
	
	while(1){
		getreading();
		Xa = Acc_x/16384.0;	/* Divide raw value by sensitivity scale factor to get real values */
		Ya = Acc_y/16384.0;
		Za = Acc_z/16384.0;
		Xg = Gyro_x/131;
		Yg = Gyro_y/131;
		Zg = Gyro_z/131;
		dtostrf( Xa, 3, 2, float_ );/* Take values in buffer to send all parameters over USART */
		sprintf(buffer,"%s, ",float_);
		USART_SendString(PAX);
		USART_SendString(buffer);
		_delay_ms(100);
		
		dtostrf( Ya, 3, 2, float_ ); /* Take values in buffer to send all parameters over USART */
		sprintf(buffer,"%s, ",float_);
		USART_SendString(PAY);
		USART_SendString(buffer);
		_delay_ms(100);
		
		dtostrf( Za, 3, 2, float_ ); /* Take values in buffer to send all parameters over USART */
		sprintf(buffer,"%s, ",float_);
		USART_SendString(PAZ);
		USART_SendString(buffer);
		USART_SendString("\r\n");
		_delay_ms(1000);
		
		dtostrf( Xg, 3, 2, float_ ); /* Take values in buffer to send all parameters over USART */
		sprintf(buffer,"%s, ",float_);
		USART_SendString(PGX);
		USART_SendString(buffer);
		
		_delay_ms(100);
		
		dtostrf( Yg, 3, 2, float_ ); /* Take values in buffer to send all parameters over USART */
		sprintf(buffer,"%s, ",float_);
		USART_SendString(PGY);
		USART_SendString(buffer);
		_delay_ms(100);
		
		dtostrf( Zg, 3, 2, float_ ); /* Take values in buffer to send all parameters over USART */
		sprintf(buffer,"%s, ",float_);
		USART_SendString(PGZ);
		USART_SendString(buffer);
		USART_SendString("\r\n");
		_delay_ms(1000);
	}
	
	return 0;
}

void uart_putc(unsigned char c){

	while(!(UCSR0A & (1<<UDRE0))); // WAIT A BIT, BEFORE SENDING CAN OCCUR 
	UDR0 = c; // OUTPUT CHARACTER, SAVED IN C 
}

void uart_puts(char *s){
	while(*s){
		uart_putc(*s);
		s++;
	}
}

void init_uart(uint16_t baudrate){

	uint16_t UBRR_val = (F_CPU/16)/(baudrate-1);

	UBRR0H = UBRR_val >> 8;
	UBRR0L = UBRR_val;

	UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0); // UART TX (TRANSMIT 
	UCSR0C |= (1<<USBS0) | (3<<UCSZ00); // MODUS ASYNCHRON 
}

void init_MPU6050(void){
	_delay_ms(150);										
	i2c_start(MPU6050_WRITE); // GYROSCOPE SAMPLE RATE = 1KHz, ACCELEROMETER SAMPLE RATE = 1KHz  
	i2c_write(SMPLRT_DIV); // SAMPLE RATE PRODUCED, DIVIFING GYROSCOPE OUTPUT RATE BY SMPLRT_DIV
	i2c_write(0x07); // GYROSCOPE OUTPUT RATE = 8KHz, SAMPLE RATE = GYROSCOPE OUTPUT RATE / (1 + SMPLRT_DIV)
	i2c_stop();

	i2c_start(MPU6050_WRITE);
	i2c_write(PWR_MGMT_1);
	i2c_write(0x01); // X AXIS, PLL GYROSCOPE REFERENCE PLL 
	i2c_stop();

	i2c_start(MPU6050_WRITE);
	i2c_write(CONFIG); // FRAME SYNCHRONIZATION & DIGITAL LOW PASS FILTER 
	i2c_write(0x00);
	i2c_stop();
	
	i2c_start(MPU6050_WRITE);
	i2c_write(GYRO_CONFIG); // GYROSCOPE SCALE RANGE = FS_SEL SELECTS = 11  = ± 2000 °/s
	i2c_write(0x18);		// ACCELEROMETER RANGE  = ± 2g (default)
	i2c_stop();

	i2c_start(MPU6050_WRITE);
	i2c_write(INT_ENABLE); // DATA_RDY_EN = 1
	i2c_write(0x01);
	i2c_stop();
}

void getreading(void){
	
	i2c_start(MPU6050_WRITE);
	i2c_write(ACCEL_XOUT_H); // POINTER SET
	i2c_start(MPU6050_READ);
	Acc_x = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	// ACCEL Y
	Acc_y = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());

	// ACCEL Z
	Acc_z = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());

	// GYRO X
	Gyro_x = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	
	// GYRO Y
	Gyro_y = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	
	// GYRO Z
	Gyro_z = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	i2c_stop();
}
