/* 
 * File:   CONFIG.H
 * Author: mmmyue@outlook.com
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H2
#define	XC_HEADER_TEMPLATE_H2

#include <xc.h> // include processor files - each processor file is guarded.  
#include <string.h> // include processor files - each processor file is guarded.  
#include "s25fl256l-ming.h"  
#include "mdtimers.h"  




// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

#define DATAID_COUNT    32
#define FRAME_LEN       32

struct MWDDATAS {
    unsigned char id;
    unsigned char nbits;
    unsigned int max;
    unsigned int min;
};
//extern MWDDATAS dataid[DATAID_COUNT];

struct MDCNFH{
    unsigned char pagetype; //0:configuration parameter, 1: logging pages
    unsigned char gampre; // preset time to poll gamma counter
    unsigned char dipre; //preset time to poll DI counter
    unsigned char pulsew; // pulse width;
    MDDATE cnftime;
    unsigned long long ind; //
    unsigned char mstr[8]; //="min-ETEC\0";
} ;

union FLL_PAGE_HEAD {

    struct {
        unsigned char pagetype; //0:configuration parameter, 1: logging pages
        unsigned char gampre; // preset time to poll gamma counter
        unsigned char dipre; //preset time to poll DI counter
        unsigned char pulsew; // pulse width;
        MDDATE cnftime;
        unsigned long long ind; //
        unsigned char mstr[8]; //="min-ETEC\0";
    } pageh;
    char phh[32];
};

struct CONFIGS {
    //union FLL_PAGE_HEAD pagehead;
    struct MDCNFH hhh;
    struct MWDDATAS frame[4][FRAME_LEN]__attribute__((aligned(32)));
};
extern struct CONFIGS Rcnfbuf, Wcnfbuf;





// Comment a function and leverage automatic documentation with slash star star4
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

