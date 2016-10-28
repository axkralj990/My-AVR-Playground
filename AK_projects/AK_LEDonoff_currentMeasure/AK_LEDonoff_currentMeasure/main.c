/*
 * AK_LEDonoff_currentMeasure.c
 *
 * Created: 10/17/2016 9:12:45 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>

int main(void)
{
	clock_prescale_set(clock_div_1);
	
	DDRB |= (1<<DDB5);
	
	/*
	// CTC mode, toggle OC1A on compare match
    TCCR1A |= (1<<COM1A0);
	//1024 prescaller
	TCCR1B |= (1<<CS12) | (1<<CS10) | (1<<WGM12);
	OCR1A = 488;
	*/
    while (1) 
    {
		PORTB ^= (1<<PORTB5);
		_delay_ms(500);
    }
}

