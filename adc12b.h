


//*******************************************************************************
// 																				*
//		PPS PVT Firmware														*
//		File:           	   	adc506a.h										*
//		PPS Inc. 	cli 		2011.06.23										*
// 																				*
//*******************************************************************************





#ifndef __ADC12b_H
#define __ADC12b_H 

#include <xc.h>		// Register definitions


//---------------------------------------------------------------------
// Variable declarations
//---------------------------------------------------------------------


//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------

// With Section Attribute:
void adc1_init(void);
void adc1_int_enable(void);
void adc1_int_disable(void);
void adc1_vib(signed int *VIB_Data);
int adc1_an0(unsigned char ch);


#endif
