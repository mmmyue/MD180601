/* 
 * File:   EMBtimer.h
 * Author: YumingY
 *
 * Created on April 11, 2018
 */


#ifndef _MD_TIMERS_H
#define _MD_TIMERS_H  1


#include <xc.h>		// Register definitions
#include "md.h"


//---------------------------------------------------------------------
//Constant Definitions
//---------------------------------------------------------------------



//-----------------------   Timers Definations   -------------------------

#define      TMR1_10msPERIOD			(Fcy*0.010/256)
#define      TMR3_PERIOD			0xFFFF
#define      BEACON_PERIOD			50



    
typedef struct{
    unsigned ye;
    unsigned mo;
    unsigned da;
    unsigned char ho;
    unsigned char mi;
    unsigned char se;
    unsigned t1;
    unsigned t2;
    unsigned t3;
    unsigned t4;
}emtimer;    



void initTimer(void);  


#endif	/* EMBTIMER_H */

