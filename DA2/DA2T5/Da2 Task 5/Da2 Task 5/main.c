/*
 * Da2 Task 5.c
 *
 * Created: 3/4/2016 10:36:45 AM
 * Author : Dominique
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL // 8MHz

void delay250ms();

int main(void)
{	
	int i = 0;				// Counter to be displayed on LEDs
	int c = 0;				// Counter to determine the 5th and 10th rising pulse
	DDRC = 0x30;			// Set PortC.4 and PortC.5 as an output
	DDRB = 0xFF;			// Set all of PortB as an output
	PORTB = 0;				// Initialize PortB to output 0
	PORTC = 0;				// Initialize PortC to output 0

	while (1)
	{
		delay250ms();		// Call the Delay Function
		i++;				// Increment the 8 bit-counter
		PORTB = i;			// Output the 8-bit counter to port B
		c++;				// Increment the toggle counter
		switch(c) {			// Switch Statement to determine which bits to toggle
			case 5  : PORTC = 0x20; break;
			case 10 : PORTC = 0x10; break;
			case 15 : PORTC = 0x30; break;
			case 20 : PORTC = 0x00; c = 0; break;
		}
		delay250ms();
	}
}

// Delay Function to delay for 250ms
void delay250ms(){
	for(int i = 399; i > 0; i--)
	_delay_ms(5);
}