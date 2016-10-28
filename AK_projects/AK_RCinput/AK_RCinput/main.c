/*
 * AK_RCinput.c
 *
 * Created: 10/26/2016 8:05:31 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <stdlib.h>
#include <util/delay.h>
#include "AK_tictoc_lib.h"
#include "USART.h"

volatile uint8_t last_channel_1 = 0;
volatile uint32_t timer_1, current_time;
volatile uint32_t receiver_input;

int main(void)
{	
	// 8MHz clock
	clock_prescale_set(clock_div_1);
	
	char channel_1_str[16];
	
    PCICR |= (1 << PCIE0);
    PCMSK0 |= (1 << PCINT0);
    PCMSK0 |= (1 << PCINT1);
    PCMSK0 |= (1 << PCINT2);
    PCMSK0 |= (1 << PCINT3);
	
	initUSART();
	init_TICTOC();
	
	sei();
	
    while (1) 
    {
		//tic();
		dtostrf(receiver_input,5,2,channel_1_str);
		printLine(channel_1_str);
		_delay_ms(4);
    }
}

ISR(PCINT0_vect){
	//Channel 1=========================================
	if(PINB & 0b00000001){                                        //Is input 8 high?
		if(last_channel_1 == 0){                                   //Input 8 changed from 0 to 1
			last_channel_1 = 1;                                      //Remember current input state
			timer_1 = toc();                                  //Set timer_1 to current_time
		}
	}
	else if(last_channel_1 == 1){                                //Input 8 is not high and changed from 1 to 0
		last_channel_1 = 0;                                        //Remember current input state
		receiver_input = toc() - timer_1;
		tic();
	}
}