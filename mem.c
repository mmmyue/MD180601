


//*******************************************************************************
// 																				*
//		PPS MWD Firmware														*
//		File:           	   	mem.h											*
//		PPS Inc. 	cli 		2011.06.27										*
// 																				*
//*******************************************************************************





#include <mem.h>



// External Function Definitions:
//extern unsigned char SPI1_RW(unsigned char x);	// Change the function here based on the SPI port used for memory.
extern unsigned char SPI2_RW(unsigned char x);		// Change the function here based on the SPI port used for memory.


/************************** AT45DB16/AT45DB32 Memory R/W *******************************/

void MEM_CalAddr(unsigned char sector_addr,
                 unsigned char block_addr,
                 unsigned char page_addr,
				 unsigned char line_addr)
{

	//------------------- 528 bytes Structure -----------------------
	#if defined(MEM_Type0)											// AT45DB161D
		third_addr  = ((sector_addr << 2) & 0x3C) |
					  ((block_addr >> 3) & 0x03);					// A21 - A16
		second_addr = ((block_addr << 5) & 0xE0) | 
					   ((page_addr << 2) & 0x1C) |
					   ((line_addr >> 2) & 0x03);					// A15 - A8
		first_addr  = line_addr * 64;								// A7  - A0
	#endif
	//-------------------------------------------------------
	#if defined(MEM_Type1)											// AT45DB321D
		//third_addr  = ((sector_addr << 1) & 0x7E) |
		//			  ((block_addr >> 3) & 0x01);					// A22 - A16
		//second_addr = ((block_addr << 5) & 0xE0) | 
		//			   ((page_addr << 2) & 0x1C) |
		//			   ((line_addr >> 2) & 0x03);					// A15 - A8
		//first_addr  = line_addr * 64;								// A7  - A0
		third_addr = sector_addr*2 + block_addr/8;					// A22 - A16.
		second_addr = block_addr*32 + page_addr*4 + line_addr/4;	// A15 - A8.
		first_addr = line_addr*64;									// A7  - A0.

	#endif

}

//-------------------------------------------------------------------------------
unsigned char MEM_status(unsigned char chip_addr)
{
    unsigned char mem_STS;

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0xD7);						// Read status command.
	mem_STS =SPI2_RW(0);

	MEM_CE0 = 1;
	MEM_CE1 = 1;

	return(mem_STS);
}

//----------------------------------------------------------------------------------
void MEM_Format(void)
{
	unsigned char i;

	for(i=0;i<64;i++) mem_BUF[i] = 0xff;
	mem_BUF[0] = 0x88;
	MEM_WriteLine(0,0,0,0,0);

	for(i=0;i<64;i++) mem_BUF[i] = 0x00;		// Operation information.
	MEM_WriteLine(0,0,1,7,0);

	for(i= 0;i<32;i++) mem_BUF[i] = 0xff;
	for(i=32;i<64;i++) mem_BUF[i] = 0x00;

	MEM_WriteLine(0,0,0,0,1);					// Bad block table.
	MEM_WriteLine(0,0,0,0,2);

	#if defined(MEM_Type1)
	 	MEM_WriteLine(0,0,0,0,3);				// Bad block table.
		MEM_WriteLine(0,0,0,0,4);
	#endif

}

//----------------------------------------------------------------------------------
void MEM_EraseBlock(unsigned char chip_addr,
					unsigned char sector_addr,
                    unsigned char block_addr)
{

	MEM_CalAddr(sector_addr,block_addr,0,0);

	//if(MEM_chip == 0) MEM_CE0 = 0;
	//else MEM_CE1 = 0;
	if(chip_addr == 0) MEM_CE0 = 0;	// CL
	else MEM_CE1 = 0;				// CL

	SPI2_RW(0x50);					// Block Erase Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;
	MEM_CE1 = 1;

	//while(!(0x80 & MEM_status(MEM_chip)));	// Checking status: bit7=1 ready.
	while(!(0x80 & MEM_status(chip_addr)));	// Checking status: bit7=1 ready.

}

