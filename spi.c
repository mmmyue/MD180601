


//*******************************************************************************
// 																				*
//		PPS MWD Firmware														*
//		File:           	   	spi.c											*
//		PPS Inc. 	cli 		2011.06.23										*
// 																				*
//*******************************************************************************



#include <xc.h>		// Register definitions



//---------------------------------------------------------------------------------

void spi1_init(void)

{

	// SPI1CON1 Register Settings:
	SPI1CON1bits.DISSCK = 0;		// Internal Serial Clock is Enabled.
	SPI1CON1bits.DISSDO = 0;		// SDOx pin is controlled by the module.
	SPI1CON1bits.PPRE = 3;			// Primary prescale: 0 for 64:1; 1 for 16:1; 2 for 4:1; 3 for 1:1.
	SPI1CON1bits.SPRE = 7;			// Secondary prescale: 0 for 8:1; ... ; 7 for 1:1. 
	SPI1CON1bits.MODE16 = 0;		// Communication is word-wide (16 bits).
	SPI1CON1bits.SMP = 0;			// Input Data is sampled at the middle of data output time.
	SPI1CON1bits.CKE = 0;			// Serial output data changes on transition from active clock state to idle clock state.
	SPI1CON1bits.CKP = 1;			// Idle state for clock is a high level; active state is a low level.
	SPI1CON1bits.MSTEN = 1;			// Master Mode Enabled.

	// SPI1STAT Register Settings:
	SPI1STATbits.SPIEN = 1;			// Enables module and configures SCKx, SDOx, SDIx and SSx as serial port pins.

}


//---------------------------------------------------------------------------------

void spi2_init(void)

{

	// SPI2CON1 Register Settings:
	SPI2CON1bits.DISSCK = 0;		// Internal Serial Clock is Enabled.
	SPI2CON1bits.DISSDO = 0;		// SDOx pin is controlled by the module.
	SPI2CON1bits.PPRE = 2;			// Primary prescale: 0 for 64:1; 1 for 16:1; 2 for 4:1; 3 for 1:1. 
	SPI2CON1bits.SPRE = 6;			// Secondary prescale: 0 for 8:1; ... ; 7 for 1:1. (SCLK = 3.6864MHz/2/PPRE/SPRE = 230KHz SCLK)
	SPI2CON1bits.MODE16 = 0;		// Communication is byte-wide (8 bits).
	SPI2CON1bits.SMP = 0;			// Input Data is sampled at the middle of data output time.
	SPI2CON1bits.CKE = 0;			// Serial output data changes on transition from active clock state to idle clock state.
	SPI2CON1bits.CKP = 1;			// Idle state for clock is a high level; active state is a low level.
	SPI2CON1bits.MSTEN = 1;			// Master Mode Enabled.

	// SPI2STAT Register Settings:
	SPI2STATbits.SPIEN = 1;			// Enables module and configures SCKx, SDOx, SDIx and SSx as serial port pins.

}


//---------------------------------------------------------------------------------

unsigned char SPI1_RW(unsigned char x)

{

	SPI1BUF = x;					// send data.
	
	while(!SPI1STATbits.SPIRBF);	// wait for ready.

	x = SPI1BUF;					// read data.
	return (x);

}


//---------------------------------------------------------------------------------

unsigned char SPI2_RW(unsigned char x)

{

	SPI2BUF = 0x0000 | x;			// send data.
	
	while(!SPI2STATbits.SPIRBF);	// wait for ready.

	x = SPI2BUF & 0x00FF;			// read data.
	return (x);

}


