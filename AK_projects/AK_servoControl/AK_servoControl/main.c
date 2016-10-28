/*
 * AK_servoControl.c
 *
 * Created: 10/24/2016 5:32:01 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include "AK_tictoc_lib.h"
#include <avr/power.h>

int main(void)
{
	clock_prescale_set(clock_div_1);
	
	uint32_t servo_timer = 0, timer_channel_1 = 0, timer_channel_2 = 0;
	uint8_t direction = 1;
	
	init_TICTOC();
	DDRC |= (1<<DDC4);
	PORTC = 0b00000000;
	
	DDRB |= (1<<DDB1);
	PORTB &= ~(1<<PORTB1);

	timer_channel_1 = 1000;
	timer_channel_2 = 1000;
	
    while (1) 
    {		
		//PORTB ^= (1<<PORTB1);
		
		if (direction == 1)
		{
			timer_channel_1 += 30;
			timer_channel_2 += 30;
			if (timer_channel_1 > 2000)
			{
				timer_channel_1 = 2000;
				timer_channel_2 = 2000;
				direction = 0;
			}
		}
		else if (direction == 0)
		{
			timer_channel_1 -= 30;
			timer_channel_2 -= 30;
			if (timer_channel_1 < 1000)
			{
				timer_channel_1 = 1000;
				timer_channel_2 = 1000;
				direction = 1;
			}
		}
		else
		{
			timer_channel_1 = 1500;
			timer_channel_2 = 1500;
		}
		
		//timer_channel_1 = 1500;
		//timer_channel_2 = 1500;
		
		while(toc() < 20000);
		
		tic();
		PORTC |= 0b00110000;
		
		while(PORTC >= 16)
		{
			servo_timer = toc();
			if(timer_channel_1 <= servo_timer) PORTC &= 0b11101111;
			if(timer_channel_2 <= servo_timer) PORTC &= 0b11011111;
		}	
    }
}

