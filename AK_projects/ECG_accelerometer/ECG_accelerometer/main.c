/*
 * ECG_accelerometer.c
 *
 * Created: 9/4/2017 10:00:25 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdlib.h>
#include "AK_MPU6050_lib.h"
#include "tictoc.h"
#include "USART.h"
#include "i2c_master.h"


int main(void)
{
    int16_t acc[3];
	unsigned long timer = 0;
	char timer_str[64];
	char accZ_str[16];
    //char accX_str[16], accY_str[16], accZ_str[16];
    
	initUSART();
	clock_prescale_set(clock_div_1); // set clock to 16MHz
	MPU6050_init();
	init_tictoc();
	
		MPU6050_set_accelFS(0);
		
		if (MPU6050_test_I2C()) {
			printLine("=== IMU working properly ===");
		}
		else {
			printLine("=== IMU ERROR ===");
			for(uint8_t i = 0; i < 50; i++){
				_delay_ms(50);
				printString(".");
			}
		}
		
	MPU6050_set_dlpf(2);
	
	tic();
	
    while (1) 
    {
		timer = millis();
		MPU6050_get_accel(acc);
		itoa(acc[0],accZ_str,10);
		ultoa(timer,timer_str,10);
		//itoa(acc[1],accY_str,10);
		//itoa(acc[2],accZ_str,10);
		//printString(accX_str); printString(" ");
		//printString(accY_str); printString(" ");
		printString(timer_str); printString("_");
		printLine(accZ_str);
		_delay_ms(1);
    }
}

