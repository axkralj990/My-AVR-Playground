/*
 * tinyTest.c
 *
 * Created: 11/1/2019 10:20:06 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>

int main(void)
{
	DDRB |= (1<<DDB3);
    while (1) 
    {
		PORTB |= (1<<PB3);
		_delay_ms(500);
		PORTB &= ~(1<<PB3);
		_delay_ms(500);
    }
}

