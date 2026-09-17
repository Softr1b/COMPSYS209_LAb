/*
 * Lab 5.c
 *
 * Created: 17/09/2026 4:46:56 PM
 * Author : zsha758
 */ 

#define F_CPU 2000000UL

#include "timer0.h"
#include "led.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	//TODO: set direction of LED port to OUTPUT
	DDRB = (0xFF);
	DDRC = (0x00);
	DDRD = (0x00);
	
	timer0_init();
	sei(); 
	
	while(1){
		if(timer0_check_clear_compare()) {
			led_toggle();
		}
	}
}
