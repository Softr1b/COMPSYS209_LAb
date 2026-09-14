/*
 * GccApplication1.c
 *
 * Created: 2026/9/14 21:05:26
 * Author : 941107
 */ 

#include "common.h"
#include <util/delay.h>
#include "adc.h"
#include <avr/io.h>

#define NUM_SAMPLES 40

// UART help function
void uart_init(void) {
	UBRR0L = 12; // 9600 Baud @ F_CPU = 2MHz
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_char(char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void uart_send_str(const char* s) {
	while (*s) uart_send_char(*s++);
}

void uart_send_num(uint16_t num) {
	char buf[6];
	int i = 0;
	if (num == 0) { uart_send_char('0'); return; }
	while (num > 0) { buf[i++] = (num % 10) + '0'; num /= 10; }
	while (i > 0) uart_send_char(buf[--i]);
}


int main(void) {
	uint16_t rv1_samples[NUM_SAMPLES];

	adc_init();
	uart_init();

	while (1) {
		// get samples from ADC2
		for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
			rv1_samples[i] = adc_convert_mv(adc_read(2));
			_delay_ms(1);
		}

		//print
		uart_send_str("RV1_mV\r\n");
		for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
			uart_send_num(rv1_samples[i]);
			uart_send_str("\r\n");
		}
		uart_send_str("\r\n");

		_delay_ms(2000);
	}
}
