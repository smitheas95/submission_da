
; Assignment_1A.asm
; Author : Eric Smith 
; This program will perform a multiplication of a 16-bit multiplicand with a 8-bit multiplier without using the MUL instruction.
; This program will demomstrate iterative addition. 
; (Breakpoint placed at end:) 

.SET var1 = 0x08AB

		main:
		 
			LDI R22, 0xFF ; values of 0xFF loaded into register R22
			LDI R24, low(var1) ; LOW part of 0x08AB loaded into register R24
			LDI R25, high(var1) ; HIGH part of 0x08AB loaded into register 25
			LDI R26, 0x0 ; initialize register 26 to zero
			LDI R18, 0x0 ; initialize register 18 to zero
			LDI R19, 0x0 ; initialize register 19 to zero 
			LDI R20, 0x0 ; initialize register 20 to zero 

			MOV R27, R22 ; makes copy of register 22 to register 27

			 
		loop: 
			ADD R18, R24 ; register 24 added with register 18
			ADC R19, R25 ; register 25 added with register 19 with carry
			ADC R20, R26 ; register 26 added with register 20 with carry 

			DEC R27 ; decrement from 27 
			CPI R27, 0 ; compares register 27 to immediate value 0, signifying there is nothing else to multiply by
			BRNE loop ; branch when not equal to the loop 
			
			jmp end ; jump to end 

		end:

