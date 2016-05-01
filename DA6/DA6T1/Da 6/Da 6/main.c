/*
 * Da 6.c
 *
 * Created: 4/21/2016 6:18:09 PM
 * Author : Dominique
 */ 

 #define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>				// needed for uint8_t
#include <avr/interrupt.h>

#include "nokia5110.h"

volatile uint32_t mathy;
volatile uint16_t ADCvalue;		// Global variable, set to volatile if used with ISR
volatile char ones, tens;		// Global variable for the characters to be transmit.

void delay1s();


int main(void)
{
    nokia_lcd_init();
    nokia_lcd_clear();
	nokia_lcd_write_string("Temp in F", 1);

	ADMUX = 0;									// use ADC0
	ADMUX |= (1 << REFS0);						// use AVcc as the reference
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);		// 64 prescaler for 8Mhz
	ADCSRA |= (1 << ADATE);						// Set ADC Auto Trigger Enable
	ADCSRB = 0;									// 0 for free running mode
	ADCSRA |= (1 << ADEN);						// Enable the ADC
	ADCSRA |= (1 << ADIE);						// Enable Interrupts
	ADCSRA |= (1 << ADSC);						// Start the ADC conversion
	sei();
    while(1)
	{
	}
}

ISR(ADC_vect)
{
	ADCvalue = ADC; // only need to read the low value for 8 bit
	mathy = ADCvalue;	// Value to perform the conversion between ADC and temperature
	mathy = mathy * 5;	// Math to convert from the given ADC value to a temperature value
	mathy = mathy * 100;
	mathy = mathy / 1024;
	ones = mathy % 10;	// Obtaining the ones digit for the temperature value
	tens = mathy / 10;	// Obtaining the tens digit for the temperature value
	nokia_lcd_set_cursor(0, 10);
	nokia_lcd_write_char(tens+'0', 3);	// Output the digits
	nokia_lcd_write_char(ones+'0', 3);	// Output the digits
	nokia_lcd_write_string(" :)", 3);
	nokia_lcd_render();
	delay1s();	// Delay for 1 second before converting the next value
}

void delay1s(){
	for(int i = 500; i > 0; i--)
	_delay_ms(2);
}