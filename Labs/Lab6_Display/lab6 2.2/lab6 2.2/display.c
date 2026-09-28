/*
 * display.c
 *
 * Created: 2026/9/28 21:24:24
 *  Author: 941107
 */ 

#include "display.h"

const uint8_t seg_pattern[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

static volatile uint8_t disp_characters[4] = {0, 0, 0, 0};

static volatile uint8_t disp_position = 0;

const uint8_t digit_select[4] = {0xE0, 0xD0, 0xB0, 0x70};

void init_display(void) {
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);
	
	DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

	PORTD |= 0xF0;
}

void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos) {
	disp_characters[0] = seg_pattern[(number / 1000) % 10];
	disp_characters[1] = seg_pattern[(number / 100) % 10]; 
	disp_characters[2] = seg_pattern[(number / 10) % 10];  
	disp_characters[3] = seg_pattern[number % 10];       

	if (decimal_pos < 4) {
		disp_characters[decimal_pos] |= 0x80;
	}
}

void send_next_character_to_display(void) {
	PORTC &= ~((1 << PC3) | (1 << PC5));

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

	PORTD |= 0xF0;

	PORTC |= (1 << PC5);
	PORTC &= ~(1 << PC5);

	PORTD = (PORTD & 0x0F) | digit_select[disp_position];

	disp_position = (disp_position + 1) % 4;
}