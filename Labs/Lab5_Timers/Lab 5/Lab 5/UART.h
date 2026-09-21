/*
 * UART.h
 *
 * Created: 2026/9/21 18:50:21
 *  Author: 941107
 */ 
#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(uint32_t baud, uint32_t f_cpu);
void uart_send_char(char c);
void uart_send_string(const char *str);

#endif