//----------------------------------------------------------------------------------
void MEM_ErasePage(unsigned char chip_addr,
				   unsigned char sector_addr,
                   unsigned char block_addr,
				   unsigned char page_addr)
{

	MEM_CalAddr(sector_addr,block_addr,page_addr,0);

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x81);					// Page Erase Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;
	MEM_CE1 = 1;

	while(!(0x80 & MEM_status(chip_addr)));	// Checking status: bit7=1 ready.

}

//------------------------------------------------------------------------------------
void MEM_ReadLine(unsigned char chip_addr,
				  unsigned char sector_addr,
	          	  unsigned char block_addr,
                  unsigned char page_addr,
                  unsigned char line_addr)
{
    unsigned char i;

	MEM_CalAddr(sector_addr,block_addr,page_addr,line_addr);// Cal address

	//--------------------------------
	// Main Memory Page Read: opcode = 0xD2.
	// Read memory main page directly, bypassing buffers.
	// The read operation starts after the 4 zero-bytes.
	// The read operation stops after the CS is de-asserted.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0xD2);						// Main Memory Page Read Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);		
	SPI2_RW(0);
	SPI2_RW(0);
	SPI2_RW(0);
	SPI2_RW(0);

	for(i=0;i<=63;i++)					// Read 64 bytes continuously.
		{
			mem_BUF[i] =SPI2_RW(0);
		}

	MEM_CE0 = 1;						// De-assert the CS, and the read operation is completed.
	MEM_CE1 = 1;						// De-assert the CS, and the read operation is completed.

}

//---------------------------------------------------------------------------------
// This sub-routine:
// 1) Read a page to Buffer1 (0x53), from the main memory. The three address bytes indicate the page address: 13 page adress bits, 10 don't care bits.
// 2) Write a line (64 bytes) to Buffer1 (0x84) page. The three address bytes indicate the location of the bytes within the page: 14 don't cares bits, 10 byte address bits.
// 3) Program the Buffer1 page (0x88), to the main memory. The three address bytes indicate the page address: 13 page adress bits, 10 don't care bits.
void MEM_WriteLine(unsigned char chip_addr,
				   unsigned char sector_addr,
	           	   unsigned char block_addr,
                   unsigned char page_addr,
                   unsigned char line_addr)
{
     unsigned char i;

	MEM_CalAddr(sector_addr,block_addr,page_addr,line_addr);	// Cal address

	//--------------------------------
	// Main Memory Page to Buffer Transfer: opcode = 0x53 for buffer 1; opcode = 0x55 for buffer 2.
	// A page of data can be transferred from the main memory to either buffer 1 or buffer 2.
	// The transfer of the data will start after the command is over and the CS is de-asserted.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x53);						// Main Memory Page to Buffer 1 Transfer Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;						// The command is over; the CS is de-asserted: the transfer starts here.
	MEM_CE1 = 1;						// The command is over; the CS is de-asserted: the transfer starts here.

	while(!(0x80 & MEM_status(chip_addr)));		// Checking status: bit7=1 ready.

	//--------------------------------
	// Buffer Write: opcode = 0x84 for buffer 1; opcode = 0x87 for buffer 2.
	// Data can be clocked in from the input pin (SI) into either buffer 1 or buffer 2.
	// The write operation starts immediately after the command, and will continue until the CS is de-asserted.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x84);						// Buffer 1 Write Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);
	
	for(i=0;i<=63;i++)					// Write 64 bytes data to buffer
		{
			SPI2_RW(mem_BUF[i]);		 
		}

	MEM_CE0 = 1;						// De-assert the CS, and the write operation is completed.
	MEM_CE1 = 1;						// De-assert the CS, and the write operation is completed.

	while(!(0x80 & MEM_status(chip_addr)));		// Checking status: bit7=1 ready

	//--------------------------------
	// Buffer to Main Memory Page Program without Built-in Erase: opcode = 0x88 for buffer 1; opcode = 0x89 for buffer 2.
	// A previously-erased page within main memory can be programmed with the contents of either buffer 1 or buffer 2.
	// After the CS is de-asserted, the part will program the data stored in the buffer into the specified page in the main memory.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x88);						// Buffer 1 to Main Memory Page Program Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;						// De-assert the CS; programming starts.
	MEM_CE1 = 1;						// De-assert the CS; programming starts.

	while(!(0x80 & MEM_status(chip_addr)));		// status: bit7=1 ready
}

//----------------------------------------------------------------------------
unsigned char MEM_CompWrite(unsigned char chip_addr)
{
  unsigned char st;

	//--------------------------------
	// Main Memory Page to Buffer Compare: opcode = 0x60 for buffer 1; opcode = 0x61 for buffer 2.
	// A page of data can be compared to the data in either buffer 1 or buffer 2.
	// On the Low to High transition of CS, the data bytes in the selected main memory page will be
	// compared with the data in Buffer 1 or Buffer 2.
	// On completion of the compare operation, bit 6 of the Status Register is updated with the result.

	//if(MEM_chip == 0) MEM_CE0 = 0;
	//else MEM_CE1 = 0;
	if(chip_addr == 0) MEM_CE0 = 0;	// CL
	else MEM_CE1 = 0;				// CL

	SPI2_RW(0x60);						// Main Memory Page to Buffer 1 Compare Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;
	MEM_CE1 = 1;

	do {
		//st = MEM_status(MEM_chip);
		st = MEM_status(chip_addr);	// CL
	   } while(!(0x80 & st));			// Checking status: bit7=1 ready

	if((0x40 & st) == 0) return(0);		// Checking Status: Bit6=0 No Err.
	else return(1);
}

//--------------------------------------------------------------------------------
void MEM_ReWritePage(unsigned char chip_addr)
{
 
	//--------------------------------
	// Buffer to Main Memory Page Program with Built-in Erase: opcode = 0x83 for buffer 1; opcode = 0x86 for buffer 2.
	// Date written into either buffer 1 or buffer 2 can be programmed into the selected page of the main memory.
	// After the CS is de-asserted, the part will first erase the selected page with '1' and then program the data
	// stored in the buffer into the specified page in the main memory.

	//if(MEM_chip == 0) MEM_CE0 = 0;
	//else MEM_CE1 = 0;
	if(chip_addr == 0) MEM_CE0 = 0;	// CL
	else MEM_CE1 = 0;				// CL

	SPI2_RW(0x83);						// Buffer 1 to Main Memory Page Program with Built-in Erase Commanmd.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;						// De-assert the CS; erasing and programming process starts.
	MEM_CE1 = 1;						// De-assert the CS; erasing and programming process starts.

	//while(!(0x80 & MEM_status(MEM_chip)));		// Checking status: bit7=1 ready
	while(!(0x80 & MEM_status(chip_addr)));		// Checking status: bit7=1 ready - CL

}

//--------------------------------------------------------------------------------
void Init_FLASH_MEM(void)
{
	MEM_chip = 0;
	MEM_sector = 0;
	MEM_block = 0;
	MEM_page = 0;
	MEM_line = 0;
}

//--------------------------------------------------------------------------------
void MEM_DeviceID(void)
{
	MEM_CE0 = 0;

	SPI2_RW(0x9F);						// Read memory device ID
	MEM_Manufacturer_ID =SPI2_RW(0);	
	MEM_Device_ID1      =SPI2_RW(0);
	MEM_Device_ID2      =SPI2_RW(0);
	SPI2_RW(0);							// extened device information: 0

	MEM_CE0 = 1;
}

