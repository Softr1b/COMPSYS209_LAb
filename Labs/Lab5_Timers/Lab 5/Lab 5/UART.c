/*
 * UART.c
 *
 * Created: 2026/9/21 18:50:48
 *  Author: 941107
 */ 
#include "UART.h"
#include <avr/io.h>

void uart_init(uint32_t baud, uint32_t f_cpu) {
	uint16_t ubrr = (f_cpu / (16 * baud)) - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)(ubrr);
	UCSR0B = (1 << TXEN0);                  
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}

void uart_send_char(char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void uart_send_string(const char *str) {
	while (*str) {
		uart_send_char(*str++);
	}
}