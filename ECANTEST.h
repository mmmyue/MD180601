/* 
 * File:   ECANTEST.h
 * Author: min
 *
 * Created on April 12, 2018, 1:12 PM
 */

#ifndef ECANTEST_H
#define	ECANTEST_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif


#include <xc.h>		// Register definitions
#include "md.h"
#include "ecan.h"
#include "mdtimers.h"

void test_EM(void);
void toEM(unsigned char *mm,unsigned char cmd);

#endif	/* ECANTEST_H */

