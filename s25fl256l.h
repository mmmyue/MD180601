/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H1
#define	XC_HEADER_TEMPLATE_H1

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

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
/**********************************************************************
* ?2007 Microchip Technology Inc.
*
* FileName:        spieeprom.h
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       PIC24Fxxxx
* Compiler:        MPLAB?C30 v3.00 or higher
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all 
* ownership and intellectual property rights in the code accompanying
* this message and in all derivatives hereto.  You may use this code,
* and any derivatives created by any person or entity by or on your 
* behalf, exclusively with Microchip's proprietary products.  Your 
* acceptance and/or use of this code constitutes agreement to the 
* terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS". NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT 
* NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
* CODE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS, COMBINATION WITH 
* ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE 
* LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR
* BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
* CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
* EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR 
* EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER 
* CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
* DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP 
* SPECIFICALLY TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify,
* test, certify, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Albert Z.		05/16/08	First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 
* 25LC256 is connected to SPI2
************************************************************************/


#define TEST

// peripheral configurations
#define SPI_MASTER  0x0120	// select 8-bit master mode, CKE=1, CKP=0
#define SPI_ENABLE	0x8000	// enable SPI port, clear status


/************************************************************************
* EEPROM Commands                                                       *
*                                                                       *    
************************************************************************/
#define EEPROM_PAGE_SIZE    (unsigned)512
#define EEPROM_PAGE_MASK    (unsigned)0x001ff
#define EEPROM_CMD_READ     (unsigned)0b00000011
#define EEPROM_CMD_WRITE    (unsigned)0b00000010
#define EEPROM_CMD_WRDI     (unsigned)0b00000100
#define EEPROM_CMD_WREN     (unsigned)0b00000110
#define EEPROM_CMD_RDSR     (unsigned)0b00000101
#define EEPROM_CMD_WRSR     (unsigned)0b00000001

/************************************************************************
* Aliases for IOs registers related to SPI connected to EEPROM          *
*                                                                       *    
************************************************************************/


#define EEPROM_SS_TRIS      TRISAbits.TRISA5
#define EEPROM_SS_PORT      PORTAbits.RA5
#define FCS_TRIS            TRISAbits.TRISA5
#define FCS                 PORTAbits.RA5
#define FCS1_TRIS            TRISAbits.TRISA4
#define FCS1                 PORTAbits.RA4


#ifdef TEST
#define EEPROM_SCK_TRIS     TRISFbits.TRISF6
#define EEPROM_SDO_TRIS     TRISFbits.TRISF8
#define EEPROM_SDI_TRIS     TRISFbits.TRISF7
#else
#define EEPROM_SCK_TRIS     TRISGbits.TRISG6
#define EEPROM_SDO_TRIS     TRISGbits.TRISG8
#define EEPROM_SDI_TRIS     TRISGbits.TRISG7
#endif


/************************************************************************
* Structure STATREG and union _EEPROMStatus_                            *
*                                                                       *
* Overview: Provide a bits and byte access to EEPROM status value.      *
*                                                                       *
************************************************************************/
struct  STATREG{
	unsigned    WIP:1;
	unsigned    WEL:1;
	unsigned    BP0:1;
	unsigned    BP1:1;
	unsigned    RESERVED:3;
	unsigned    WPEN:1;
};

union _EEPROMStatus_{
	struct  STATREG Bits;
	unsigned char	Char;
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
#define Lo(X)   (unsigned char)(X&0x00ff)

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
#define Hi(X)   (unsigned char)((X>>8)&0x00ff)

/************************************************************************
* Macro: mEEPROMSSLow                                                   *
*                                                                       *
* Preconditions: SS IO must be configured as output.                    *
*                                                                       *
* Overview: This macro pulls down SS line                               *
*           to start a new EEPROM operation.                            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
#define mEEPROMSSLow()      EEPROM_SS_PORT = 0;

/************************************************************************
* Macro: mEEPROMSSHigh                                                  *
*                                                                       *
* Preconditions: SS IO must be configured as output.                    *
*                                                                       *
* Overview: This macro set SS line to high level                        *
*           to start a new EEPROM operation.                            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
#define mEEPROMSSHigh()     EEPROM_SS_PORT = 1;

/************************************************************************
* Function: EEPROMInit                                                  *
*                                                                       *
* Preconditions: SPI module must be configured to operate with          *
*                 parameters: Master, MODE16 = 0, CKP = 1, SMP = 1.     *
*                                                                       *
* Overview: This function setup SPI IOs connected to EEPROM.            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
extern void EEPROMInit(void);

/************************************************************************
* Function: EEPROMReadStatus()                                          *
*                                                                       *
* Preconditions: SPI module must be configured to operate with  EEPROM. *
*                                                                       *
* Overview: This function reads status register from EEPROM.            *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: Status register value.                                        *
*                                                                       *
************************************************************************/
extern union _EEPROMStatus_ EEPROMReadStatus(void);

/************************************************************************
* Function: EEPROMWriteByte()                                           *
*                                                                       *
* Preconditions: SPI module must be configured to operate with  EEPROM. *
*                                                                       *
* Overview: This function writes a new value to address specified.      *
*                                                                       *
* Input: Data to be written and address.                                *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
extern void EEPROMWriteByte(unsigned char, unsigned int);

/************************************************************************
* Function: EEPROMReadByte()                                            *
*                                                                       *
* Preconditions: SPI module must be configured to operate with  EEPROM. *
*                                                                       *
* Overview: This function reads a value from address specified.         *
*                                                                       *
* Input: Address.                                                       *
*                                                                       *
* Output: Data read.                                                    *
*                                                                       *
************************************************************************/
extern unsigned char EEPROMReadByte(unsigned int);

/************************************************************************
* Function: EEPROMWriteEnable()                                         *
*                                                                       *
* Preconditions: SPI module must be configured to operate with EEPROM.  *
*                                                                       *
* Overview: This function allows a writing into EEPROM. Must be called  *
* before every writing command.                                         *
*                                                                       *
* Input: None.                                                          *
*                                                                       *
* Output: None.                                                         *
*                                                                       *
************************************************************************/
extern void EEPROMWriteEnable(void);
extern void EEPROMWriteDisable(void);

extern unsigned long RD_FID(void);

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H1 */

