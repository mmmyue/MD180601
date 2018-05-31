


//*******************************************************************************
// 																				*
//		PPS Motor Drive Firmware												*
//		File:           	   	main.h											*
//		PPS Inc. 	cli 		2011.03.24										*
// 																				*
//*******************************************************************************



#ifndef _MD_MAIN_H
#define _MD_MAIN_H  1


#include <xc.h>		// Register definitions


#include "pwm.h"
#include "ecan.h"



// MD Mode:
//  #define	   	MUD_TRUN
  #define	   	MUD_DBUG
//  #define	   	MUD_MTTX


// Port and Pin Definitions:
#define BEACON_ON			PORTBbits.RB12      	// Beacon ON/OFF control.



//---------------------------------------------------------------------
//			Constant Definitions
//---------------------------------------------------------------------

// Constants:
#define      HW_VER					0x11			// Hardware Ver.1.0.
#define      FW_VER					0x22			// Firmware Ver.1.0.
#define      FSYNC					0x7E			// Firmware Ver.1.0.
#define      BSYNC					0xAA			// Firmware Ver.1.0.
// Default Parameters:
#define      MD_PULSE_WIDTH			100
#define      MD_TRUE				36
#define      MD_FALSE				36
#define      MD_POL					0
#define      MD_CODE				1
// ECAN BUS Commands:
#define      MD_DIAG				0x01
#define      MD_MLVL				0x02
#define      MD_COMT				0x03
#define      MD_CFG					0x05
#define      MD_TXTST				0x20
#define      MD_MTST0				0x1A
#define      MD_MTST				0x1C
#define      MD_MFMT				0x2A
#define      MD_MERS				0x1D
#define      MD_MERS1				0x2B
#define      MD_DFLT				0x1E
#define      MD_SYNC				0x43
#define      MD_NJOB				0x1F
#define      MD_MAPR				0x1B
#define      MD_DATR				0x10
#define      MD_MTTST				0x15
#define      MD_CHECK				0x44
#define      MD_FRM1				0x45
#define      MD_FRM2				0x46
#define      MD_FRM3				0x47
#define      MD_MTMOD				0x4A
#define      MD_DBUG				0x66

// Memory Parameters:
//#define      NUM_CHIPS				2
#define      BMAP_SIZE				256
#define      ECAN_DR_DLY			1000
#define      PULSE_CODING			1
#define      POS_CODING				2

#define      FRM_RESET				1


//---------------------------------------------------------------------
//			Data Definitions:
//---------------------------------------------------------------------


//------------------------------ Motor Data: -------------------------------


// MD General:
typedef enum {PULSE_MODE, POSITION_MODE} modMODE;
modMODE md_mod_mode = POSITION_MODE;

unsigned char ecan_cmd_rdy = 0;
unsigned char md_time[3] = {0, 0, 0};
unsigned char md_time_en = 0;
unsigned char md_job_id[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};


// MD Position Mode Parameters:
unsigned int  md_pos_pulse = MD_PULSE_WIDTH;
unsigned int  md_pos_pulse_cfg = MD_PULSE_WIDTH;
unsigned int  md_pose[5] = {0, 15, 30, 45, 80};
unsigned int  md_pos_count = 0;
unsigned char md_bit_count = 10;
const unsigned int md_pulse_sets[3][8] = {{30, 40, 50, 60, 80, 100, 150, 200},
										{50, 60, 80, 100, 200, 400, 650, 800},
										{10, 12, 15, 20, 50, 60, 80, 100}};
unsigned char md_pulse_set_index = 0;

// MD Pulse Mode Parameters:
unsigned char md_mt_cfg[4][4] = {{0x42, 0x64, 0x00, 0x00}, {0x42, 0x64, 0x00, 0x00}, {0x42, 0x64, 0x00, 0x00}, {0x42, 0x64, 0x00, 0x00}};
unsigned char md_mt_mode = 0;
unsigned int  md_pulse = MD_PULSE_WIDTH;
//unsigned int  md_pulse_cfg = MD_PULSE_WIDTH;
unsigned char md_polarity = MD_POL; 			// '0' - No reversal; '1' - Reversal.
//unsigned char md_polarity_cfg = MD_POL; 		// '0' - No reversal; '1' - Reversal.
unsigned char md_codings = MD_CODE;				// 0 - No coding; 1 - Manchester Coding.
//unsigned char md_codings_cfg = MD_CODE;			// 0 - No coding; 1 - Manchester Coding.
unsigned char md_crc_codings = 1;				// 0 - No coding; 1 - CRC Coding.
//unsigned char md_crc_codings_cfg = 1;			// 0 - No coding; 1 - CRC Coding.
unsigned char md_madj = 0;
unsigned char md_protect = 1;
unsigned int  md_move[4] = {0, 0, 0, 100};

// MD Data:
unsigned int md_pwm_duty = PWM_DUTY_CYC;
//unsigned int md_pwm_duty_count = 0;
unsigned int md_counta = 0;
unsigned int md_countb = 0;
unsigned int md_countc = 0;
unsigned int md_countd = 0;
unsigned int md_countf = 0;
unsigned int md_counth = 0;
unsigned int md_countp = 0;
unsigned int md_total = 0;
unsigned long md_cost = 0;
unsigned long md_costr = 0;
unsigned long md_costc = 0;
unsigned char md_start_flag[3] = {0, 0, 0};
unsigned char md_halt_flag = 0; 
unsigned char md_dir_flag = 0xFF; 

