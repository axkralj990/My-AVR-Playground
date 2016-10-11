/*
 * AK_ultrasonic.c
 *
 * Created: 9/25/2016 12:17:27 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "USART.h"

#define TRIGPULSE 10
#define CONVERT2CM 58

void init_TICTOC();
void tic();
uint32_t toc();

volatile uint32_t echo_time = 0;
volatile uint8_t last_state = 0, beep_enable = 1;
volatile uint16_t loop_time_ctn = 0, beep_ctn = 0; // loop time count
volatile float beep_period = 0;

int main(void)
{
	clock_prescale_set(clock_div_1); // set clock to 8MHz
	
    double distance;
	char str[16];
	uint8_t no_obstacle_T = 33; //ms
	uint8_t near_dist_T = 40; //ms
	uint16_t far_dist_T = 800; //ms
	
	initUSART();
	init_TICTOC();
	
	// init TIMER/COUNTER 0 for loop time measurement
	TCCR0A |= (1<<WGM01); // CTC mode
	TCCR0B |= (1<<CS02); // prescaler 256 => tic = 32us
	TIMSK0 |= (1<<OCIE0A); // output compare match A interrupt enable
	OCR0A = 31; // trigger an interrupt every 992us --> 1ms
	
	// set pin change interrupt 0
	PCICR |= (1 << PCIE0); //Set PCIE0 to enable PCMSK0 scan. PCINT[7:0]
	PCMSK0 |= (1 << PCINT0); //Set PCINT0 to trigger an interrupt on state change.
	
	DDRB |= (1<<DDB1);
	PORTB = 0b00000000;
	
	DDRC |= (1<<DDC1);
	PORTC |= (1<<PORTC1);
	
	sei();
	
    while (1) 
    {
		cli();
		loop_time_ctn = 0;
		tic();
		PORTB |= (1<<PORTB1);
		while(PORTB >= 2){
			if(toc() <= TRIGPULSE) PORTB &= ~(1<<PORTB1);
		}
		sei();
		
		while(loop_time_ctn <= 20);
		
		distance = echo_time / (double)CONVERT2CM;
		
		dtostrf(distance,5,1,str);
		printLine(str);
		
		
		// beeper setup
		beep_period = 1000/((-0.3/CONVERT2CM)*(float)echo_time+31);
		
		if(beep_period <= near_dist_T && beep_period > no_obstacle_T){
			beep_enable = 0;
			PORTC |= (1<<PORTC1);
		}
		else if(beep_period >= far_dist_T || beep_period <= near_dist_T){
			beep_enable = 0;
			PORTC &= ~(1<<PORTC1);
		}
		else{
			beep_enable = 1;
		}

	}
}

ISR(TIMER0_COMPA_vect){
	loop_time_ctn++;
	beep_ctn++;
	if(beep_period <= beep_ctn && beep_enable == 1){
		PORTC ^= (1<<PORTC1);
		beep_ctn = 0;
	}
}

ISR(PCINT0_vect){
	if(PINB & 0b00000001){ //Is input 8 high?
		if(last_state == 0){ //Input 8 changed from 0 to 1
			last_state = 1; //Remember current input state
			tic();
		}
	}
	else if(last_state == 1){ //Input 8 is not high and changed from 1 to 0
		last_state = 0; //Remember current input state
		echo_time = toc();
	}
}

void init_TICTOC()
{
	TCCR1B |= (1<<CS11); // clock prescaler 8
	// WGM -> NORMAL mode is default
}

void tic()
{
	TCNT1 = 0;
}

uint32_t toc()
{
	uint32_t micro_time = TCNT1;
	return micro_time;
}
