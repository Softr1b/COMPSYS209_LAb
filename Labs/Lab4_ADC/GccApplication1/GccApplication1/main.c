#include "common.h"
#include <util/delay.h>
#include "adc.h"
#include <avr/io.h>

#define NUM_SAMPLES 40

void uart_init(void) {
	UBRR0L = 12;
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void uart_send_char(char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

void uart_send_str(const char* s) {
	while (*s) {
		uart_send_char(*s++);
	}
}

void uart_send_num(uint16_t num) {
	char buf[6];
	int i = 0;
	if (num == 0) {
		uart_send_char('0');
		return;
	}
	while (num > 0) {
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}
	while (i > 0) {
		uart_send_char(buf[--i]);
	}
}

int main(void) {
	uint16_t adc0_samples[NUM_SAMPLES];
	uint16_t adc1_samples[NUM_SAMPLES];

	adc_init();
	uart_init();

	while (1) {
		for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
			adc0_samples[i] = adc_convert_mv(adc_read(0));
			adc1_samples[i] = adc_convert_mv(adc_read(1));
			_delay_ms(1);
		}

		uart_send_str("ADC0_mV, ADC1_mV\r\n");
		for (uint8_t i = 0; i < NUM_SAMPLES; i++) {
			uart_send_num(adc0_samples[i]);
			uart_send_str(", ");
			uart_send_num(adc1_samples[i]);
			uart_send_str("\r\n");
		}
		uart_send_str("\r\n");

		_delay_ms(2000);
	}
}