/*
 * LAB6.c
 *
 * Created: 2026/9/26 20:19:04
 * Author : 941107
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint8_t numbers[10] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

volatile uint8_t counter = 0£»
volatile uint8_t active_digit = 0;

void show_num(uint8_t num) {
	uint8_t pattern = numbers[num];
	PORTC = (pattern & 0x3F);
	
	if (pattern & (1 << 6)) {
		PORTB |= (1 << PB4);
		} else {
		PORTB &= ~(1 << PB4);
	}
}

void timer0_init(void) {
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS00);
	OCR0A = 97;
	TIMSK0 |= (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	uint8_t shi = counter / 10;
	uint8_t ge  = counter % 10£»

	PORTB |= (1 << PB0) | (1 << PB1);

	if (active_digit == 0) {
		show_num(shi);
		PORTB &= ~(1 << PB0); 
		active_digit = 1;
		} else {
		show_num(ge);
		PORTB &= ~(1 << PB1);
		active_digit = 0;
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
	
	timer0_init();
	sei();

	while (1) {
		for (uint8_t i = 0; i < 10; i++) {
			_delay_ms(10);

			if (!(PINB & (1 << PB7))) {
				counter = 0;
				break;
			}
		}

		counter++;
		if (counter > 99) {
			counter = 0;
		}
	}

	return 0;
}
