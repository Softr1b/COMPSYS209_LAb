/*
 * disPlay.h
 *
 * Created: 2026/9/26 22:32:50
 *  Author: 941107
 */ 
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <avr/io.h>
#include <stdint.h>

void init_display(void);

void update_display_buffer(uint8_t number);

void refresh_display(void);

#endif