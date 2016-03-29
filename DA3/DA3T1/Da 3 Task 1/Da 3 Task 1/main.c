/*
 * Da 3 Task 1.c
 *
 * Created: 3/17/2016 2:04:27 PM
 * Author : Dominique
 */ 

#include <avr/io.h>
#include <stdint.h>				// needed for uint8_t
#include <avr/interrupt.h>

#define F_CPU 8000000UL			// Clock Speed
#include <util/delay.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD -1

volatile uint32_t mathy;
volatile uint16_t ADCvalue;		// Global variable, set to volatile if used with ISR
volatile char ones, tens;		// Global variable for the characters to be transmit.

void USART0SendByte(char);		// Declaration of the Method to transmit char
void delay1s();

int main(void)
{

	/*Set baud rate */
	UBRR0L = MYUBRR;
	UCSR0B |= (1 << TXEN0);				// Enable transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // Set frame: 8-bit data

	ADMUX = 0;									// use ADC0
	ADMUX |= (1 << REFS0);						// use AVcc as the reference
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);		// 64 prescaler for 8Mhz
	ADCSRA |= (1 << ADATE);						// Set ADC Auto Trigger Enable
	ADCSRB = 0;									// 0 for free running mode
	ADCSRA |= (1 << ADEN);						// Enable the ADC
	ADCSRA |= (1 << ADIE);						// Enable Interrupts
	ADCSRA |= (1 << ADSC);						// Start the ADC conversion
	sei();	
													
	while (1)
	{
	}
}

ISR(ADC_vect)
{
	ADCvalue = ADCH; // only need to read the high value for 8 bit
	mathy = ADCvalue;	// Value to perform the conversion between ADC and temperature
	mathy = mathy * 5;	// Math to convert from the given ADC value to a temperature value
	mathy = mathy * 100;
	mathy = mathy / 1024;
	ones = mathy % 10;	// Obtaining the ones digit for the temperature value
	tens = mathy / 10;	// Obtaining the tens digit for the temperature value
	USART0SendByte(tens + '0');	// Output the digits
	USART0SendByte(ones + '0');
	USART0SendByte('\n');
	USART0SendByte('\r');
	delay1s();	// Delay for 1 second before converting the next value
}


void USART0SendByte(char u8Data)
{
	//wait while previous byte is completed
	while(!(UCSR0A&(1<<UDRE0))){};
	// Transmit data
	UDR0 = u8Data;
}

void delay1s(){
	for(int i = 500; i > 0; i--)
	_delay_ms(2);
}