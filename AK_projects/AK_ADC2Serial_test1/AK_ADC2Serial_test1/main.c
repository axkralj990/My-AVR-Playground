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
	double voltage;
	char voltage_str[16];
	char sensorValue_str[16];
	
    initUSART();
	init_ADC(3,10,8);
	
	//start_FreeRunning_ADC();
	
	DDRC |= (1<<DDC4);
	PORTC |= (1<<PORTC4);
	
    while (1) 
    {
		start_SingleConversion_ADC();
		sensorValue = read_ADC_10bit();
		//voltage = (double)sensorValue / 198.2558;
		//dtostrf(voltage,5,2,voltage_str);
		dtostrf(sensorValue,5,2,sensorValue_str);
		//printString(voltage_str); printString("_");
		//printString("35"); printString("_");
		//printString("40"); printString("_");
		//printString("50"); printString("_");
		printLine(sensorValue_str);
		
		_delay_ms(20);
    }
}

