/*
 * elan_mpu6050.c
 *
 * Created: 10/28/2019 9:33:35 PM
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
	int16_t acc[3];
	char accX_str[16], accY_str[16], accZ_str[16];
	
	// set status LED as output
	DDRB |= (1<<DDB5);
	
	initUSART();
	clock_prescale_set(clock_div_1); // set clock to 16MHz
	MPU6050_init();
	
	if (MPU6050_test_I2C()) {
		printLine("=== IMU working properly ===");
		statusLED(1);
	}
	else {
		statusLED(1);
		printLine("=== IMU ERROR ===");
		for(uint8_t i = 0; i < 50; i++){
			statusLED(0);
			_delay_ms(50);
			statusLED(1);
			_delay_ms(50);
			printString(".");
		}
	}
	
	printLine("Calibrating Accelerometer...");
	MPU6050_auto_set_accel_bias();
	printLine("Calibration OK");
	
	MPU6050_set_accelFS(2);

    while (1) 
    {
		MPU6050_get_accel(acc);
		itoa(acc[0],accX_str,10);
		itoa(acc[1],accY_str,10);
		itoa(acc[2],accZ_str,10);
		printString(accX_str); printString(" ");
		printString(accY_str); printString(" ");
		printLine(accZ_str);
		_delay_ms(10);
		timing_bit = !timing_bit;
		statusLED(timing_bit);
    }
}

void statusLED(uint8_t status)
{
	if (status) {
		PORTB |= (1<<PORTB5);
	}
	else {
		PORTB &= ~(1<<PORTB5);
	}
	
}