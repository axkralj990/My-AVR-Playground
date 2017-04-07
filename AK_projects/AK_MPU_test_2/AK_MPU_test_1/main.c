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
	uint8_t timing_bit = 0;
	uint16_t gyr[6];
	char gyrX_str[16], gyrY_str[16], gyrZ_str[16];
	uint8_t scale_selector = 1;
	
	DDRD |= (1<<DDD3);
	
	initUSART();
	clock_prescale_set(clock_div_1); // set clock to 16MHz
	MPU6050_init();
	
	/*
	MPU6050_set_gyroFS() set the gyro full scale range.
	gyroFS:
	0 - 250 deg/s, 131 LSB/(deg/s)
	1 - 500 deg/s, 65.5 LSB/(deg/s)
	2 - 1000 deg/s, 32.8 LSB/(deg/s)
	3 - 2000 deg/s, 16.4 LSB/(deg/s)
	*/
	MPU6050_set_gyroFS(scale_selector);
	
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
		//MPU6050_get_gyro(gyr);
		//MPU6050_get_accel(gyr);
		MPU6050_get_motion(gyr);
		itoa(gyr[3],gyrX_str,10);
		itoa(gyr[4],gyrY_str,10);
		itoa(gyr[5],gyrZ_str,10);
		printString(gyrX_str); printString("_");
		printString(gyrY_str); printString("_");
		printLine(gyrZ_str);
		_delay_ms(10);
		timing_bit = !timing_bit;
		statusLED(timing_bit);
    }
}

void statusLED(uint8_t status)
{
	//DDRD |= (1<<DDD3);
	if (status) {
		PORTD |= (1<<PORTD3);
	}
	else {
		PORTD &= ~(1<<PORTD3);
	}
	
}