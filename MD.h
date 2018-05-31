/* 
 * File:   MD.h
 * Author: min
 *
 * Created on April 6, 2018, 4:29 PM
 */

#ifndef MD_H
#define	MD_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#define Fcy  5000000

#define LED0        LATCbits.LATC1
#define LED1        LATCbits.LATC2

#define enLED0      TRISCbits.TRISC1
#define enLED1      TRISCbits.TRISC2

#define enAN0       TRISBbits.TRISB0

extern unsigned int cnt10ms;

void SYS_Initialize(void);


#endif	/* MD_H */