////------------------------------------------------------------------------------
//void MEM_FindNext(void)					//find next good block
//{
//	#if defined(MEM_Type0)						// AT45DB161D
//		if(MEM_block == NBLOCK - 2) {
//			if(MEM_sector == NSECTS - 1) {
//				MEM_chip = MEM_chip + 1;
//				MEM_sector = 0;
//				MEM_block = 0;
//				MEM_page  = 0;
//				MEM_line  = 0;
//
//				while(MEM_chip == NCHIPS) {	 
//					Nop();						// Delay1TCY();
//					Nop();						// Delay1TCY();
//					Sleep();					// sleep
//					Nop();						// Delay1TCY();
//					Nop();						// Delay1TCY();
//				}
//			}
//		}
//		else if(MEM_block == NBLOCK) {
//			MEM_sector = MEM_sector + 1;
//			MEM_block  = 0;
//			MEM_page   = 0;
//			MEM_line   = 0;
//		}
//	#endif
//	//-----------------------------------------------------------------
//	#if defined(MEM_Type1)						// AT45DB321D
//		if(MEM_block == NBLOCK - 2) {			// skip B255
//			if(MEM_sector == NSECTS/2 - 1) {
//				MEM_sector = MEM_sector + 1;
//				MEM_block = 0;
//				MEM_page  = 0;
//				MEM_line  = 0;
//			}
//
//			if(MEM_sector == NSECTS -1) {
//				MEM_chip = MEM_chip + 1;
//				MEM_sector = 0;
//				MEM_block = 0;
//				MEM_page  = 0;
//				MEM_line  = 0;
//
//				while(MEM_chip == NCHIPS) {	 
//					Nop();						// Delay1TCY();
//					Nop();						// Delay1TCY();
//					Sleep();					// sleep
//					Nop();						// Delay1TCY();
//					Nop();						// Delay1TCY();
//				}
//			}
//		}
//		else if(MEM_block == NBLOCK) {
//			MEM_sector = MEM_sector + 1;
//			MEM_block = 0;
//			MEM_page  = 0;
//			MEM_line  = 0;
//		}
//	#endif
//}

//------------------------------------------------------------------------------
void MEM_FindNext(void)					//find next good block
{
	#if defined(MEM_Type0)						// AT45DB161D
		if(MEM_block == NBLOCK - 2) {
			if(MEM_sector == NSECTS - 1) {
				MEM_chip = MEM_chip + 1;
				MEM_sector = 0;
				MEM_block = 0;
				MEM_page  = 0;
				MEM_line  = 0;

				while(MEM_chip == NCHIPS) {	 
					Nop();						// Delay1TCY();
					Nop();						// Delay1TCY();
					Sleep();					// sleep
					Nop();						// Delay1TCY();
					Nop();						// Delay1TCY();
				}
			}
		}
		else if(MEM_block == NBLOCK) {
			MEM_sector = MEM_sector + 1;
			MEM_block  = 0;
			MEM_page   = 0;
			MEM_line   = 0;
		}
	#endif
	//-----------------------------------------------------------------
	#if defined(MEM_Type1)						// AT45DB321D
		//if(MEM_block == NBLOCK - 2) {			// skip B255
		//	if(MEM_sector == NSECTS/2 - 1) {
		//		MEM_sector = MEM_sector + 1;
		//		MEM_block = 0;
		//		MEM_page  = 0;
		//		MEM_line  = 0;
		//	}
		//
		//	if(MEM_sector == NSECTS -1) {
		//		MEM_chip = MEM_chip + 1;
		//		MEM_sector = 0;
		//		MEM_block = 0;
		//		MEM_page  = 0;
		//		MEM_line  = 0;
		//
		//		while(MEM_chip == NCHIPS) {	 
		//			Nop();						// Delay1TCY();
		//			Nop();						// Delay1TCY();
		//			Sleep();					// sleep
		//			Nop();						// Delay1TCY();
		//			Nop();						// Delay1TCY();
		//		}
		//	}
		//}
		//else if(MEM_block == NBLOCK) {
		if(MEM_block >= NBLOCK)
		{
			if (MEM_sector < (NSECTS-1))
			{
				MEM_sector = MEM_sector + 1;
				MEM_block = 0;
				MEM_page  = 0;
				MEM_line  = 0;
			}
			else
			{
				if (MEM_chip < (NCHIPS-1))
				{
					MEM_chip = MEM_chip + 1;
					if ((MEM_chip == 0) || (MEM_chip == 1))
					{
						MEM_sector = 4;
						MEM_block = 0;
						MEM_page  = 0;
						MEM_line  = 0;
					}
					else
					{
						MEM_sector = 0;
						MEM_block = 0;
						MEM_page  = 0;
						MEM_line  = 0;
					}
				}
				else
				{
					MEM_chip = NCHIPS - 1;
					MEM_sector = NSECTS - 1;
					MEM_block = NBLOCK - 1;
					MEM_page  = 7;
					MEM_line  = 7;
				}
			}
		}
	#endif
}

