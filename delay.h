/**********************************************************************
* © 2007 Microchip Technology Inc.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33Fxxxx
* Compiler:        MPLAB® C30 v3.00 or higher

*************************************************************************************************/
#ifndef DELAY_H
#define	DELAY_H

#include "md.h"

void Delay( unsigned int delay_count );
void Delay_Us( unsigned int delayUs_count );

#define Delay200uS_count  (Fcy * 0.0002) / 1080
#define Delay_1mS_Cnt	  (Fcy * 0.001) / 2950
#define Delay_2mS_Cnt	  (Fcy * 0.002) / 2950
#define Delay_5mS_Cnt	  (Fcy * 0.005) / 2950
#define Delay_15mS_Cnt 	  (Fcy * 0.015) / 2950
#define Delay_1S_Cnt	  (Fcy * 0.1) / 2950 

#endif
