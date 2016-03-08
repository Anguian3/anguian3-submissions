/*
 * Da2 Task 6.c
 *
 * Created: 3/4/2016 10:36:45 AM
 * Author : Dominique
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define F_CPU 8000000UL // 8MHz

int c = 0;				// Counter to determine the 5th and 10th rising pulse
int i = 0;				// Counter to be displayed on LEDs

// This interrupt is triggered whenever
// a match occurs
ISR (TIMER1_COMPA_vect) {
	i++;										// Increment Counter
	PORTB = i;									// Output Counter to Port
	c++;										// Toggle Counter
	switch(c) {
		case 5  : PORTC = 0x20; break;			// PC5 on, PC4 Off
		case 10 : PORTC = 0x10; break;			// PC5 off, PC4 On
		case 15 : PORTC = 0x30; break;			// PC4 and PC5 On
		case 20 : PORTC = 0x00; c = 0; break;	// PC4 and PC 5 Off
	}
}

int main(void)
{	
	DDRC = 0x30;			// Set PortC.4 and PortC.5 as an output
	DDRB = 0xFF;			// Set all of PortB as an output
	PORTB = 0;				// Initialize PortB to output 0
	PORTC = 0;				// Initialize PortC to output 0

	OCR1A = 0x0F44;			// Load value 1954 into Output Compare Register
	TCCR1A = 0x00;			// Timer 1, CTC mode, Normal port Operation
	TCCR1B = 0x0D;			// Turn the clock on with 1024 prescaler
	TIMSK1 = 0x02;			// Enable the Timer 1 Output Compare Match Interrupt
	sei();					// Enable Global Interrupts

	while (1)
	{
		// Do Nothing
		// Interrupt should occur every .5 seconds.
	}
}