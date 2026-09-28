/*
 * lab6 2.2.c
 *
 * Created: 2026/9/27 21:05:10
 * Author : 941107
 */ 


#define F_CPU 2000000UL 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "display.h"

void init_timer0(void) {
	TCCR0A = (1 << WGM01); 
	TCCR0B = (1 << CS02); 
	OCR0A = 77;                         
	TIMSK0 |= (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	send_next_character_to_display();
}

int main(void) {
	init_display();   
	init_timer0();    
	sei();            

	uint16_t count = 0;

	while (1) {
		seperate_and_load_characters(count, 0xFF);

		_delay_ms(400);

		count++;
		if (count > 9999) {
			count = 0; 
		}
	}
}