unsigned char md_en = 0;
unsigned char md_on = 0;
unsigned char md_err = 0;
unsigned char md_rdy = 0;
unsigned char md_data[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char md_byte[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char md_buf0[5] = {0, 0, 0, 0, 0};
unsigned char md_buf1[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char md_crc_chksum = 0;
unsigned char md_crc_chksum1 = 0;
unsigned char md_sub = 0;
unsigned int  md_btotal = 0;
unsigned int  md_buf0_ptr = 0;
unsigned int  md_buf1_ptr = 0;
unsigned int  md_data_ptr = 0;
unsigned int  md_byte_ptr = 0;
unsigned char md_source_id = ECAN_PC_ID;
unsigned char md_frm_next = 0;
unsigned char md_frm_next1 = 0;
unsigned char md_frm_last = 0;
unsigned int  md_frm_total = 0;
unsigned char md_frm_reset = 0;
unsigned char md_wait_cnt = 0;
unsigned char md_txrst_cnt = 0;
unsigned char md_txrst_en = 0;
unsigned char md_crc_tst = 0xFF;
unsigned char md_crc_tst1 = 0xFF;

unsigned char pwm_err = 0;
//unsigned char md_oc_en = 0;
//unsigned char md_oc_en1 = 0;
//unsigned char md_oc_cnt = 0;
//unsigned char md_oc_cnt_max = 0;

unsigned char md_clk = 0;
unsigned char frm_sync = 0x7E;
unsigned char bit_sync = 0xAA;

hDATA hall_data, hall_reg;
mdCOMM md_cmmnd = STOP;

typedef enum {LOW, HIGH} mdPOS;
mdPOS md_pos = LOW;

unsigned char clk_synced = 0;


//------------------------------ Memory Data: -------------------------------


// External variables used in mem.c:
unsigned char mem_BUF[64];
unsigned char MEM_chip = 0;
unsigned char MEM_sector = 0;
unsigned char MEM_block = 0;
unsigned char MEM_page = 0;
unsigned char MEM_line = 0;
unsigned char first_addr = 0;
unsigned char second_addr = 0;
unsigned char third_addr = 0;
unsigned char MEM_chip_1 = 0;
unsigned char MEM_sector_1 = 0;
unsigned char MEM_block_1 = 0;
unsigned char MEM_page_1 = 0;
unsigned char MEM_line_1 = 0;
unsigned char MEM_chip_2 = 0;
unsigned char MEM_sector_2 = 0;
unsigned char MEM_block_2 = 0;
unsigned char MEM_page_2 = 0;
unsigned char MEM_line_2 = 0;

unsigned char MEM_Manufacturer_ID;
unsigned char MEM_Device_ID1;
unsigned char MEM_Device_ID2;
unsigned int  md_buf_ptr = 0;


unsigned char blk_map[BMAP_SIZE];
unsigned char blk_stat = 0;
unsigned char cfg_stat = 0;
unsigned char md_jtab[60] = {0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4, 0, 0, 4};
unsigned char md_jcnt = 0;
unsigned char md_jnum = 0;

unsigned char mt_chip = 0;
unsigned char mt_sec = 0;
unsigned int mt_blks = 0;
unsigned int mt_blks1 = 0;
unsigned int mt_blks2 = 0;
unsigned int mt_blk = 0;
unsigned char mt_page = 0;
unsigned char mt_line = 0;
unsigned char mt_byte = 0;
unsigned char mt_tested_stat = 0;
unsigned char mt_tested_chip = 0;
unsigned int mt_tested_blks = 0;
unsigned char mt_ersed_stat = 0;
unsigned char mt_ersed_chip = 0;
unsigned int mt_ersed_blks = 0;

unsigned char mr_chip = 0;
unsigned char mr_sec = 0;
unsigned int mr_blk = 0;
unsigned char mr_page = 0;
unsigned char mr_line = 0;
unsigned char mr_byte = 0;
unsigned int mr_addr = 0;
unsigned int mr_size = 0;

// MD Pulser Buffer:
unsigned char md_rec[24];
unsigned int md_rec_ptr = 0;


//------------------------------ VIB Data: -------------------------------

signed int VIB_AD_Data[2] = {0, 0};
unsigned char vib_clk = 0;
unsigned int vib_cnt = 0;
unsigned int vib_tm = 0;



//------------------------------ MD Fixed-Data Test/Trial Data: -------------------------------

unsigned char md_test_data[24] = {0x7E, 0xA2, 0xC5, 0x62, 0x3D, 0xD4, 0xD8, 0xA6, 0x2C, 0x7A, 0x45, 0x89, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char md_test_data_len = 99;
unsigned char tx_pause = 100;
unsigned char tx_test_mode = 0;


//------------------------------ ECAN Data: -------------------------------

// ECAN Signals:
mID mCT;
mID mCR;
// Define ECAN Message Buffers
extern ECAN1MSGBUF ecan1msgBuf;
extern unsigned char ecan_cmd_reg[8];


//------------------------------ Test Data: -------------------------------


// Debug:
unsigned char beacon_count = 0; 
//unsigned char hall_data_buff[2000]; 
//unsigned int  hall_data_buff_index = 0; 
//unsigned int  md_fwrd_count = 0; 
//unsigned int  md_rvrs_count = 0; 
//unsigned int  md_fwrd_stop_count = 0; 
//unsigned int  md_rvrs_stop_count = 0; 
//unsigned int  md_fwrd_time_reg = 0; 
//unsigned int  md_rvrs_time_reg = 0; 




//---------------------------------------------------------------------
//			Functions
//---------------------------------------------------------------------

int main(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _T1Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _T2Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _T3Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _IC1Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _IC2Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _IC3Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _IC4Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _C1Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _ADC1Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _SPI1Interrupt(void);
void __attribute__ ((__interrupt__, __shadow__, no_auto_psv)) _SPI2Interrupt(void);


#endif
