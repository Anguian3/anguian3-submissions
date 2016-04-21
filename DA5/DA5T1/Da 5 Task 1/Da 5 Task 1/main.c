/*
 * Da 5 Task 1.c
 *
 * Created: 4/7/2016 3:24:01 PM
 * Author : Dominique
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>			// Needed for delay function
#include <stdint.h>				// needed for uint8_t
#define ENABLE 6

void Delay(unsigned int time);

float ADC_ratio = .0009775; // 1/1023
int time = 50;
int value;
int main(void)
{
	DDRD |= (1<<6);         // Enable Port D.6 as an output
	PORTD = (1<<ENABLE);    // Output 1 at Port D.6
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
		PORTD = PORTD | (1<<ENABLE);
		Delay((unsigned int)time*value*ADC_ratio);
		PORTD = PORTD & (~(1<<ENABLE));
		Delay((unsigned int)time*(1-(value*ADC_ratio)));
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
