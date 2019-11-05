/*
 * elan_blink.c
 *
 * Created: 10/28/2019 8:20:33 PM
 * Author : Aleksij
 */ 

#define F_CPU 16000000L // nas clock je 16MHz

#include <avr/io.h>
#include <util/delay.h>

//DDRB = 1 << PB5; // PB5 je konstanta, ki pomeni 5. Zazeljena uporaba zaradi berljivosti

int main(void)
{
	DDRB |= (1 << DDB5);
	while (1) {
			PORTB |= (1<<PB5);
			_delay_ms(1000);
			PORTB &= ~(1<<PB5);
			_delay_ms(50);
	}
	return(0);
}

