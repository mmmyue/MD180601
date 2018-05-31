/**********************************************************************
 * April 2018, YMYUE
 *
 * FileName:       s25fl256l-ming .c
 
 ************************************************************************/
#include "s25fl256l-ming.h"

void FLLInit() {
    // Set IOs directions for FLL SPI
    FLL_SS_PORT = 1;
    FLL_SS_TRIS = 0;
}

/************************************************************************
 * Function: FLL4PP()                                           *
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
void FLL4PP(unsigned char *d, unsigned long pageaddr) {
    unsigned char Local_8, *pl;
    unsigned i;
    unsigned long addr = pageaddr * FLL_PAGE_SIZE;
    pl = (unsigned char *) &addr;
    FLLWriteEnable();
    mFLLSSLow();

    Local_8 = writeSPI1(FLL_CMD_4PP);

    Local_8 = writeSPI1(pl[3]);
    Local_8 = writeSPI1(pl[2]);
    Local_8 = writeSPI1(pl[1]);
    Local_8 = writeSPI1(pl[0]);
    for (i = 0; i < FLL_PAGE_SIZE; i++) {
        Local_8 = writeSPI1(*d);
        d++;
    }

    mFLLSSHigh();

    // wait for completion of previous write operation
    while (FLLReadStatus().Bits.WIP);

    FLLWriteDisable();
}

void FLL4SE(unsigned long addr) {
    unsigned char Local_8, *pl;
     pl = (unsigned char *) &addr;
    FLLWriteEnable();
    mFLLSSLow();

    Local_8 = writeSPI1(FLL_CMD_4SE);

    Local_8 = writeSPI1(pl[3]);
    Local_8 = writeSPI1(pl[2]);
    Local_8 = writeSPI1(pl[1]);
    Local_8 = writeSPI1(pl[0]);
    mFLLSSHigh();

    // wait for completion of previous write operation
    while (FLLReadStatus().Bits.WIP);

    FLLWriteDisable();
}

unsigned char FLL4READ(unsigned char *d, unsigned long addr, unsigned long len) {
    unsigned char Local_8;
    unsigned long i;
    unsigned char * pl = (unsigned char *) &addr;
    mFLLSSLow();

    Local_8 = writeSPI1(FLL_CMD_4READ);

    Local_8 = writeSPI1(pl[3]);
    Local_8 = writeSPI1(pl[2]);
    Local_8 = writeSPI1(pl[1]);
    Local_8 = writeSPI1(pl[0]);
    for (i = 0; i < len; i++) {
        d[i] = writeSPI1(0);
    }
    mFLLSSHigh();
    return FLLReadStatus().Char;

}

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
unsigned char FLLReadByte(unsigned long addr) {
    unsigned char Local_8;
    unsigned char * pl = (unsigned char *) &addr;
    mFLLSSLow();

    Local_8 = writeSPI1(FLL_CMD_4READ);

    Local_8 = writeSPI1(pl[3]);
    Local_8 = writeSPI1(pl[2]);
    Local_8 = writeSPI1(pl[1]);
    Local_8 = writeSPI1(pl[0]);
    Local_8 = writeSPI1(0);
    mFLLSSHigh();
    return Local_8;
}

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
void FLLWriteEnable() {
    unsigned char Local_8;
    mFLLSSLow();
    Local_8 = writeSPI1(FLL_CMD_WREN);
    mFLLSSHigh();
}

void FLLWriteDisable() {
    unsigned char Local_8;
    mFLLSSLow();
    Local_8 = writeSPI1(FLL_CMD_WRDI);
    mFLLSSHigh();
}

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
union _FLLStatus_ FLLReadStatus() {
    unsigned char Local_8;

    mFLLSSLow();
    Local_8 = writeSPI1(FLL_CMD_RDSR);
    Local_8 = writeSPI1(0);
    mFLLSSHigh();

    return (union _FLLStatus_)Local_8;
}

unsigned long RD_FID(void) {

    unsigned char *FID;
    unsigned long l;
    FID = (unsigned char *) &l;
    FCS = 0;
    writeSPI1(0x9f);
    FID[0] = writeSPI1(0);
    FID[1] = writeSPI1(0);
    FID[2] = writeSPI1(0);
    FID[3] = writeSPI1(0);
    FCS = 1;
    return l;


}