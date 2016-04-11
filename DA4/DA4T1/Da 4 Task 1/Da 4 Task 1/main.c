/*
 * Da 4 Task 1.c
 *
 * Created: 3/31/2016 3:22:08 PM
 * Author : Dominique
 */ 

#define F_CPU 8000000UL		// XTAL = 8 MHz
#include <avr/io.h>
#include <util/delay.h>		// Library for Delay

void delay();
// Red = PB1, OCR1
// Green = PB3, OCR2
// Blue = PD6, OCR0

int main(void)
{
   unsigned char i, j, k;		// Char Max value is 255

   DDRD = 0xFF;			// Set PD6 as an output for OC0A
   DDRB = 0xFF;			// Set PB1 as an output for OC1A and PB3 as an output for OC2A

   i = 230;				// Values for 10% duty cycle in inverted mode
   j = 230;
   k = 230;

   OCR0A = i;			// Duty cycle = 50%
   OCR1A = j;
   OCR2A = k;
   TCCR0A = 0xC1;		// Phase Correct PWM, inverted
   TCCR0B = 0x03;		// Prescalar = 64
   TCCR1A = 0xC1;
   TCCR1B = 0x03;
   TCCR2A = 0xC1;
   TCCR2B = 0x04;
   while(1) 
   {
		while (k >= 30) 
		{
			while(j >= 30)
			{
				while(i >= 30)
				{
					OCR2A = i;
					i = i - 25;
					delay();
				}
				i = 230;
				OCR2A = i;
				j = j - 25;
				OCR1A = j;
				delay();
			}
			j = 230;
			OCR1A = j;
			k = k - 230;
			OCR0A = k;
			delay();
		}
		k = 230;
   }
   while (1);			// Wait here forever after lighting is done
   return 0;
}

// Delay Subroutine that delays for 100 milliseconds.
void delay(){
	for(int i = 50; i >= 0; i--)
	_delay_ms(2);
}