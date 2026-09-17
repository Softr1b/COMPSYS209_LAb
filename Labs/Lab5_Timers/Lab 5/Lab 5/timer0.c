#include "timer0.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

ISR(TIMER0_COMPA_vect) {
	led_toggle();
}

void timer0_init() {
	TCCR0A = (1 << WGM01);
	TCCR0B = (1 << CS02);
	OCR0A = (78);
}


uint8_t timer0_check_clear_compare(){
	if( TIFR0 & (1 << OCF0A )){ //TODO: check compare flag
		//TODO: clear compare flag.
		TIFR0 |= (1 << OCF0A);
		//Note: in datasheet this is done by writing 1 to the compare flag
		
		return 1;
	}
	return 0;
}