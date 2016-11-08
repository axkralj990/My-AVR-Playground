/*
 * tictoc.c
 *
 * Created: 11/7/2016 9:01:53 PM
 * Author : Aleksij
 */ 



#include <avr/io.h>
#include "tictoc.h"
#include <avr/interrupt.h>

volatile uint32_t timer_count = 0;

void init_tictoc()
{
	// Set 64 clock prescaller on timer 0
	TCCR0B |= (1<<CS01) | (1<<CS00);
	// Set Timer/Counter0 Overflow interrupt Enable
	TIMSK0 |= (1<<TOIE0);
	// Global interrupt enable
	sei();
}

void tic()
{
	TCNT0 = 0;
	timer_count = 0;
}

uint32_t toc()
{
	timer_count += TCNT0;
	return timer_count * 4;
}

ISR(TIMER0_OVF_vect)
{
	timer_count += 256;
}