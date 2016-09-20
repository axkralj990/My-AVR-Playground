/*
 * AK_TimerStuff_2.c
 *
 * Created: 9/20/2016 11:57:14 AM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/power.h>

#include "AK_tictoc_lib.h"

int main(void)
{
	uint32_t microTime = 0;
	char str[64];
	
	// set F_CPU to 8MHz
	clock_prescale_set(clock_div_1);
	
    initUSART();
	init_TICTOC();

	
	DDRC |=   (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0); // config PORTC4 as output
	PORTC |= (1<<PORTC5) | (1<<PORTC4) | (1<<PORTC3) | (1<<PORTC2) | (1<<PORTC1) | (1<<PORTC0); // set PORTC4 to HIGH
	
	//sei(); // enable global interrupts
	
    while (1) 
    {
		tic();
		_delay_us(500);
		microTime = toc();
		ultoa(microTime,str,10);
		printLine(str);
		_delay_ms(20);
    }
}