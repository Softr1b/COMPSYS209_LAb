/*
 * lab6 2.2.c
 *
 * Created: 2026/9/27 21:05:10
 * Author : 941107
 */ 

#include <avr/io.h>

const uint8_t seg_pattern[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

static volatile uint8_t disp_characters[4]={0,0,0,0};
	
static volatile uint8_t disp_position=0;
	
void init_display() {
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);
	DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
	
	PORTD &= ~(1 << PD7);
	PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6);
}

void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos){
	disp_characters[0] = seg_pattern[(number / 1000) % 10]; 
	disp_characters[1] = seg_pattern[(number / 100) % 10]; 
	disp_characters[2] = seg_pattern[(number / 10) % 10];   
	disp_characters[3] = seg_pattern[number % 10];         

	if (decimal_pos < 4) {
		disp_characters[decimal_pos] |= 0x80;
	}
}


void send_next_character_to_display(void) {
	uint8_t pattern = disp_characters[disp_position];

	for (int8_t i = 7; i >= 0; i--) {
		if (pattern & (1 << i)) {
			PORTC |= (1 << PC4); 
			} else {
			PORTC &= ~(1 << PC4); 
		}
		PORTC |= (1 << PC3);
		PORTC &= ~(1 << PC3);
	}

	PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

	PORTC |= (1 << PC5);
	PORTC &= ~(1 << PC5);

	switch (disp_position) {
		case 0: PORTD &= ~(1 << PD4); break; 
		case 1: PORTD &= ~(1 << PD5); break; 
		case 2: PORTD &= ~(1 << PD6); break; 
		case 3: PORTD &= ~(1 << PD7); break; 
	}

	disp_position = (disp_position + 1) % 4;
}
	
// 		{
// 			PORTC &= ~((1 << PC3) | (1 << PC5));
// 		
// 			for (int8_t i = 7; i >= 0; i--) {
// 				if (pattern & (1 << i)) {
// 					PORTC |= (1 << PC4);
// 					} else {
// 					PORTC &= ~(1 << PC4);
// 				}
// 				PORTC |= (1 << PC3);
// 				PORTC &= ~(1 << PC3);
// 			}
// 			PORTC |= (1 << PC5);
// 			PORTC &= ~(1 << PC5);
// 		}

#include <avr/interrupt.h>

void init_timer0(void) {
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02) | (1 << CS00); 
	OCR0A = 48;
	TIMSK0 |= (1 << OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
	send_next_character_to_display();
}

int main(void)
{
	init_display();
	init_timer0();
	sei(); 

	uint16_t count = 0;

	while (1)
	{
		seperate_and_load_characters(count, 0xFF);
		
		for (volatile uint32_t i = 0; i < 20000; i++);

		count++;
		if (count > 9999) {
			count = 0;
		}
	}
}