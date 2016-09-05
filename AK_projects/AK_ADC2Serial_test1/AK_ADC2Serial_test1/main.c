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

int main(void)
{
	uint16_t sensorValue;
	char str[16];
	
    initUSART();
	init_ADC(5,10,8);
	
	//start_FreeRunning_ADC();
	
	DDRC |= (1<<DDC4);
	PORTC |= (1<<PORTC4);
	
    while (1) 
    {
		start_SingleConversion_ADC();
		sensorValue = read_ADC_10bit();
		itoa(sensorValue,str,10);
		printString(str);
		transmitByte(10);
		_delay_ms(20);
    }
}

