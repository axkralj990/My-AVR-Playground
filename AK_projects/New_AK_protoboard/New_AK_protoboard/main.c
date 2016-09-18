/*
 * New_AK_protoboard.c
 *
 * Created: 9/17/2016 12:56:50 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC |= (1<<DDC4);
	PORTC |= (1<<PORTC4);
	
    while (1) 
    {
		_delay_ms(100);
		PORTC &= ~(1<<PORTC4);
		_delay_ms(750);
		PORTC |= (1<<PORTC4);
    }
}

