/*
 * AK_SD_1.c
 *
 * Created: 3/7/2018 3:30:50 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "diskio.h"
#include "pff.h"

int main(void)
{
	FATFS fs;
	
	BYTE res;
	
	//res = pf_mount(&fs);
	res = 1;
	DDRB |= (1<<PORTB5);
	
    while (1) 
    {
	if (res == FR_OK) {
		PORTB |= (1<<PORTB5);
		_delay_ms(500);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(500);
	} else {
		PORTB |= (1<<PORTB5);
		_delay_ms(100);
		PORTB &= ~(1<<PORTB5);
		_delay_ms(100);
	}
    }
}

