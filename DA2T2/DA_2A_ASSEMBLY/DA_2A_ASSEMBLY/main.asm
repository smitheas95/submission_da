;
; DA_2A_ASSEMBLY.asm
;
; Created: 3/4/2019 9:39:43 PM
; Author : Eric Smith
; (ATMEGA328P XPLAINED MINI BOARD WOULD NOT HOOK UP WITH ATMEL STUDIO 7, POSSIBLY BROKEN)

.ORG 0

.include <m328pdef.inc>

CBI DDRC, 2 ; PC2 AS INPUT
SBI DDRB, 2 ; PB2 AS OUTPUT 

REPEAT: 

SBIS PINC, 2 ; SKIP NEXT IF PC2 IS HIGH
RJMP OVER ; JUMP TO LABEL OVER
SBI PORTB, 2 
RJMP REPEAT ; JUMP TO LABEL REPEAT

OVER:

CBI PORTB, 2 ; PORTB2 SET AS HIGH
LDI R20, 5 ; PRESCALER CLOCK AT 1024
STS TCCR1B, R20 

begin:

LDI R20, 0x00 ;RESET COUNTER TO 0
STS TCNT1H, R20
STS TCNT1L, R20

delay:

LDS R29, TCNT1H ; LOADING UPPER BIT OF COUNTER TO R29
LDS R28, TCNT1L ; LOADING LOWER BIT OF COUNTER INTO R28

CPI R28, 0x4A ; COMPARING IF LOWER 8 BITS OF TIMER IS 0x4A
BRSH body ; IF LOWER BITS OF TIMER HAVEW REACHED DESIRED AMLOUNT, CHECK UPPER BITS
RJMP delay ; OTHERWISE, KEEP CHECKING LOWER BITS

body:

CPI R29, 0x4C ; CHECK TO SEE IF UPPER TIMER BITS HAVE REACHED THER DESIRED VALUE
BRLT delay ; IF NOT, RECHECK THE LOWER BITS
RET ; ONCE TIMER REACHED THE DESIRED VALUE, TOGGLE THE LED

RJMP REPEAT 



