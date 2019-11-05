/*
 * AK_DS_test_1.c
 *
 * Created: 3/12/2018 8:46:59 PM
 * Author : Aleksij
 */ 

#include <avr/io.h>
#include <avr/power.h>
#include <stdlib.h>

#include "diskio.h"

#include <util/delay.h>
#include "USART.h"

int main(void)
{
	uint8_t readSize = 10;
	char byte_string[16];
	
	DSTATUS statInit;
	
    //DRESULT resReceive;
	BYTE outBuff[7] = {0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A, 0x7A};
	
	BYTE buff[readSize];
	DWORD sector = 0;
	UINT offset = 446;
	UINT count = readSize;
	initUSART();
	clock_prescale_set(clock_div_1); // set clock to 16MHz
	
	do {
		statInit = disk_initialize();
		
		if (statInit == 0x01) {
			printLine("Card not initialized");
			} else if (statInit == 0x02) {
			printLine("Card not found");
			} else {
			printLine("Card initialized");
		}
		_delay_ms(100);
	} while(statInit);
	
	
	_delay_ms(1000);
	
    while (1) 
    {
		printLine("=== MAIN LOOP ===");
		
		disk_readp(buff,sector,offset,count);
		
		for(uint8_t i=0; i<readSize; i++){
			utoa(buff[i],byte_string,16);
			printLine(byte_string);
		}
	    
		disk_writep(outBuff,2);
		
		_delay_ms(1000);
    }
}

