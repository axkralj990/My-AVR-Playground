/*
 * AK_servo_timer1.c
 *
 * Created: 5/30/2017 4:28:07 PM
 * Author : Aleksij
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	uint16_t pulseWidth = 1001;
	int direction = 1;
	
	TCCR1A |= (1<<COM1A1) | (1<<WGM11);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11); // prescale 8
	ICR1 = 39999;
	DDRB |= (1<<PINB1);
    while (1) 
    {
		OCR1A = 2*pulseWidth;
		pulseWidth = pulseWidth + 10*direction;
		if (pulseWidth >= 2200)
		{
			direction = -1;
		}
		else if (pulseWidth <= 900)
		{
			direction = 1;
		}
		_delay_ms(2);
    }
}