//-------------------------------------------------------------------------------
//void MEM_FindFirst(void)
void MEM_FindFirst(unsigned char *blk_map)	// The above line is original. CL
{
	MEM_chip   = 0;
	MEM_sector = 0;
	//MEM_block  = 3*2;			// AT45DB161/321: The original line.
	MEM_block  = 2;			// The above line is original. CL
	MEM_page   = 0;
	MEM_line   = 0;

	do {
		do
		{
			MEM_block = MEM_block + 2;
			MEM_FindNext();
		} while (MEM_CheckBlock(MEM_chip,MEM_sector,MEM_block,blk_map)!=0);
		//MEM_block = MEM_block + 2;	// Original.
		//MEM_FindNext();	// Original.
		MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
	} while(mem_BUF[0]!=0xff);
}

//-------------------------------------------------------------------------------
void MEM_FindCurrent(unsigned char jcnt, unsigned char *table)
{
	if (jcnt > 0)
	{
		MEM_chip   = table[(jcnt-1)*3];
		MEM_sector = table[(jcnt-1)*3+1];
		MEM_block  = table[(jcnt-1)*3+2];
	}
	else
	{
		MEM_chip   = table[0];
		MEM_sector = table[1];
		MEM_block  = table[2];
	}
	MEM_page   = 0;
	MEM_line   = 0;
}

//-------------------------------------------------------------------------------
void MEM_FindLine(unsigned char *blk_map)
{
	//MEM_chip   = 0;
	//MEM_sector = 0;
	//MEM_block  = 2;

	MEM_page   = 7;
	MEM_line   = 7;

	MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
	while(mem_BUF[0]!=0xff)
	{
		do
		{
			MEM_block = MEM_block + 1;
			MEM_FindNext();
		} while (MEM_CheckBlock(MEM_chip,MEM_sector,MEM_block,blk_map)!=0);
		MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
	}

	MEM_page   = 0;
	MEM_line   = 255;

	do {
		MEM_line += 1;
		if (MEM_line == 8)
		{
			MEM_page += 1;
			MEM_line = 0;
			if (MEM_page == 8)
			{
				MEM_block += 1;
				MEM_page = 0;
			}
		}
		MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
	} while(mem_BUF[0]!=0xff);
}


////-------------------------------------------------------------------------------
//void MEM_NextBlock(unsigned char *blk_map)
//{
//	//MEM_chip   = 0;
//	//MEM_sector = 0;
//	//MEM_block  = 0;
//	//MEM_page   = 0;
//	//MEM_line   = 0;
//	do
//	{
//		do
//		{
//			MEM_block = MEM_block + 1;
//			MEM_FindNext();
//		} while (MEM_CheckBlock(MEM_chip,MEM_sector,MEM_block,blk_map)!=0);
//		MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
//	} while(mem_BUF[0]!=0xff);
//}

//-------------------------------------------------------------------------------
void MEM_NextULine(unsigned char *blk_map)
{
	//MEM_chip   = 0;
	//MEM_sector = 0;
	//MEM_block  = 0;
	//MEM_page   = 0;
	//MEM_line   = 0;
	MEM_line += 1;
	if (MEM_line > 7)
	{
		MEM_page += 1;
		MEM_line = 0;
		if (MEM_page > 7)
		{
			MEM_page = 0;
			do
			{
				MEM_block = MEM_block + 1;
				MEM_FindNext();
			} while (MEM_CheckBlock(MEM_chip,MEM_sector,MEM_block,blk_map)!=0);
		}
	};
}

//-------------------------------------------------------------------------------
void MEM_NextBLine(unsigned char *blk_map)
{
	//MEM_chip   = 0;
	//MEM_sector = 0;
	//MEM_block  = 0;
	//MEM_page   = 0;
	//MEM_line   = 0;
	MEM_line += 1;
	if (MEM_line > 7)
	{
		MEM_page += 1;
		MEM_line = 0;
		if (MEM_page > 7)
		{
			MEM_page = 0;
			//MEM_NextBlock(blk_map);
			do
			{
				do
				{
					MEM_block = MEM_block + 1;
					MEM_FindNext();
				} while (MEM_CheckBlock(MEM_chip,MEM_sector,MEM_block,blk_map)!=0);
				MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
			} while(mem_BUF[0]!=0xff);
		}
	};
}

