/* 
 * File:   MDCMD.H
 * Author: mmmyue@outlook.com
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MDCMD_H
#define	MDCMD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "ecan.h"  
#include "mdtimers.h"  

//extern struct CANFFF canbus;

 
// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations
//extern enum CANCMD mdcmd1;

typedef union {

    struct {
        unsigned char cmd;
        unsigned char sid;
        unsigned char sta : 3;
        unsigned char ver : 5;
        unsigned char pos;
        unsigned char ddid;
        unsigned char nb; //number of DATA bits
        unsigned char d6;
        unsigned char d7;
    } canbus;

    struct {
        unsigned char cmd;
        unsigned char sid;
        unsigned char sta : 3;
        unsigned char ver : 5;
        unsigned char pos;
        float fff;
    } canbusf;

    struct {
        unsigned char cmd;
        unsigned char sid;
        unsigned char sta : 3;
        unsigned char ver : 5;
        unsigned char pos;
        MDDATE mddate;
    } cantime;
    unsigned char c[8];
    unsigned int  i[4];
}CAN8B;


extern unsigned char mdcmd(void);
extern unsigned char wrfllpage(unsigned long pageaddr,unsigned char *d);
extern void clnwcnfbuf(void);

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

