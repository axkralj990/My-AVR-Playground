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
	uint8_t potentiometer;
	float freq;
	char wave1_str[16];
	
    initUSART();
	init_ADC(3,8,8);
	
	TCCR1B |= (1<<WGM12) | (1<<CS10) | (1<<CS12);
	OCR1A = 62813;
	//OCR1A = 500;
	
    while (1) 
    {
		start_SingleConversion_ADC();
		potentiometer = read_ADC_8bit();
		freq = (float)potentiometer/25.5;
		w = 2*M_PI*freq/1024;
		time = TCNT1;
		wave1 = sin(w*(float)time);
		dtostrf(wave1,3,4,wave1_str);
		
		printLine(wave1_str);
		
		//_delay_ms(5);
    }
}

