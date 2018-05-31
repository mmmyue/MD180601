
/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef XC_HEADER_TEMPLATE_H1
#define XC_HEADER_TEMPLATE_H1

#include <xc.h> // include processor files - each processor file is guarded.
#include "SPI1.h"

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

#define TEST

/************************************************************************
 * FLL Commands                                                       *
 *                                                                       *    
 ************************************************************************/
#define FLL_PAGE_SIZE (unsigned)256
#define FLL_PAGE_MASK (unsigned)0x00ff

#define FLL_S_SIZE (unsigned)0x1000
#define FLL_HB_SIZE (unsigned)0x8000
#define FLL_B_SIZE (unsigned)0x10000
#define FLL_C_SIZE (unsigned)0x2000000
//
//#define FLL_P_COUNT (FLL_C_SIZE/FLL_PAGE_SIZE)
//#define FLL_S_COUNT //(unsigned)8192
//#define FLL_HB_COUNT (unsigned)1024
//#define FLL_B_COUNT (unsigned)512
//

#define FLL_P_COUNT (FLL_C_SIZE/FLL_PAGE_SIZE)
#define FLL_S_COUNT (FLL_C_SIZE/FLL_S_SIZE)
#define FLL_HB_COUNT (FLL_C_SIZE/FLL_HB_SIZE)
#define FLL_B_COUNT (FLL_C_SIZE/FLL_B_SIZE)


#define FLL_CMD_4READ (unsigned)0x13
#define FLL_CMD_4PP (unsigned)0x12
#define FLL_CMD_WRDI (unsigned)0x4
#define FLL_CMD_WREN (unsigned)0x6
#define FLL_CMD_RDSR (unsigned)0b00000101
#define FLL_CMD_WRSR (unsigned)0b00000001
#define FLL_CMD_4SE (unsigned)0x21
#define FLL_CMD_4HBE (unsigned)0x53
#define FLL_CMD_4BE (unsigned)0xDC
#define FLL_CMD_4CE (unsigned)0x60


// #define FLL_PAGE_SIZE    (unsigned)256
// #define FLL_PAGE_MASK    (unsigned)0x00ff
// #define FLL_CMD_READ     (unsigned)0b00000011
// #define FLL_CMD_WRITE    (unsigned)0b00000010
// #define FLL_CMD_WRDI     (unsigned)0b00000100
// #define FLL_CMD_WREN     (unsigned)0b00000110
// #define FLL_CMD_RDSR     (unsigned)0b00000101
// #define FLL_CMD_WRSR     (unsigned)0b00000001

/************************************************************************
 * Aliases for IOs registers related to SPI connected to FLL          *
 *                                                                       *    
 ************************************************************************/

#define FLL_SS_TRIS TRISAbits.TRISA5
#define FLL_SS_PORT PORTAbits.RA5
#define FCS_TRIS TRISAbits.TRISA5
#define FCS PORTAbits.RA5
#define FCS1_TRIS TRISAbits.TRISA4
#define FCS1 PORTAbits.RA4

#ifdef TEST
#define FLL_SCK_TRIS TRISFbits.TRISF6
#define FLL_SDO_TRIS TRISFbits.TRISF8
#define FLL_SDI_TRIS TRISFbits.TRISF7
#else
#define FLL_SCK_TRIS TRISGbits.TRISG6
#define FLL_SDO_TRIS TRISGbits.TRISG8
#define FLL_SDI_TRIS TRISGbits.TRISG7
#endif

/************************************************************************
 * Structure STATREG and union _FLLStatus_                            *
 *                                                                       *
 * Overview: Provide a bits and byte access to FLL status value.      *
 *                                                                       *
 ************************************************************************/
struct STATREG
{
    unsigned WIP : 1;
    unsigned WEL : 1;
    unsigned BP0 : 1;
    unsigned BP1 : 1;
    unsigned RESERVED : 3;
    unsigned WPEN : 1;
};

union _FLLStatus_ {
    struct STATREG Bits;
    unsigned char Char;
};

/************************************************************************
 * Macro: Lo                                                             *
 *                                                                       *
 * Preconditions: None                                                   *
 *                                                                       *
 * Overview: This macro extracts a low byte from a 2 byte word.          *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/
#define Lo(X) (unsigned char)(X & 0x00ff)

/************************************************************************
 * Macro: Hi                                                             *
 *                                                                       *
 * Preconditions: None                                                   *
 *                                                                       *
 * Overview: This macro extracts a high byte from a 2 byte word.         *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/
#define Hi(X) (unsigned char)((X >> 8) & 0x00ff)

/************************************************************************
 * Macro: mFLLSSLow                                                   *
 *                                                                       *
 * Preconditions: SS IO must be configured as output.                    *
 *                                                                       *
 * Overview: This macro pulls down SS line                               *
 *           to start a new FLL operation.                            *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/
#define mFLLSSLow() FLL_SS_PORT = 0;

/************************************************************************
 * Macro: mFLLSSHigh                                                  *
 *                                                                       *
 * Preconditions: SS IO must be configured as output.                    *
 *                                                                       *
 * Overview: This macro set SS line to high level                        *
 *           to start a new FLL operation.                            *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/
#define mFLLSSHigh() FLL_SS_PORT = 1;

/************************************************************************
 * Function: FLLInit                                                  *
 *                                                                       *
 * Preconditions: SPI module must be configured to operate with          *
 *                 parameters: Master, MODE16 = 0, CKP = 1, SMP = 1.     *
 *                                                                       *
 * Overview: This function setup SPI IOs connected to FLL.            *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/
extern void FLLInit(void);

/************************************************************************
 * Function: FLLReadStatus()                                          *
 *                                                                       *
 * Preconditions: SPI module must be configured to operate with  FLL. *
 *                                                                       *
 * Overview: This function reads status register from FLL.            *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: Status register value.                                        *
 *                                                                       *
 ************************************************************************/
extern union _FLLStatus_ FLLReadStatus(void);

/************************************************************************
 * Function: FLLWriteByte()                                           *
 *                                                                       *
 * Preconditions: SPI module must be configured to operate with  FLL. *
 *                                                                       *
 * Overview: This function writes a new value to address specified.      *
 *                                                                       *
 * Input: Data to be written and address.                                *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/

extern void FLL4SE(unsigned long addr);
extern void FLL4PP(unsigned char *d, unsigned long pageaddr);

/************************************************************************
 * Function: FLLReadByte()                                            *
 *                                                                       *
 * Preconditions: SPI module must be configured to operate with  FLL. *
 *                                                                       *
 * Overview: This function reads a value from address specified.         *
 *                                                                       *
 * Input: Address.                                                       *
 *                                                                       *
 * Output: Data read.                                                    *
 *                                                                       *
 ************************************************************************/
extern unsigned char FLL4READ(unsigned char *d, unsigned long addr, unsigned long len);
extern unsigned char FLLReadByte(unsigned long addr);

/************************************************************************
 * Function: FLLWriteEnable()                                         *
 *                                                                       *
 * Preconditions: SPI module must be configured to operate with FLL.  *
 *                                                                       *
 * Overview: This function allows a writing into FLL. Must be called  *
 * before every writing command.                                         *
 *                                                                       *
 * Input: None.                                                          *
 *                                                                       *
 * Output: None.                                                         *
 *                                                                       *
 ************************************************************************/
extern void FLLWriteEnable(void);
extern void FLLWriteDisable(void);

extern unsigned long RD_FID(void);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// TODO If C++ is being used, regular C code needs function names to have C
// linkage so the functions can be used by the c code.

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XC_HEADER_TEMPLATE_H1 */
