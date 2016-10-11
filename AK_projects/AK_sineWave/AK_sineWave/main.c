/*
 * AK_ADC2Serial_test1.c
 *
 * Created: 9/2/2016 3:31:05 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include <stdlib.h>
#include <math.h>

int main(void)
{
	uint16_t time = 0;
	float w = 2*M_PI*2/1024;
	float wave1;
	char wave1_str[16];
	
    initUSART();
	
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12);
	//OCR1A = 62813;
	OCR1A = 500;
	
    while (1) 
    {
		time = TCNT1;
		wave1 = sin(w*(double)time);
		//wave1 = (float)time/500;
		dtostrf(wave1,3,4,wave1_str);
		
		printString(wave1_str);
		printString("_");
		printLine("0.777");
		
		//_delay_ms(5);
    }
}

