

/* 
 * File:   DATAID.H
 * Author: etech.mmm@gmail.com     
 * Comments: MWD 
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef DATAID_H
#define	DATAID_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define TS		0x01
#define Gx		0x02
#define Gy		0x03
#define Gz		0x04
#define Bx		0x05
#define By		0x06
#define Bz		0x07
#define BT		0x08
#define GT		0x09
#define INC		0x0A
#define AZ		0x0B
#define TF		0x0C
#define Vib		0x0D
//#define P1W1	0x0E            //Presure+Temp 1 Byte1 (MSB) Byte2
//#define P1W2    0x0F			//Presure+Temp 1 Byte3  Byte4
//#define P1W3    0x10 			//Presure+Temp 1 Byte5 (MSB) Byte6 (LSB)
//#define P2W1	0x11
//#define P2W2    0x12
//#define P2W3    0x13
#define Gamma	0x14
#define DipA	0x15
#define VibX	0x16
#define VibY	0x17
#define VibZ	0x18
#define TEMP	0x19

//#define TRX		0x1A
//#define RTSX	0x1B
//#define ATBHX	0x1C
//#define PDBHX	0x1D
//#define ATBSHX	0x1E
//#define PDBSHX	0x1F
//#define ATBLX	0x20
//#define PDBLX	0x21
//#define ATBSLX	0x22
//#define PDBSLX	0x23

#define VBatt	0x24
#define RPRS	0x25
#define FPRS	0x26
#define MOTC	0x27
#define STP     0xff




//#define MWDS	0x25
//#define EMINDEX	0x26





#endif	/* DATAID_H */

