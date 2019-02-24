;
; Lab1B-S19.asm
;
; Created: 2/23/2019 6:04:17 PM
; Author : Eric Smith 

; Breakpoint used at RJMP END 
; Chose consecutive numbers option instead of random numbers 
; 
; process of storing 99 numbers 

RESET:

.SET STARTADDS = 0x0200 
.SET COUNT = 99

.ORG 0 

; POINTER SITUATION 

LDI XL, LOW(STARTADDS) ; initializes [X] = 0x0200
LDI XH, HIGH(STARTADDS) 

LDI YL, LOW(0x0400) ; initializes [Y] = 0x0400
LDI YH, HIGH(0x0400) 

LDI ZL, LOW(0x0600) ; initializes [Z] = 0x0600
LDI ZH, HIGH(0x0600) 

; COUNT REGISTER INITIALIZATION 

LDI R21, COUNT ; R21 = 99
LDI R22, 10 ; R22 = 10 is starting point of counter 
LDI R20, 3 ; R20 = 3

; CLEARING REGISTERS FOR SUMS

CLR R0
CLR R16
CLR R17
CLR R18
CLR R19

; ADDING LOWER ANDS HIGHER ADDRESS BITS TO BE STORED 

START:
 
MOV R1, XL ; R1 = XL
ADD R1, XH ; R1 = XH + XL
MOV R3, R1 ; R3 = R1
ADD R3, R22 ; R3 = 10 + R3
ST X+, R3 ; stores values of R3 into incremented "X" register 

DIVBYTHREE: ; divide by 3 loop

CP R1, R20 ; compare R20 to R1
BRLO DIVBAD ; if R1 < 3 go to DIVBAD
SUB R1, R20 ; R1 - 3
CP R1, R0 ; compare R0 to R1
BREQ DIVGOOD ; if R1 = 0 go to DIVGOOD
RJMP DIVBYTHREE 

DIVGOOD: ; divide by 3 is good loop 

SUB R3, R23 ; subtract R23 from R3
ST Y+, R3 ; stores value of R3 into incremented "Z" register
ADD R16, R3 ; R16 = ZH + ZL
ADC R17, R0 ; R17 = carry value from previous line
RJMP DONE

DIVBAD: ; divide by 3 is not good loop 

SUB R3, R23 ; subtract R23 from R3
ST Z+, R3 ; stores value of R3 into incremented "Y" register 
ADD R18, R3 ; R18 = YH + YL 
ADC R19, R0 ; R19 = carry value from previous line 
RJMP DONE 

DONE: 

CP R21, R0 ; compare R0 to R21
BREQ END ; if R21 = 0 go back to finish
SUBI R21, 1 ; R21 = 21 - 1
BRNE START ; if R21 != 0 go back to START

FINALVAL: ; final value part (label)

ADD R3, R23 ; add R23 with r3
ADD R18, R3 ; add R3 with R18
ADC R19, R0 ; add with carry for R0 with R19

END:
RJMP END