//-------------------------------------------------------------------------------
unsigned char MEM_CountJob(unsigned char *blk_map, unsigned char *table)
{
	unsigned char job_i = 0;
	unsigned char jcnt = 0;
	MEM_chip   = 0;
	MEM_sector = 0;
	MEM_block  = 2;
	MEM_page   = 0;
	MEM_line   = 0;
	for (job_i=0;job_i<20;job_i++)
	{
		table[job_i*3] = 0;
		table[job_i*3+1] = 0;
		table[job_i*3+2] = 4;
	}
	do {
		do
		{
			MEM_block = MEM_block + 2;
			MEM_FindNext();
		} while (MEM_CheckBlock(MEM_chip,MEM_sector,MEM_block,blk_map)!=0);
		MEM_ReadLine(MEM_chip,MEM_sector,MEM_block,MEM_page,MEM_line);
		if (mem_BUF[0]==0xAA)
		{
			jcnt ++;
			table[(jcnt-1)*3] = MEM_chip;
			table[(jcnt-1)*3+1] = MEM_sector;
			table[(jcnt-1)*3+2] = MEM_block;
		}
	} while(mem_BUF[0]!=0xff);

	return (jcnt);
}






//----------------------------------------------------------------------------------
unsigned char MEM_TestBlock(unsigned char chip_addr, unsigned int block_num, unsigned char *blk_map)
{

	unsigned char sector_addr, block_addr;
	unsigned char mem_stat = 0;
	unsigned char i, j, k;

	unsigned int byte_index;
	unsigned char bit_index;
	unsigned char bit_mask;	

	sector_addr = block_num/16;
	block_addr = block_num%16;
	MEM_EraseBlock(chip_addr, sector_addr, block_addr);
	for(k=0;k<64;k++) mem_BUF[k] = 0xAA;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++) MEM_WriteLine(chip_addr, sector_addr, block_addr, i, j);
		if(MEM_CompWrite(chip_addr)) mem_stat += 1;
	}
	MEM_EraseBlock(chip_addr, sector_addr, block_addr);
	for(k=0;k<64;k++) mem_BUF[k] = 0x55;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++) MEM_WriteLine(chip_addr, sector_addr, block_addr, i, j);
		if(MEM_CompWrite(chip_addr)) mem_stat += 1;
	}
	MEM_EraseBlock(chip_addr, sector_addr, block_addr);

	byte_index = chip_addr*128 + block_num/8;
	bit_index = block_num%8;
	switch (bit_index)
	{
		case 0:	bit_mask = 0b10000000; break; 
		case 1:	bit_mask = 0b01000000; break; 
		case 2:	bit_mask = 0b00100000; break; 
		case 3:	bit_mask = 0b00010000; break; 
		case 4:	bit_mask = 0b00001000; break; 
		case 5:	bit_mask = 0b00000100; break; 
		case 6:	bit_mask = 0b00000010; break; 
		case 7:	bit_mask = 0b00000001; break; 
	}
	if (mem_stat == 0)
	{
		bit_mask ^= 0b11111111;
		blk_map[byte_index] &= bit_mask;
	}
	else blk_map[byte_index] |= bit_mask;

	return (mem_stat);

}




