/*
 * Lab 5.c
 *
 * Created: 17/09/2026 4:46:56 PM
 * Author : zsha758
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
	DDRB = (0xFF);
	DDRC = (0x00);
	DDRD = (0x00);
	
    while (1) 
    {
		 PORTB = (1 << PB5); 
		_delay_ms(375);
		 PORTB = (0 << PB5);
		_delay_ms(125);
    }
}

