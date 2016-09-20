/*
 * Servo_control_1.c
 *
 * Created: 9/20/2016 5:45:16 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdlib.h>
#include "AK_tictoc_lib.h"
#include "USART.h"


int main(void)
{
	clock_prescale_set(clock_div_1);
	
	// set LED and servo ports as output
    DDRC |= (1<<DDC5) | (1<<DDC3);
	
	// LED ON
	PORTC |= (1<<PORTC3);
	PORTC &= ~(1<<PORTC5);
	
	initUSART();
	init_TICTOC();
	
	uint8_t servo_receive = 150;
	uint16_t servo_signal = servo_receive*10;
	uint32_t micros = 0;
	//char str[16];
	
	_delay_ms(1000);
	
    while (1) 
    {
		
		//servo_receive = getNumber();
		servo_signal = 2000;
		
		tic();
		PORTC |= (1<<PORTC5);
		//_delay_us(1000);
		//PORTC &= ~(1<<PORTC5);
		
		while (PORTC >= 40)
		{
			micros = toc();
			if(servo_signal <= micros)
			{
				PORTC &= ~(1<<PORTC5);
			}
		}
		
		_delay_ms(20);
    }
}