//----------------------------------------------------------------------------------
unsigned char MEM_QuickBlock(unsigned char chip_addr, unsigned int block_num, unsigned char *blk_map)
{

	unsigned char sector_addr, block_addr;
	unsigned char mem_stat = 0;
	unsigned char i, k;

	unsigned int byte_index;
	unsigned char bit_index;
	unsigned char bit_mask;	

	sector_addr = block_num/16;
	block_addr = block_num%16;
	MEM_EraseBlock(chip_addr, sector_addr, block_addr);
	for(k=0;k<64;k++) mem_BUF[k] = ((k%16)<<4) + (k%16);
	for(i=0;i<8;i++)
	{
		MEM_WriteLine(chip_addr, sector_addr, block_addr, i, i);
		if(MEM_CompWrite(chip_addr)) mem_stat += 1;
	}
	MEM_EraseBlock(chip_addr, sector_addr, block_addr);

	byte_index = chip_addr*128 + block_num/8;
	bit_index = block_num%8;
	switch (bit_index)
	{
		case 0:	bit_mask = 0b10000000; break; 
		case 1:	bit_mask = 0b01000000; break; 
		case 2:	bit_mask = 0b00100000; break; 
		case 3:	bit_mask = 0b00010000; break; 
		case 4:	bit_mask = 0b00001000; break; 
		case 5:	bit_mask = 0b00000100; break; 
		case 6:	bit_mask = 0b00000010; break; 
		case 7:	bit_mask = 0b00000001; break; 
	}
	if (mem_stat != 0) blk_map[byte_index] |= bit_mask;

	return (mem_stat);

}




//----------------------------------------------------------------------------------
unsigned char MEM_CheckBlock(unsigned char chip_addr, unsigned char sector_addr, unsigned char block_addr, unsigned char *blk_map)
{

	unsigned int byte_index;
	unsigned char bit_index;
	unsigned char bit_mask;	

	byte_index = chip_addr*128 + sector_addr*2 + block_addr/8;
	bit_index = block_addr%8;
	switch (bit_index)
	{
		case 0:	bit_mask = 0b10000000; break; 
		case 1:	bit_mask = 0b01000000; break; 
		case 2:	bit_mask = 0b00100000; break; 
		case 3:	bit_mask = 0b00010000; break; 
		case 4:	bit_mask = 0b00001000; break; 
		case 5:	bit_mask = 0b00000100; break; 
		case 6:	bit_mask = 0b00000010; break; 
		case 7:	bit_mask = 0b00000001; break; 
	}

	return (blk_map[byte_index] & bit_mask);

}



//----------------------------------------------------------------------------------
//void MEM_NextBlock(unsigned char *map)
//{
//
//	unsigned int next_blk;
//	unsigned int byte_num;
//	unsigned char bit_num, bit_mask;
//	
//	next_blk = MEM_chip*1024 + MEM_sector*16 + MEM_block;
//	do {
//		next_blk += 1;
//		if ((next_blk >= 0) && (next_blk <= 3)) next_blk = 4;
//		else if ((next_blk >= 1024) && (next_blk <= 1027)) next_blk = 1028;
//		byte_num = next_blk / 8;
//		bit_num = next_blk % 8;
//		switch (bit_num)
//		{
//			case 0:	bit_mask = 0b10000000; break; 
//			case 1:	bit_mask = 0b01000000; break; 
//			case 2:	bit_mask = 0b00100000; break; 
//			case 3:	bit_mask = 0b00010000; break; 
//			case 4:	bit_mask = 0b00001000; break; 
//			case 5:	bit_mask = 0b00000100; break; 
//			case 6:	bit_mask = 0b00000010; break; 
//			case 7:	bit_mask = 0b00000001; break; 
//		}
//
//	}	while (map[byte_num]&bit_mask);
//
//	if (next_blk <= 1023) MEM_chip = 0;
//	else
//	{
//		MEM_chip = 1;
//		next_blk -= 1024;
//	}
//	MEM_sector = next_blk / 16;
//	MEM_block = next_blk % 16;
//
//}



//---------------------------------------------------------------------------------


