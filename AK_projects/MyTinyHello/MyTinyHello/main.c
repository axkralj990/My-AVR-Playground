/*
 * MyTinyHello.c
 *
 * Created: 3/29/2017 9:51:58 AM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
//#define F_CPU 1000000


int main(void)
{
	DDRB |= (0b00001000);
	PORTB |= (0b00001000);
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(50);
		PORTB ^= (0b00001000);
    }
}

