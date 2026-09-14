#include "common.h"
#include "adc.h"
#include <avr/io.h>

void adc_init(void) {
	//5v reference voltage
	ADMUX = (1 << REFS0);
	//enable adc(125k clock)
	ADCSRA = (1 << ADEN) | (1 << ADPS2);
	ADCSRB = 0x00;
}

uint16_t adc_read(uint8_t chan) {
	//chanel 0 - 7
	ADMUX = (ADMUX & 0xF0) | (chan & 0x07);
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

//convert to mv
uint16_t adc_convert_mv(uint16_t raw_val) {
	return (uint16_t)(((uint32_t)raw_val * 5000UL) >> 10);
}