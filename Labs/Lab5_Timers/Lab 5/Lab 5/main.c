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


volatile uint32_t high_level_ticks = 0; 
volatile uint8_t measure_flag = 0;

ISR(INT0_vect) {
	static uint8_t is_rising = 1;

	if (is_rising) {
		timer0_start();
		
		EICRA = (1 << ISC01);
		is_rising = 0;
		} else {
		timer0_stop();
		high_level_ticks = timer0_get_ticks(); 
		
		EICRA = (1 << ISC01) | (1 << ISC00);
		is_rising = 1;
		
		measure_flag = 1; 
	}
}

void int0_init(void) {
	EICRA |= (1 << ISC01) | (1 << ISC00); 
	EIMSK |= (1 << INT0);                 
}

int main(void) {
	DDRB = 0xFF; 
	DDRD = 0x00; 

	timer0_init();
	int0_init();
	sei();       
	while (1) {
		if (measure_flag) {
			measure_flag = 0;
			
			double t_high = high_level_ticks * 0.000128;
			double frequency = 1.0 / (2.0 * t_high);

		}
	}
}




// 	int main(void){
// 		//TODO: set direction of LED port to OUTPUT
// 		DDRB = (0xFF);
// 		DDRC = (0x00);
// 		DDRD = (0x00);
// 	
// 		timer0_init();
// 		sei(); 
// 	
// 		while(1){
// 	// 		if(timer0_check_clear_compare()) {
// 	// 			led_toggle();
// 	// 		}
// 		}
// 	}
