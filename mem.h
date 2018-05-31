


//*******************************************************************************
// 																				*
//		PPS MWD Firmware														*
//		File:           	   	mem.h											*
//		PPS Inc. 	cli 		2011.06.27										*
// 																				*
//*******************************************************************************





#ifndef _MEM_H
#define _MEM_H  1


#include <xc.h>		// Register definitions


//---------------------------------------------------------------------
//		TC58V32                        AT45DB161D		   	AT45DB321D
//---------------------------------------------------------------------
//	   	2   sectors a chip				16						64
//		256 blocks per sector			32						16
//		16  pages  per block			8						8
//		8   lines  per page				8						8
//		64  bytes  per line				64						64
//
//	Total: 2*256*16*8*64 = 4MB		16*32*8*8*64 = 2MB			4MB
//---------------------------------------------------------------------
//	TC58V32
//		   A21		A20 - A13	A12 - A9	A8 - A0	
//		 sector		  block		  page		 line	
//---------------------------------------------------------------------
//	AT45DB161D
//		A21 - A18	A17 - A13 	A12 - A10	A9 - A0
//		 sector		  block		  page		 line		
//---------------------------------------------------------------------
//	AT45DB321D
//		A22 - A17	A16 - A13 	A12 - A10	A9 - A0
//		 sector		  block		  page		 line		
//---------------------------------------------------------------------
//	Constant Definitions
//---------------------------------------------------------------------
//
	#define		Ver_150					// Version for 150C application

//  #define	   	MEM_Type0				// 0: AT45DB161D
    #define		MEM_Type1				// 1: AT45DB321D
//
//
//---------------------------------------------------------------------

#if defined(MEM_Type0)
	#define	   NCHIPS	2
	#define	   NSECTS	16				// AT45DB161
	#define	   NBLOCK	32
#endif

#if defined(MEM_Type1)
	#define	   NCHIPS	2
	#define	   NSECTS	64				// AT45DB321
	#define	   NBLOCK	16
#endif

// Define the following Port pins accordingly:
#define	   MEM_CE0  LATGbits.LATG0		// MEM CS0 pin. 
#define	   MEM_CE1  LATGbits.LATG1		// MEM CS1 pin
//#define	   MEM_CE2  LATGbits.LATG2		// MEM CS2 pin. 
//#define	   MEM_CE3  LATGbits.LATG3		// MEM CS3 pin

//---------------------------------------------------------------------
// 	Variable declarations
//---------------------------------------------------------------------

extern unsigned char mem_BUF[64];

extern unsigned char MEM_chip;			// For 2 Memory chips: 0 - 1; for 4 Memory chips: 0 - 3.
extern unsigned char MEM_sector;
extern unsigned char MEM_block;
extern unsigned char MEM_page;
extern unsigned char MEM_line;

extern unsigned char first_addr;
extern unsigned char second_addr;
extern unsigned char third_addr;

extern unsigned char MEM_Manufacturer_ID;
extern unsigned char MEM_Device_ID1;
extern unsigned char MEM_Device_ID2;

//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------
void Init_FLASH_MEM(void);
void MEM_DeviceID(void);

void MEM_Format(void);

void MEM_CalAddr(unsigned char sector_addr,
                 unsigned char block_addr,
                 unsigned char page_addr,
				 unsigned char line_addr);

void MEM_EraseBlock(unsigned char chip_addr,
				    unsigned char sector_addr,
               	    unsigned char block_addr);

void MEM_ErasePage(unsigned char chip_addr,
				   unsigned char sector_addr,
               	   unsigned char block_addr,
				   unsigned char page_addr);

void MEM_ReadLine(unsigned char chip_addr,
				  unsigned char sector_addr,
	          	  unsigned char block_addr,
                  unsigned char page_addr,
                  unsigned char line_addr);

void MEM_WriteLine(unsigned char chip_addr,
				   unsigned char sector_addr,
	           	   unsigned char block_addr,
                   unsigned char page_addr,
                   unsigned char line_addr);

unsigned char MEM_status(unsigned char chip_addr);

unsigned char MEM_CompWrite(unsigned char chip_addr);
void MEM_ReWritePage(unsigned char chip_addr);

//void MEM_FindFirst(void);
void MEM_FindFirst(unsigned char *blk_map);
//void MEM_FindCurrent(unsigned char *blk_map);
void MEM_FindCurrent(unsigned char jcnt, unsigned char *table);
void MEM_FindNext(void);
//void MEM_FindLine(void);
void MEM_FindLine(unsigned char *blk_map);
unsigned char MEM_CountJob(unsigned char *blk_map, unsigned char *table);
//void MEM_NextBlock(unsigned char *blk_map);
void MEM_NextULine(unsigned char *blk_map);
void MEM_NextBLine(unsigned char *blk_map);
unsigned char MEM_TestBlock(unsigned char chip_addr, unsigned int block_num, unsigned char *blk_map);
unsigned char MEM_QuickBlock(unsigned char chip_addr, unsigned int block_num, unsigned char *blk_map);
unsigned char MEM_CheckBlock(unsigned char chip_addr, unsigned char sector_addr, unsigned char block_addr, unsigned char *blk_map);
void MEM_CalAddrByte(unsigned char sector_addr,
					 unsigned char block_addr,
                 	 unsigned char page_addr,
				 	 unsigned int byte_addr);
void MEM_WriteByte(unsigned char chip_addr,
				   unsigned char sector_addr,
	           	   unsigned char block_addr,
                   unsigned char page_addr,
                   unsigned int byte_addr, unsigned char length);

#endif


