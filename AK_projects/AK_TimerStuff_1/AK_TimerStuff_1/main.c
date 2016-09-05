/*
 * AK_ADC2Serial_test1.c
 *
 * Created: 9/2/2016 3:31:05 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "AK_ADC_lib.h"
#include "USART.h"
#include <stdlib.h>
#include <avr/interrupt.h>

volatile uint8_t q_second_ctn = 0; // quarter-second timer

int main(void)
{
	uint8_t sensorValue;
	
	char str[16];
	
    initUSART();
	init_ADC(5,8,8); // init_ADC(AD5,8-bit,prescale /8)
	
	// Timer initialization =========
	TCCR0B |= (1<<CS02) | (1<<CS00); // clock prescaller 1024
	TCCR0A |= (1<<WGM01); // CTC mode
	//TCCR0A |= (1<<COM0A0); // toggle OC0A on Compare Match
	OCR0A = 244; // OCR value to generate an inerrupt every 0.25s
	TIMSK0 |= (1<<OCIE0A); // Timer/Counter0 Output Compare Match Interrupt Enable
	// ==============================
	
	DDRC |= (1<<DDC4); // config PORTC4 as output
	PORTC |= (1<<PORTC4); // set PORTC4 to HIGH
	
	sei(); // enable global interrupts
	
    while (1) 
    {
		// ADC ==============================
		start_SingleConversion_ADC();
		sensorValue = read_ADC_8bit();
		// =================================
		
		// USART ============================
		itoa(sensorValue,str,10); // convert integer to string
		printString(str); // send string via serial
		transmitByte(10); // send "/n"
		// =================================
		
		// TIMER ===========================
		if (q_second_ctn >= 8) { // toggle PORTC4 state every x*0.25s
			q_second_ctn = 0;
			PORTC ^= (1<<PORTC4);
		}
		// =================================
		_delay_ms(20);
    }
}

ISR(TIMER0_COMPA_vect) {
	q_second_ctn += 1; // increment quarter-second counter
}
