;
; Da 2 Task 1.asm
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
	sbi DDRC, 0				; Set port C bit 0 as an output
WaveLoop:
	call Delay				; Call the Delay function 
	ldi r16, 1
	out PORTC, r16			; Output a 1 at PORTC.0

FallingEdge:
	call Delay				; Call the Delay subroutine
	ldi r16, 0
	out PORTC, r16			; Output a 0 at PORTC.0
	jmp WaveLoop			; Restart the Loop

; Subroutine for delay
; This subroutine will cause a delay of approximately .25 Seconds
; Assuming an 8MHz clock
Delay:						; Total of 2,000,455 Cycle Delay
	push r16				; 2 Cycles each push
	push r17				; This saves the values that were
	push r18				; originally in these registers

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
	pop r17					; Return the values to the registers
	pop r16
	ret						; 4 Cycles