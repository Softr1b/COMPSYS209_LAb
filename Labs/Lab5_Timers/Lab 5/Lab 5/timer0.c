#include "timer0.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t counter = 0;

ISR(TIMER0_COMPA_vect) {
	counter++;
// 		if (counter == 10)
// 		{
// 			counter =0;
// 			led_toggle();
// 		}
}

void timer0_init() {
	TCCR0A = (0 << WGM00);
	TCCR0A = (0 << WGM01);
	TCCR0B = (0 << WGM02);
// 		TCCR0B = (1 << CS02);
	OCR0A = (78);
	TIMSK0 |= (1 << OCIE0A);
}

void timer0_start(void) {
	TCNT0 = (0x00);              
	counter = 0;   
	TCCR0B = (1 << CS02);         
}

void timer0_stop(void) {
	TCCR0B = 0x00;
}

uint32_t timer0_get_ticks(void) {
	uint8_t remaining_steps = TCNT0; 
	return ((uint32_t)counter * 256) + remaining_steps;
}

// 	uint8_t timer0_check_clear_compare(){
// 		if( TIFR0 & (1 << OCF0A )){ //TODO: check compare flag
// 			TIFR0 |= (1 << OCF0A);
// 			//Note: in datasheet this is done by writing 1 to the compare flag
// 		
// 			return 1;
// 		}
// 		return 0;
//		}