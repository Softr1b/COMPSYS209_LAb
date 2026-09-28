/*
 * display.h
 *
 * Created: 2026/9/28 21:24:43
 *  Author: 941107
 */ 
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>
#include <stdint.h>

void init_display(void);
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos);
void send_next_character_to_display(void);

#endif 