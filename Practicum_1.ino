/*
* Practicum1.c
*
* Created: 8/24/2025 2:36:25 PM
* Author : Huawei D15
*/

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
// Segment codes for displaying 0-9 on a common anode 7-segment display
unsigned char TENS[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
unsigned char ONES[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
unsigned char ones, tens;

DDRB |= 0x07;  // Consider lower 3 bits as outputs |(1<<0)|(
DDRC |= 0x0F;  // Bits 0-3 as outputs
DDRD |= 0xFF;  // All bits of PORTD as outputs

// ADC setup: Enable ADC, prescaler 128
ADCSRA = 0x87;
// Set Vref = AVCC, ADC channel = ADC4
ADMUX = 0x44;

while (1)
{
// Start ADC conversion
ADCSRA |= (1 << ADSC);
// Wait for the conversion to finish
for(int i=0; i<3;i++)
{
	while (ADCSRA & (1 << ADSC));
	_delay_ms(10);
	
}

// Read ADC value
unsigned int adc_value = ADC;

// Convert ADC value to temperature in Celsius
// LM35 gives 10mV per degree Celsius, so:
// Temperature = (ADC_value / 1024) * 500
// Simplified as below
unsigned char temperature = (adc_value * 500)/1023;
              

// Separate the temperature into tens and ones digits
ones = temperature % 10;
tens = temperature / 10;

// Display the digits
PORTD = ONES[ones];                // Display ones digit on PORTD
PORTB = (TENS[tens] & 0xF0) >> 4;  // Display higher nibble of tens on               PORTB
PORTC = (TENS[tens] & 0x0F);       // Display lower nibble of tens on PORTC

_delay_ms(1000);  // 1-second delay
}
return  0;
}