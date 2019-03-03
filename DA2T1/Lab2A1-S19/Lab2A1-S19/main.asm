;
; Lab2A1-S19.asm
;
; Created: 3/2/2019 10:38:26 PM
; Author : eas7w

.ORG 0
LDI R20, 0xFF ; load immediate value of 0xFF into register R20

OUT DDRB, R20 ; set as output alongside values of 0xFF

LDI R17, 0x01 ;  load immediate 0x01 into R17
LDI R18, 0x00 ; load immediate 0x00 into R18
LDI R22, .435 ; load immediate timing into R22
LDI R21, .435 ; load immediate timing
LDI R23, 48 ; load immediate timing into R23

L1:
DELAY1:
	INNERDELAY1: ; represents inner delay
	DEC R22 ; decrement R22
	BRNE INNERDELAY1 ; branch when not equal to innerdelay1
	DEC R21 ; decrement R21
	BRNE DELAY1 ; branch when not equal to delay1
	DEC R23 ; decrement R23
	BRNE L1 ; branch when not equal to L1
	OUT PORTB, R17 ; output R17 for portb
	LDI R22, .435 ; load immediate timing
	LDI R21, .435 ; load immediate timing
	LDI R23, 48 ; load immediate timing
	L2: 
	DELAY2: 
	INNERDELAY2: ; represents inner delay 2
	DEC R22 ; decrement R22
	BRNE INNERDELAY2 ; branch when not equal to innerdelay 2
	DEC R21 ; decrement R21
	BRNE DELAY2 ; branch when not equal to delay 2
	DEC R23 ; decrement R23
	BRNE L2 ; branch when not equal to L2
	OUT PORTB, R18 ; output R18 into portb