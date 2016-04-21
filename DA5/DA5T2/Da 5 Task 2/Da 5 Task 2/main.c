/*
 * Da 5 Task 2.c
 *
 * Created: 4/7/2016 6:27:28 PM
 * Author : Dominique
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>		// Needed for if_bit_is_clear function
#include <util/delay.h>			// Needed for delay function

void Delay(unsigned int time);

float ADC_ratio = .0009775; // 1/1023
int time = 50;
int value;
int main(void)
{
	DDRB = 0xFF;
	/*Enable the ADC Conversion*/
	ADMUX = 0;									// use ADC0
	ADMUX |= (1 << REFS0);						// use AVcc as the reference
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);		// 8 prescaler
	ADCSRA |= (1 << ADEN);						// Enable the ADC
	ADCSRA |= (1 << ADSC);						// Start the ADC conversion

	while (1)               // Infinite while loop for code execution
	{
		ADCSRA |= (1 << ADSC);						// Start the ADC conversion
		loop_until_bit_is_clear(ADCSRA, ADSC);
		value = ADC;
		PORTB = 0X66;
		Delay((unsigned int)time*value*ADC_ratio);
		PORTB = 0xCC;
		Delay((unsigned int)time*value*ADC_ratio);
		PORTB = 0x99;
		Delay((unsigned int)time*value*ADC_ratio);
		PORTB = 0x33;
		Delay((unsigned int)time*value*ADC_ratio);
	}
	return 0;
}

// Function delays for the number of ms provided
void Delay(unsigned int length)
{
	int i = 0;
	for (i = 0; i < length; i++)
		_delay_ms(1);
}
