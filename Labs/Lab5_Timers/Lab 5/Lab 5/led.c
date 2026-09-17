
/*
 * led.c
 *
 * Created: 17/09/2026 6:49:54 PM
 *  Author: zsha758
 */ 
#include "led.h"

#include <avr/io.h>
#include <util/delay.h>


void led_toggle(){
	//TODO: LED toggle code
	 PINB = (1<<PINB5);
}