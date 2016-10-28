/*
 * AK_CrystalVsRC.c
 *
 * Created: 10/27/2016 5:13:30 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "AK_tictoc_lib.h"
#include <stdlib.h>
#include <avr/power.h>
#include <avr/interrupt.h>

volatile uint32_t time = 0;

int main(void)
{
	//clock_prescale_set(clock_div_1);
	
	uint8_t state;
	state = 0;
	
	
	initUSART();
	init_TICTOC();
	TCCR1B |= (1<<WGM12);
	OCR1A = 2500;
	TIMSK1 |= (1<<OCIE1A);
	sei();
	
	//tic();
	
    while (1) 
    {
		
		if (time >= 10000)
		{
			if (state == 1)
			{
				state = 0;
			}
			else
			{
				state = 1;
			}
			time = 0;
		}
		
		printByte(state);
		transmitByte(10);
    }
}

ISR(TIMER1_COMPA_vect)
{
	time += 10;
	//tic();
}

