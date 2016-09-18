/*
 * AK_MPU_test_1.c
 *
 * Created: 9/18/2016 12:24:07 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include "AK_MPU6050_lib.h"
#include <avr/power.h>
#include <util/delay.h>
#include "USART.h"
#include <stdlib.h>
#include "i2c_master.h"

void statusLED(uint8_t status);

int main(void)
{
	uint16_t acc[3];
	char accX_str[16], accY_str[16], accZ_str[16];
	
	initUSART();
	clock_prescale_set(clock_div_1); // set clock to 8MHz
	MPU6050_init();
	MPU6050_set_accelFS(3);
	
	//statusLED_ON();
	
	if (MPU6050_test_I2C()) {
		printLine("=== IMU working properly ===");
		statusLED(1);
	}
	else {
		statusLED(1);
		printLine("=== IMU ERROR ===");
		while(1){
			statusLED(0);
			_delay_ms(50);
			statusLED(1);
			_delay_ms(50);
		}
	}
	
    while (1) 
    {
		MPU6050_get_accel(acc);
		itoa(acc[0],accX_str,10);
		itoa(acc[1],accY_str,10);
		itoa(acc[2],accZ_str,10);
		printString(accX_str); printString("_");
		printString(accY_str); printString("_");
		printLine(accZ_str);
		_delay_ms(15);
    }
}

void statusLED(uint8_t status)
{
	DDRD |= (1<<DDD5);
	if (status) {
		PORTD |= (1<<PORTD5);
	}
	else {
		PORTD &= ~(1<<PORTD5);
	}
	
}