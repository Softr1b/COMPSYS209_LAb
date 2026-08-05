/*
 * GccApplication1.c
 *
 * Created: 2026/8/5 20:09:29
 * Author : 941107
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
	int limit = 300;
	
	for(int n = 2; n <= limit; n++) {
		bool if_prime = true;
	
		for (int i = 2; i * i <= n; i++){
			if (n % i == 0) {
				if_prime = false;
					break;
		}
	}
	
		if (if_prime) {
			printf("%d", n);
		}
	}
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

