/*
 * Da 2 Task 4.c
 *
 * Created: 3/4/2016 9:33:14 AM
 * Author : Dominique
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL // 8MHz

void delay250ms();

int main(void)
{
	DDRC = 0x01;		// Set portC.0 as an output
	PORTC = 0;			// Initialize portC to output 0
    while (1) 
    {
	delay250ms();		// Call the Delay Function
	PORTC = 1;			// Output a 1 at PORTC.0
	delay250ms();
	PORTC = 0;			// Output a 0 at PORTC.0
    }
}

// Function to Delay for approximately 250ms
void delay250ms(){
	for(int i = 399; i > 0; i--)
		_delay_ms(5);
}