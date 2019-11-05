
#include <avr/io.h>
#include "pff.h"

BYTE xmit_spi(BYTE c) {
	SPDR = c;
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}

//-----------------------------------------------------------------------
// Receive a byte from MMC via SPI  (Platform dependent)                 
//-----------------------------------------------------------------------

BYTE rcv_spi(void) {
	return xmit_spi(0xFF);
}

