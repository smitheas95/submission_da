
; DA_2B_T1.asm

; Created: 3/9/2019 6:59:15 PM
; Author : Eric Smith

.include <m328pdef.inc>
.ORG 0x02 ; LOCATION FOR RESET
RJMP EXO_ISR

START:
LDI R16, 0x04 ; LOAD BINARY 0b00000100 INTO R16
OUT DDRB, R16 ; DIRECTION IS SET FOR R16 AS OUTPUT 
OUT PORTB, R16 ; PULL-UP RESISTOR SET AT PIN3
LDI R17, 0x00 ; LOAD IMMEDIATE VALUE 0x00 INTO R17
OUT DDRD, R17 ; DIRECTION IS SET FOR R17 AS INPUT FOR ALL 
SBI PORTD, 2 ; SET BIT, PULL-UP RESISTOR
NOP ; WAIT 

; INTERRUPT INITIALIZATION

LDI R20, 0x2 ; MAKE INT0 FALLING EDGE TRIGGERED
STS EICRA, R20 ; CONFIGURE LOADED INTO R20
LDI R20, 1 << INT0 ; ENABLE INT0
OUT EIMSK, R20 ; (MASK) LOAD ENABLE INTO R20
SEI ; ENABLE GLOBAL INTERRUPTS

HERE: JMP HERE

EXO_ISR:
LDI R21, 0xFB ; LOAD BINARY 0b11111011 TO R21
OUT PORTB, R21 ; LED TURNED ON 
RCALL DELAY_GO ; RUN THROUGH DELAY(S)
RCALL DELAY_100MS
RCALL DELAY_50MS 
OUT PORTB, R16 ; LED TURNED OFF
RETI 

; PROCESS OF USING DELAYS TO CALCULATE/GET 1.25 SECONDS 

DELAY_GO:
RCALL DELAY_100MS ; 0.1 SECONDS
RCALL DELAY_100MS ; 0.2 SECONDS
RCALL DELAY_100MS ; 0.3 SECONDS
RCALL DELAY_100MS ; 0.4 SECONDS
RCALL DELAY_100MS ; 0.5 SECONDS
RCALL DELAY_100MS ; 0.6 SECONDS
RCALL DELAY_100MS ; 0.7 SECONDS
RCALL DELAY_100MS ; 0.8 SECONDS 
RCALL DELAY_100MS ; 0.9 SECONDS 
RCALL DELAY_100MS ; 1 SECOND
RCALL DELAY_100MS ; 1.1 SECONDS
RCALL DELAY_100MS ; 1.2 SECONDS
RET 

DELAY_100MS:
RCALL DELAY_50MS ; 1.25 SECONDS 
RET 

DELAY_50MS:
PUSH R16
PUSH R18
LDI R16, 255 ; LOAD IMMEDIATE 255 TO R16
LDI R18, 6 ; LOAD IMMEDIATE 6 TO R18

DELAY_1A: 
	DELAY_1B:
	NOP ; WAIT
	DEC R16 ; DECREMENT R16
	BRNE DELAY_1B
	DEC R18 ; DECREMENT R18
	BRNE DELAY_1B
	POP R18 ; POP REGISTER FROM STACK 
	POP R16 ; POP REGISTER FROM STACK 
	RET 