


//*******************************************************************************
// 																				*
//		PPS Motor Drive Firmware												*
//		File:           	   	pwm.h											*
//		PPS Inc. 	cli 		2011.03.24										*
// 																				*
//*******************************************************************************



#ifndef _MD_PWM_H
#define _MD_PWM_H  1


#include <xc.h>		// Register definitions



//---------------------------------------------------------------------
//Constant Definitions
//---------------------------------------------------------------------



//-----------------------   PWM Definations   -------------------------

#define      PWM_CYC				0x007E					// PWM Cycle.
#define      PWM_ZERO				0x0000					// PWM Zero.
#define      PWM_DUTY_CYC			0x007D					// PWM Duty Cycle. //76.
#define      PWM_LSTGF				0x0026					// PWM Duty Cycle. //6E.
#define      PWM_LSTGR				0x002C					// PWM Duty Cycle. //6E.
#define      PWM_HOLDF				0x0010					// PWM Duty Cycle. //3E.
#define      PWM_HOLDR				0x003F					// PWM Duty Cycle. //3E.



//---------------------------------------------------------------------
//           Data Definitions:
//---------------------------------------------------------------------


// Hall Sensor Data:
typedef union
{
	unsigned char hall_bits; 
	struct {
			unsigned hall1		:1;
			unsigned hall2		:1;
			unsigned hall3		:1;
		   };
} hDATA;


// Motor Commands:
typedef enum {START, FORWARD, REVERSE, LATESTAGEF, LATESTAGER, PAUSE, FHOLD, RHOLD, STOP} mdCOMM;


//-----------------------   PWM Definations   -------------------------

//


//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------


void pwm_en(void);
void pwm_dis(void);
void ic_init(void);
void ic_int_enable(void);
void md_comm(void);
void hall_update(void);



#endif
