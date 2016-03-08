;
; Da 2 Task 2.asm
;
; Created: 3/1/2016 1:49:55 PM
; Author : Dominique
;

.macro initstack			; Initialize Stack
	ldi r16, high(RAMEND)
	out sph, r16
	ldi r16, low(RAMEND)
	out spl, r16
.endmacro

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
	mov r20, r16			; Counter to determine when to toggle
WaveLoop:
	call Delay				; Call the Delay function 
	inc r1					; Increment the 8-bit counter
	out PORTB, r1			; Output the bits of the 8-bit counter

	inc r20					; Increment the toggle counter
	cpi r20, 5				; Compare to 4 different immediate values
	breq Toggle5th			; to determine which bits to toggle
	cpi r20, 10
	breq Toggle10th
	cpi r20, 15
	breq Toggle15th
	cpi R20, 20
	breq Toggle20th 
FallingEdge:
	call Delay				; Call the Delay subroutine
	jmp WaveLoop			; Restart the Loop

Toggle5th:
	ldi r16, 0x20			; Set bit 5 to high and clear bit 4
	out PORTC, r16
	jmp FallingEdge
Toggle10th:
	ldi r16, 0x10			; Clear bit 5 and set bit 4
	out PORTC, r16
	jmp FallingEdge
Toggle15th:
	ldi r16, 0x30			; Set bit 5 and 4
	out PORTC, r16
	jmp FallingEdge
Toggle20th:
	ldi r20, 0				; Clear r20
	ldi r16, 0x00			; Clear bit 5 and 4
	out PORTC, r16
	jmp FallingEdge


; Subroutine for delay
; This subroutine will cause a delay of approximately .25 Seconds
; Assuming an 8MHz clock
Delay:						; Total of 2,000,455 Cycle Delay
	push r16				; 2 Cycles each push
	push r17
	push r18

	ldi r16, 63				; 1 Cycle
L1:							
	ldi r17, 125			; 1   * 63  = 63 Cycles
L2:
	ldi r18, 83				; 1   * 63 * 125 = 7,875 Cycles
	nop						; 1   * 63 * 125 = 7,875 Cycles
	nop						; 1   * 63 * 125 = 7,875 Cycles
L3:
	dec r18					; 1   * 63 * 125 * 83 =  653,625 Cycles
	brne L3					; 2/1 * 63 * 125 * 83 =  1,299,375 Cycles
	dec r17					; 1   * 63 * 125 = 7,875 Cycles
	brne L2					; 2/1 * 63 * 125 = 15,687 Cycles
	dec r16					; 1   * 63 = 63 Cycles
	brne L1					; 2/1 * 63 = 125 Cycles

	pop r18					; 2 Cycles each pop
	pop r17
	pop r16
	ret						; 4 Cycles