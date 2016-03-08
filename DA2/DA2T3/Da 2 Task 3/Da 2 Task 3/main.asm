;
; Da 2 Task 3.asm
;
; Created: 3/3/2016 3:45:59 PM
; Author : Dominique
;

	.org 0x00
	rjmp Start
	.org 0x16
	rjmp TCNT1_COMPA

.macro initstack			; Initialize Stack
	ldi r16, high(RAMEND)
	out sph, r16
	ldi r16, low(RAMEND)
	out spl, r16
.endmacro


Init:
Start:
	sbi DDRB, 0				; Set all the bits in Port B as outputs
	sbi DDRB, 1
	sbi DDRB, 2
	sbi DDRB, 3
	sbi DDRB, 4
	sbi DDRB, 5
	sbi DDRB, 6
	sbi DDRB, 7

	sbi DDRC, 5				; SEt port C bit 5 as an output
	sbi DDRC, 4				; Set port C bit 6 as an output

	ldi r16, 0				; Load r16 to 0 to initialize the counter
	mov r1, r16				; Copy r16 to r1.  r1 will be our 8 bit
							; counter
	mov r20, r16			; r2 is the toggle counter

	; Code to use Timer 1 on CTC mode for the interrupt
	ldi r22, 0x0F			; Load the value 1954 (0x7A2) into OCR1
	sts OCR1aH, r22			; Load the high bits of Output Compare Register 1			
	ldi r22, 0x44
	sts OCR1aL, r22			; Load the low bits of Output Compare Register 1

	ldi r22, 0x00
	sts TCCR1A, r22			; Timer 1, CTC mode, Normal port Operation
	ldi r22, 0x0D			; Turn clock on, 1024 prescaler
	sts TCCR1B, r22
	ldi r22, 0x02			; Enable the Timer 1 Output Compare Match Interrupt
	sts TIMSK1, r22
	sei						; Enable the global Interrupt

WaveLoop:
	rjmp Waveloop

TCNT1_COMPA:
	ldi r22, 0x02			; Load a 1 into bit 1 to clear OCF1A flag
	out TIFR1, r22
	inc r1
	out PORTB, r1
Toggler:
	inc r20					; Increment the toggle Counter
	cpi r20, 5				; Compare to 4 different immediate values
	breq Toggle5th			; to determine which bits to toggle
	cpi r20, 10
	breq Toggle10th
	cpi r20, 15
	breq Toggle15th
	cpi r20, 20
	breq Toggle20th 
	jmp TogglerEnd
Toggle5th:
	ldi r16, 0x20			; Set bit 5 to high and clear bit 4
	out PORTC, r16
	jmp TogglerEnd
Toggle10th:
	ldi r16, 0x10			; Clear bit 5 and set bit 4
	out PORTC, r16
	jmp TogglerEnd
Toggle15th:
	ldi r16, 0x30			; Set bit 5 and 4
	out PORTC, r16
	jmp TogglerEnd
Toggle20th:
	ldi r20, 0				; Clear r2
	ldi r16, 0x00			; Clear bit 5 and 4
	out PORTC, r16
TogglerEnd:
	reti