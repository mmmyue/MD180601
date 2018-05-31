/* 
 * File:   MDTIMER.h
 * Author: YumingY
 *
 * Created on April 11, 2018
 */


#ifndef _MD_TIMERS_H
#define _MD_TIMERS_H  

#include <xc.h>		// Register definitions
#include "md.h"

#define      TMR1_10msPERIOD		(Fcy*0.010/256)
#define      TMR3_PERIOD			0xFFFF
#define      BEACON_PERIOD			50

typedef struct {
    unsigned int se:5;
    unsigned int mi:6;
    unsigned int ho:5;
    unsigned int da:5;
    unsigned int mo:4;
    unsigned int ye:7; 
} MDDATE;

typedef struct {
    unsigned t1;
    unsigned t2;
    unsigned t3;
    unsigned t4;
    unsigned tmr1s,tmr10ms,tmr100ms;  
    unsigned txtk;
    unsigned tmrcan100ms;
    unsigned long t1s;
} MDTimer;

extern MDDATE mddate; 
extern MDTimer mdtimer; 
void initTimer(void);

#endif      /* _MD_TIMERS_H */