void MEM_CalAddrByte(unsigned char sector_addr,
					 unsigned char block_addr,
                 	 unsigned char page_addr,
				 	 unsigned int byte_addr)
{

	//------------------- 528 bytes Structure -----------------------
	#if defined(MEM_Type0)											// AT45DB161D
		third_addr  = ((sector_addr << 2) & 0x3C) |
					  ((block_addr >> 3) & 0x03);					// A21 - A16
		second_addr = ((block_addr << 5) & 0xE0) | 
					   ((page_addr << 2) & 0x1C) |
					   ((line_addr >> 2) & 0x03);					// A15 - A8
		first_addr  = line_addr * 64;								// A7  - A0
	#endif
	//-------------------------------------------------------
	#if defined(MEM_Type1)											// AT45DB321D
		//third_addr  = ((sector_addr << 1) & 0x7E) |
		//			  ((block_addr >> 3) & 0x01);					// A22 - A16
		//second_addr = ((block_addr << 5) & 0xE0) | 
		//			   ((page_addr << 2) & 0x1C) |
		//			   ((line_addr >> 2) & 0x03);					// A15 - A8
		//first_addr  = line_addr * 64;								// A7  - A0
		third_addr = sector_addr*2 + block_addr/8;					// A22 - A16.
		second_addr = block_addr*32 + page_addr*4 + byte_addr/256;	// A15 - A8.
		first_addr = byte_addr%256;									// A7  - A0.

	#endif

}



//---------------------------------------------------------------------------------
// This sub-routine:
// 1) Read a page to Buffer1 (0x53), from the main memory. The three address bytes indicate the page address: 13 page adress bits, 10 don't care bits.
// 2) Write a line (64 bytes) to Buffer1 (0x84) page. The three address bytes indicate the location of the bytes within the page: 14 don't cares bits, 10 byte address bits.
// 3) Program the Buffer1 page (0x88), to the main memory. The three address bytes indicate the page address: 13 page adress bits, 10 don't care bits.
void MEM_WriteByte(unsigned char chip_addr,
				   unsigned char sector_addr,
	           	   unsigned char block_addr,
                   unsigned char page_addr,
                   unsigned int byte_addr, unsigned char length)
{
     unsigned char i;

	MEM_CalAddrByte(sector_addr,block_addr,page_addr,byte_addr);	// Cal address

	//--------------------------------
	// Main Memory Page to Buffer Transfer: opcode = 0x53 for buffer 1; opcode = 0x55 for buffer 2.
	// A page of data can be transferred from the main memory to either buffer 1 or buffer 2.
	// The transfer of the data will start after the command is over and the CS is de-asserted.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x53);						// Main Memory Page to Buffer 1 Transfer Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;						// The command is over; the CS is de-asserted: the transfer starts here.
	MEM_CE1 = 1;						// The command is over; the CS is de-asserted: the transfer starts here.

	while(!(0x80 & MEM_status(chip_addr)));		// Checking status: bit7=1 ready.

	//--------------------------------
	// Buffer Write: opcode = 0x84 for buffer 1; opcode = 0x87 for buffer 2.
	// Data can be clocked in from the input pin (SI) into either buffer 1 or buffer 2.
	// The write operation starts immediately after the command, and will continue until the CS is de-asserted.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x84);						// Buffer 1 Write Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);
	
	for(i=0;i<=length;i++)					// Write 64 bytes data to buffer
		{
			SPI2_RW(mem_BUF[i]);		 
		}

	MEM_CE0 = 1;						// De-assert the CS, and the write operation is completed.
	MEM_CE1 = 1;						// De-assert the CS, and the write operation is completed.

	while(!(0x80 & MEM_status(chip_addr)));		// Checking status: bit7=1 ready

	//--------------------------------
	// Buffer to Main Memory Page Program without Built-in Erase: opcode = 0x88 for buffer 1; opcode = 0x89 for buffer 2.
	// A previously-erased page within main memory can be programmed with the contents of either buffer 1 or buffer 2.
	// After the CS is de-asserted, the part will program the data stored in the buffer into the specified page in the main memory.

	if(chip_addr == 0) MEM_CE0 = 0;
	else MEM_CE1 = 0;

	SPI2_RW(0x88);						// Buffer 1 to Main Memory Page Program Command.
	SPI2_RW(third_addr);	
	SPI2_RW(second_addr);
	SPI2_RW(first_addr);	

	MEM_CE0 = 1;						// De-assert the CS; programming starts.
	MEM_CE1 = 1;						// De-assert the CS; programming starts.

	while(!(0x80 & MEM_status(chip_addr)));		// status: bit7=1 ready
}










