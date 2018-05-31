


//*******************************************************************************
// 																				*
//		PPS Filter Firmware														*
//		File:           	   	spi.h											*
//		PPS Inc. 	cli 		2011.09.19										*
// 																				*
//*******************************************************************************



#ifndef _SPI_H
#define _SPI_H 


#include <xc.h>		// Register definitions



//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------

void spi1_init(void);
void spi2_init(void);
unsigned char SPI1_RW(unsigned char x);
unsigned char SPI2_RW(unsigned char x);


#endif
