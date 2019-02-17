;
; Assignment1_1AMUL.asm
 ; This program will verify the performance of the multiplication of a 16 bit number with a 8 bit multiplier WITH using the MUL instruction  
 ; Note: Goal involves demonstrating two multiplications and adding both results 

.def Res18 = R18 ; setting a symbolic name on a register 18, allows register to be referred to as symbols 
.def Res19 = R19 ; setting a symbolic name on a register 19, allows register to be referred to as symbols 
.def Res20 = R20 ; setting a symbolic name on a register 20, allows register to be referred to as symbols 
.def m1A = R24 ; setting a symbolic name on register 24, will be considered for LOW part in calculations 
.def m1B = R25 ; setting a symbolic name on register 25, will be considered for HIGH part in calculations 
.def m2 = R22 ; setting a symbolic name on register 22, represents multiplier 

; Loading Registers, setting up situation of 16 bit being multiplied by 8 bit multiplier

.SET m1 = 0x08AB ; 16 bit constant to be tested 

	LDI m1B,HIGH(m1) ; Load immediate of upper 8 bits of m1 to m1B
	LDI m1A,LOW(m1) ; Load immediate of lower 8 bits of m1 to m1A
	LDI m2,0xFF ; Load immediate of 8-bit constant to m2

; Quick Breakdown: As R25 and R24 gets multiplied by R22, R24 and R22 produce a 16 bit result.
; Then, R25 gets multiplied by R22, it produces a result that is a 16 bit as well.
; So, the HIGH part of the number produced by the multiplication of R24 and R22 is added to the LOW part produced by the multiplication of R25 and R22.

	MUL m1A,m2 ; Multiplying the least significant bits 
	MOV Res18,R0 ; copying result to register 18 which is a result register 
	MOV Res19,R1 ; copying result to register 19 which is a result register 

	MUL m1B,m2 ; Multiplying the most significant bits 

	MOV Res20,R1 ; copying most significant result to result 
	ADD Res19,R0 ; adding least significant bit result to result 
	BRCC NoInc ; jump if there is no carry 
	INC Res20 ; increment for when there is a 1 carried over 
NoInc: ; jump occurs when there is no carry 



