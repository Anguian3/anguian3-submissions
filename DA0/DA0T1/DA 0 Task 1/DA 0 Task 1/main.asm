;
; DA 0 Task 1.asm
;
; Created: 2/13/2016 4:02:48 AM
; Author : Dominique
;

.org 0
	sbi DDRB, 2		; Set PORTB.2 as an output
	ldi r16, 0		; Initialize r16 to 0
					; This register will hold the sum
	ldi r17, 59		; Load immediate value 59 into the register
	add r16, r17	; r16 = r16 + r17

	ldi r17, 54		; Load immediate value 54 into the register
	add r16, r17	; r16 = r16 + r17

	ldi r17, 59		; Load immediate value 59 into the register
	add r16, r17	; r16 = r16 + r17
	
	ldi r17, 41		; Load immediate value 41 into the register
	add r16, r17	; r16 = r16 + r17

	ldi r17, 45		; Load immediate value 45 into the register
	add r16, r17	; r16 = r16 + r17

	brcs Overflow	; Branch if an overflow occurs
NoOverflow:
	ldi r18, 0		; Set value of 0 into register to set PORTB.2 pin
					; to low
	out PORTB, r18	; Send value of r18 to corresponding bit
	jmp NoOverflow	; Branch to NoOverflow

Overflow:
	ldi r18, 4		; Set value of 4 into register to set PORTB.2 pin
					; to high
	out PORTB, r18	; Send value of r18 to corresponding bit
	jmp Overflow	; Branch to Overflow