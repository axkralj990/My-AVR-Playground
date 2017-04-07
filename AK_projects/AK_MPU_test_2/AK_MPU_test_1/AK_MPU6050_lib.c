/*
 * AK_MPU6050_lib.c
 *
 * Created: 9/18/2016 11:20:39 AM
 *  Author: Aleksij Kraljic
 *
 * Library created for purposes of developing ATMEGA328P based quadcopter flight controller.
 * Library requires "i2c_master.h" library for TWI communications written by g4lvanix (source: https://github.com/g4lvanix/I2C-master-lib).
 */ 

#include <avr/io.h>
#include "AK_MPU6050_lib.h"
#include "i2c_master.h"

void MPU6050_init()
{
	i2c_init();
	MPU6050_set_clockSource(1);
	MPU6050_set_sleepMode(0);
	MPU6050_set_gyroFS(0);
	MPU6050_set_accelFS(0);
}

uint8_t MPU6050_test_I2C()
{
	unsigned char Data = 0x00;
	uint8_t MPU6050_test = 0;
	
	i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_WHO_AM_I, &Data, 1);
	
	if(Data == 0x68)
	{
		MPU6050_test = 1;
	}
	else
	{
		MPU6050_test = 0;
	}
	return MPU6050_test;
}

void MPU6050_get_motion(uint16_t* motion)
{
	uint8_t motion_all[14];
	i2c_readReg(MPU6050_ADDRESS,MPU6050_RA_ACCEL_XOUT_H,motion_all,14);
	motion[0] = (((uint16_t)motion_all[0]) << 8) | motion_all[1];
	motion[1] = (((uint16_t)motion_all[2]) << 8) | motion_all[3];
	motion[2] = (((uint16_t)motion_all[4]) << 8) | motion_all[5];
	
	// temperature data
	//motion[0] = (((uint16_t)motion_all[6]) << 8) | motion_all[7];
	
	motion[3] = (((uint16_t)motion_all[8]) << 8) | motion_all[9];
	motion[4] = (((uint16_t)motion_all[10]) << 8) | motion_all[11];
	motion[5] = (((uint16_t)motion_all[12]) << 8) | motion_all[13];
}

void MPU6050_get_accel(uint16_t* acceleration) 
{
	uint8_t accel[6];
	i2c_readReg(MPU6050_ADDRESS,MPU6050_RA_ACCEL_XOUT_H,accel,6);
	acceleration[0] = (((uint16_t)accel[0]) << 8) | accel[1];
	acceleration[1] = (((uint16_t)accel[2]) << 8) | accel[3];
	acceleration[2] = (((uint16_t)accel[4]) << 8) | accel[5];
}

void MPU6050_get_gyro(uint16_t* gyroRates)
{
	uint8_t gyro[6];
	i2c_readReg(MPU6050_ADDRESS,MPU6050_RA_GYRO_XOUT_H,gyro,6);
	gyroRates[0] = (((uint16_t)gyro[0]) << 8) | gyro[1];
	gyroRates[1] = (((uint16_t)gyro[2]) << 8) | gyro[3];
	gyroRates[2] = (((uint16_t)gyro[4]) << 8) | gyro[5];
}

void MPU6050_set_sleepMode(uint8_t enableSleep)
{
	uint8_t power_reg_read, power_reg_write;
	switch(enableSleep) {
		case 1:
				i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
				power_reg_write = power_reg_read & ~(0b01000000);
				power_reg_write |= (0b01000000);
				i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
				break;
		case 0:
				i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
				power_reg_write = power_reg_read & ~(0b01000000);
				power_reg_write |= (0b00000000);
				i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
				break;
		default:
				i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
				power_reg_write = power_reg_read & ~(0b01000000);
				power_reg_write |= (0b01000000);
				i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
				break;
	}
}

void MPU6050_set_gyroFS(uint8_t gyroFS)
{
	switch(gyroFS) {
		case 0:
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG,(uint8_t*)0b00000000,1);
			break;
		case 1:
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG,(uint8_t*)0b00001000,1);
			break;
		case 2:
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG,(uint8_t*)0b00010000,1);
			break;
		case 3:
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG,(uint8_t*)0b00011000,1);
			break;
		default:
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_GYRO_CONFIG,(uint8_t*)0b00000000,1);
			break;
	}
}

void MPU6050_set_accelFS(uint8_t accelFS)
{
	uint8_t accel_config_read, accel_config_write;
	
	switch(accelFS) {
		case 0:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_read, 1);
			accel_config_write = accel_config_read & ~(0b00011000);
			accel_config_write |= (0b00000000);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_write, 1);
			break;
		case 1:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_read, 1);
			accel_config_write = accel_config_read & ~(0b00011000);
			accel_config_write |= (0b00001000);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_write, 1);
			break;
		case 2:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_read, 1);
			accel_config_write = accel_config_read & ~(0b00011000);
			accel_config_write |= (0b00010000);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_write, 1);
			break;
		case 3:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_read, 1);
			accel_config_write = accel_config_read & ~(0b00011000);
			accel_config_write |= (0b00011000);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_write, 1);
			break;
		default:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_read, 1);
			accel_config_write = accel_config_read & ~(0b00011000);
			accel_config_write |= (0b00000000);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_ACCEL_CONFIG, &accel_config_write, 1);
			break;
	}
}

void MPU6050_set_clockSource(uint8_t clockSource)
{
	uint8_t power_reg_read, power_reg_write;
	switch(clockSource) {
		case 0:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
			power_reg_write = power_reg_read & ~(0b00000111);
			power_reg_write |= (0b00000000);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);;
			break;
		case 1:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
			power_reg_write = power_reg_read & ~(0b00000111);
			power_reg_write |= (0b00000001);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
			break;
		case 2:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
			power_reg_write = power_reg_read & ~(0b00000111);
			power_reg_write |= (0b00000010);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
			break;
		case 3:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
			power_reg_write = power_reg_read & ~(0b00000111);
			power_reg_write |= (0b00000011);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
			break;
		default:
			i2c_readReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_read, 1);
			power_reg_write = power_reg_read & ~(0b00000111);
			power_reg_write |= (0b00000001);
			i2c_writeReg(MPU6050_ADDRESS, MPU6050_RA_PWR_MGMT_1, &power_reg_write, 1);
			break;
	}
}