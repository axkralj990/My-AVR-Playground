/*
 * AK_testingMyMilllis.c
 *
 * Created: 11/7/2016 9:25:13 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"
#include "tictoc.h"
#include <stdlib.h>
#include <avr/interrupt.h>


int main(void)
{
	uint32_t time1 = 0, dt = 0, time2 = 0;
	char measuredTime1[16], measuredTime2[16], measuredTime3[16];
	
	init_tictoc();
	initUSART();
	
    while (1) 
    {
		printLine("Measurement 1 - 100000us:");
		time1 = millis();
		_delay_ms(1000);
		dt = millis()-time1;
		dtostrf(dt,5,2,measuredTime1);
		printLine(measuredTime1);
		
		printLine("Measurement 2 - 500us:");
		time1 = micros();
		_delay_us(500);
		dt = micros()-time1;
		dtostrf(dt,5,2,measuredTime2);
		printLine(measuredTime2);
		
		printLine("Measurement 3 - 80us:");
		time1 = micros();
		_delay_us(80);
		dt = micros()-time1;
		dtostrf(dt,5,2,measuredTime3);
		printLine(measuredTime3);

		_delay_ms(3000);
    }
}