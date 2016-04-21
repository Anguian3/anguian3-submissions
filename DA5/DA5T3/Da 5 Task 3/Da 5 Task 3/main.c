/*
 * Da 5 Task 3.c
 *
 * Created: 4/7/2016 6:46:02 PM
 * Author : Dominique
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>		// Needed for if_bit_is_clear function
#include <util/delay.h>

void Delay(unsigned int time);

const float ADC_ratio = .0009775; // 1/1023
int value;

int main()
{
	int x;
	int angle;
	DDRB = 0xFF;  // Set port B as an output for timer 1
	/*Enable the ADC Conversion*/
	ADMUX = 0;									// use ADC0
	ADMUX |= (1 << REFS0);						// use AVcc as the reference
	ADCSRA |= (1 << ADPS0) | (1 << ADPS1);		// 8 prescaler
	ADCSRA |= (1 << ADEN);						// Enable the ADC
	ADCSRA |= (1 << ADSC);						// Start the ADC conversion

	//TOP = ICR1;
	//output compare OC1A 8 bit non inverted PWM
	//Clear OC1A on Compare Match, set OC1A at TOP
	//Fast PWM
	//ICR1 = 20000 defines 50Hz pwm
	ICR1 = 20000;
	OCR1A = 500;
	TCCR1A|=(0<<COM1A0)|(1<<COM1A1)|(0<<COM1B0)|(0<<COM1B1)|(0<<FOC1A)|(0<<FOC1B)|(1<<WGM11)|(0<<WGM10); //TCCR1A = 0x82
	TCCR1B|=(0<<ICNC1)|(0<<ICES1)|(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10); //TCCR1B = 0x1A
	while (1)
	{	
		ADCSRA |= (1 << ADSC);	// Start the ADC conversion
		loop_until_bit_is_set(ADCSRA, ADSC);
		value = ADC;
		angle = 1800*(1-(ADC_ratio*value)); // Total value of 500 is approximately 0 degrees
		angle = 500 + angle;  // Total value of 2300 is approximately 180 degrees
		OCR1A = angle;
		for(x = 0; x<500;x++)
			_delay_ms(1);
	}
	return 0;
}