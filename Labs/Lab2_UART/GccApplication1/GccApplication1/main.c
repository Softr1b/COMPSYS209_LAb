/*
 * GccApplication1.c
 *
 * Created: 2026/8/5 20:09:29
 * Author : 941107
 */ 
#define  F_CPU 2000000UL

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>

void usart_init(uint16_t ubrr) {
	UBRR0L = (uint8_t)ubrr;			//save 12
	UBRR0H = (uint8_t)(ubrr >> 8);		//save 0
	UCSR0B = (1 << TXEN0);		//enable transmit
}

void usart_transmit(uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));	//wait to load
	UDR0 = data;	//load
}

int main(void) {
	usart_init(12);		//UBRR = 12
	//the code to find prime number
	uint16_t primes[62];
	uint16_t count = 0;
	uint16_t limit = 300;
	
	for(uint16_t n = 2; n <= limit; n++) {
		bool if_prime = true;
	
		for (uint16_t i = 2; i * i <= n; i++){
			if (n % i == 0) {
				if_prime = false;
				break;
		}
	}
	
	if (if_prime) {
		primes[count] = n;
		count++;
	}
}

	while(1) {
		//use a for loop to print the prime number one by one
		for (uint16_t i = 0; i < count; i++) {
			uint16_t num = primes[i];
			usart_transmit((num / 100) + '0');
			usart_transmit((num / 10) % 10 + '0');
			usart_transmit((num % 10) + '0');
		
			usart_transmit(',');
			usart_transmit(' ');
			_delay_ms(500);
		}
	}
	
	return 0;
}



