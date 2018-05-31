


//*******************************************************************************
// 																				*
//		PPS Motor Drive Firmware												*
//		File:           	   	md_coding.h										*
//		PPS Inc. 	cli 		2011.07.11										*
// 																				*
//*******************************************************************************



#ifndef _MD_CODING_H
#define _MD_CODING_H  1


#include <xc.h>		// Register definitions



//---------------------------------------------------------------------
//Constant Definitions
//---------------------------------------------------------------------

// Default Parameters:

//---------------------------------------------------------------------
//           Motor Drive Data Definitions:
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------

void md_coding(unsigned char *data, unsigned char num, unsigned char coding, unsigned char pol, unsigned char code_size, unsigned char *code);
unsigned char md_crc_coding(unsigned char *data, unsigned int total_bits);
unsigned char md_code_rd(unsigned char *md_code, unsigned int md_i);
void md_code_wr(unsigned char *md_code, unsigned int md_i, unsigned char md_v);


#endif
