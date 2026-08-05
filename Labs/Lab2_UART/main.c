/*
 * GccApplication1.c
 *
 * Created: 2026/8/5 20:09:29
 * Author : 941107
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

int main(void)
{
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
			printf("%u ", n);
		}
	}
	
    /* Replace with your application code */
    while (1) 
    {
	}
}

