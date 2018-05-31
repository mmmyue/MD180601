


//*******************************************************************************
// 																				*
//		PPS Motor Drive Firmware												*
//		File:           	   	md_coding.c										*
//		PPS Inc. 	cli 		2011.07.11										*
// 																				*
//*******************************************************************************



#include <xc.h>		// Register definitions

#include "md_coding.h"         	// PWM data definitions.



//---------------------------------------------------------------------
//           Data Definitions
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------



//------------------------------- Manchester Coding ----------------------------------

void md_coding(unsigned char *data, unsigned char num, unsigned char coding, unsigned char pol, unsigned char code_size, unsigned char *code)

{
	unsigned int m_code = 0;
	unsigned char num_byte = 0;
	unsigned char num_bit = 0;
	unsigned char i = 0;
	//unsigned char j = 0;

	num_byte = num / 8;
	num_bit = num % 8;

	for (i=0;i<code_size;i++) code[i] = 0;
	if (coding == 1)
		{
			for (i=0;i<num;i++)
			{	
				if (md_code_rd(data, i) == 0) m_code = 0x01^(pol*0x03);
				else m_code = 0x02^(pol*0x03);
				//if (pol == 1) m_code ^= 0x03;
				code[i/4] += m_code << (6-(i%4)*2);
			}			
		}
	else
		{
			//for (i=0;i<num_byte;i++) code[i] = data[i];
			//switch (num_bit)
			//{
			//	case 0: code[num_byte] = data[i] & 0x00; break;
			//	case 1: code[num_byte] = data[i] & 0x80; break;
			//	case 2: code[num_byte] = data[i] & 0xC0; break;
			//	case 3: code[num_byte] = data[i] & 0xE0; break;
			//	case 4: code[num_byte] = data[i] & 0xF0; break;
			//	case 5: code[num_byte] = data[i] & 0xF8; break;
			//	case 6: code[num_byte] = data[i] & 0xFC; break;
			//	case 7: code[num_byte] = data[i] & 0xFE; break;
			//	default: break;
			//}
			for (i=0;i<num;i++)
			{	
				m_code = 0x01;
				if (md_code_rd(data, i) != 0) code[i/8] += m_code << (7-(i%8));
			}			
		}
}


//------------------------------- CRC Coding ----------------------------------

unsigned char md_crc_coding(unsigned char *data, unsigned int total_bits)

{
	unsigned char i = 0;
	unsigned char crc = 0x0F;
	unsigned char crc_flag = 0;

	for (i = 0; i < total_bits; i++)
	{
		crc_flag = crc & 0x08;
		crc *= 2;
		crc &= 0x0F;
		if (md_code_rd(data, i) != 0) crc += 1;
		if (crc_flag != 0) crc ^= 0x03;
	}
	return (crc&0x0F);
}


//------------------------------- MD Code Read ----------------------------------

unsigned char md_code_rd(unsigned char *md_code, unsigned int md_i)
{
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned char m = 0;

	i = md_i / 8;
	j = md_i % 8;
	switch (j)
	{
		case 0:	m = md_code[i] & 0x80; break;
		case 1:	m = md_code[i] & 0x40; break;
		case 2:	m = md_code[i] & 0x20; break;
		case 3:	m = md_code[i] & 0x10; break;
		case 4:	m = md_code[i] & 0x08; break;
		case 5:	m = md_code[i] & 0x04; break;
		case 6:	m = md_code[i] & 0x02; break;
		case 7:	m = md_code[i] & 0x01; break;
		default:  break;
	}
	if (m != 0) m = 1;	// Added for position mode.
	return m;
}


//------------------------------- MD Code Write ----------------------------------

void md_code_wr(unsigned char *md_code, unsigned int md_i, unsigned char md_v)
{
	unsigned int i = 0;
	unsigned int j = 0;

	i = md_i / 8;
	j = md_i % 8;
	switch (j)
	{
		case 0:
				if (md_v == 0) md_code[i] &= 0x7F;
				else md_code[i] |= 0x80;
				break;
		case 1:
				if (md_v == 0) md_code[i] &= 0xBF;
				else md_code[i] |= 0x40;
				break;
		case 2:
				if (md_v == 0) md_code[i] &= 0xDF;
				else md_code[i] |= 0x20;
				break;
		case 3:
				if (md_v == 0) md_code[i] &= 0xEF;
				else md_code[i] |= 0x10;
				break;
		case 4:
				if (md_v == 0) md_code[i] &= 0xF7;
				else md_code[i] |= 0x08;
				break;
		case 5:
				if (md_v == 0) md_code[i] &= 0xFB;
				else md_code[i] |= 0x04;
				break;
		case 6:
				if (md_v == 0) md_code[i] &= 0xFD;
				else md_code[i] |= 0x02;
				break;
		case 7:
				if (md_v == 0) md_code[i] &= 0xFE;
				else md_code[i] |= 0x01;
				break;
		default:  break;
	}
}


