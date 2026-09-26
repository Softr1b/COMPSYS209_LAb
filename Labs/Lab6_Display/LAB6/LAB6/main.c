/*
 * LAB6.c
 *
 * Created: 2026/9/26 20:19:04
 * Author : 941107
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

uint8_t counter = 0;
uint8_t numbers[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void disPlay(uint8_t count) {
	uint8_t pattern = numbers[count];
	
	PORTC = (pattern & 0x3F);

	if (pattern & (1 << 6)) {
		PORTB |= (1 << PB4); 
		} else {
		PORTB &= ~(1 << PB4);
	}
}


int main(void)
{
	DDRB &= ~(1 << PB7);
	PORTB |= (1 << PB7);
	
	DDRB |= (1 << PB0) | (1 << PB1);
	DDRB |= (1 << PB4);
	DDRC = (0xFF);

	PORTB |= (1 << PB0);
	PORTB &= ~(1 << PB1);
	
    /* Replace with your application code */
    while (1) {
		if (counter > 9) {
			counter = 0;
		}
		
		disPlay(counter);
		
		for (uint8_t i = 0; i < 10; i++) {
			_delay_ms(10);
			
			if (!(PINB & (1 << PB7)))
			{
				counter = 0;
				break;
			}
		}
	counter++;
	}
	return 0;
}

