


//*******************************************************************************
// 																				*
//		PPS Motor Drive Firmware												*
//		File:           	   	pwm.c											*
//		PPS Inc. 	cli 		2011.03.24										*
// 																				*
//*******************************************************************************



#include <xc.h>		// Register definitions

#include "pwm.h"         		// PWM data definitions.



//---------------------------------------------------------------------
//           Data Definitions
//---------------------------------------------------------------------

extern hDATA hall_data;
extern mdCOMM md_cmmnd;
extern unsigned int md_pwm_duty;
extern unsigned char md_halt_flag; 
hDATA hall_valid_reg[2], hall_data_comm;


//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------



//------------------------------- PWM Enable ----------------------------------

void pwm_en(void)

{

	// Output Compare (PWM1) Initialization:
	OC1CONbits.OCM = 0b000;
	OC1R = 0;
	OC1RS = 0;
	OC1CONbits.OCTSEL = 0;
	OC1CONbits.OCM = 0b110;	// Set Output Compare module to PWM mode.

	// Output Compare (PWM2) Initialization:
	OC2CONbits.OCM = 0b000;
	OC2R = 0;
	OC2RS = 0;
	OC2CONbits.OCTSEL = 0;
	OC2CONbits.OCM = 0b110; // Set Output Compare module to PWM mode.

	// Output Compare (PWM3) Initialization:
	OC3CONbits.OCM = 0b000;
	OC3R = 0;
	OC3RS = 0;
	OC3CONbits.OCTSEL = 0;
	OC3CONbits.OCM = 0b110; // Set Output Compare module to PWM mode.

	// Output Compare (PWM4) Initialization:
	OC4CONbits.OCM = 0b000;
	OC4R = 0;
	OC4RS = 0;
	OC4CONbits.OCTSEL = 0;
	OC4CONbits.OCM = 0b110; // Set Output Compare module to PWM mode.

	// Output Compare (PWM5) Initialization:
	OC5CONbits.OCM = 0b000;
	OC5R = 0;
	OC5RS = 0;
	OC5CONbits.OCTSEL = 0;
	OC5CONbits.OCM = 0b110; // Set Output Compare module to PWM mode.

	// Output Compare (PWM6) Initialization:
	OC6CONbits.OCM = 0b000;
	OC6R = 0;
	OC6RS = 0;
	OC6CONbits.OCTSEL = 0;
	OC6CONbits.OCM = 0b110; // Set Output Compare module to PWM mode.

	// Output Compare (PWM7) Initialization:
	OC7CONbits.OCM = 0b000;
	OC7R = 0;
	OC7RS = 0;
	OC7CONbits.OCTSEL = 0;
	OC7CONbits.OCM = 0b110; // Set Output Compare module to PWM mode.

	// Output Compare (PWM8) Initialization:
	OC8CONbits.OCM = 0b000;
	OC8R = 0;
	OC8RS = 0;
	OC8CONbits.OCTSEL = 0;
	OC8CONbits.OCM = 0b110;	// Set Output Compare module to PWM mode.

}


//------------------------------- PWM Disable ----------------------------------

void pwm_dis(void)

{

	// Output Compare (PWM1) Initialization:
	OC1CONbits.OCM = 0b000;
	OC1R = 0;
	OC1RS = 0;
	OC1CONbits.OCTSEL = 0;

	// Output Compare (PWM2) Initialization:
	OC2CONbits.OCM = 0b000;
	OC2R = 0;
	OC2RS = 0;
	OC2CONbits.OCTSEL = 0;

	// Output Compare (PWM3) Initialization:
	OC3CONbits.OCM = 0b000;
	OC3R = 0;
	OC3RS = 0;
	OC3CONbits.OCTSEL = 0;

	// Output Compare (PWM4) Initialization:
	OC4CONbits.OCM = 0b000;
	OC4R = 0;
	OC4RS = 0;
	OC4CONbits.OCTSEL = 0;

	// Output Compare (PWM5) Initialization:
	OC5CONbits.OCM = 0b000;
	OC5R = 0;
	OC5RS = 0;
	OC5CONbits.OCTSEL = 0;

	// Output Compare (PWM6) Initialization:
	OC6CONbits.OCM = 0b000;
	OC6R = 0;
	OC6RS = 0;
	OC6CONbits.OCTSEL = 0;

	// Output Compare (PWM7) Initialization:
	OC7CONbits.OCM = 0b000;
	OC7R = 0;
	OC7RS = 0;
	OC7CONbits.OCTSEL = 0;

	// Output Compare (PWM8) Initialization:
	OC8CONbits.OCM = 0b000;
	OC8R = 0;
	OC8RS = 0;
	OC8CONbits.OCTSEL = 0;

	LATD &= 0xFF00;

}


//------------------------------- IC Initialization ----------------------------------

void ic_init(void)

{

	// Initialize Capture Module 1:
	IC1CONbits.ICM= 0b00; 			// Disable Input Capture 1 module.
	IC1CONbits.ICTMR= 0; 			// '1' = TMR2 contents are captured on capture event; '0' = TMR3 contents are captured on capture event. Select Timer3 as the IC1 Time base.
	IC1CONbits.ICI= 0b00; 			// Interrupt on every capture event.
	IC1CONbits.ICM= 0b001; 			// Capture mode, every edge – rising and falling (the ICI<1:0> bits do not control interrupt generation for this mode).

	// Initialize Capture Module 2:
	IC2CONbits.ICM= 0b00; 			// Disable Input Capture 2 module.
	IC2CONbits.ICTMR= 0; 			// '1' = TMR2 contents are captured on capture event; '0' = TMR3 contents are captured on capture event. Select Timer3 as the IC2 Time base.
	IC2CONbits.ICI= 0b00; 			// Interrupt on every capture event.
	IC2CONbits.ICM= 0b001; 			// Capture mode, every edge – rising and falling (the ICI<1:0> bits do not control interrupt generation for this mode).

	// Initialize Capture Module 3:
	IC3CONbits.ICM= 0b00; 			// Disable Input Capture 3 module.
	IC3CONbits.ICTMR= 0; 			// '1' = TMR2 contents are captured on capture event; '0' = TMR3 contents are captured on capture event. Select Timer3 as the IC3 Time base.
	IC3CONbits.ICI= 0b00; 			// Interrupt on every capture event.
	IC3CONbits.ICM= 0b001; 			// Capture mode, every edge – rising and falling (the ICI<1:0> bits do not control interrupt generation for this mode).

	// Initialize Capture Module 4:
	IC4CONbits.ICM= 0b00; 			// Disable Input Capture 4 module.
	IC4CONbits.ICTMR= 0; 			// '1' = TMR2 contents are captured on capture event; '0' = TMR3 contents are captured on capture event. Select Timer3 as the IC4 Time base.
	IC4CONbits.ICI= 0b00; 			// Interrupt on every capture event.
	IC4CONbits.ICM= 0b001; 			// Capture mode, every edge – rising and falling (the ICI<1:0> bits do not control interrupt generation for this mode).

}


//------------------------------- IC Initialization ----------------------------------

void ic_int_enable(void)

{

	// Enable Input Capture 1 Interrupt:
	IPC0bits.IC1IP = 5; 			// Setup IC1 interrupt priority level.
	IFS0bits.IC1IF = 0; 			// Clear IC1 Interrupt Status Flag.
	IEC0bits.IC1IE = 1; 			// Enable IC1 interrupt.

	// Enable Input Capture 2 Interrupt:
	IPC1bits.IC2IP = 5; 			// Setup IC2 interrupt priority level.
	IFS0bits.IC2IF = 0; 			// Clear IC2 Interrupt Status Flag.
	IEC0bits.IC2IE = 1; 			// Enable IC2 interrupt.

	// Enable Input Capture 3 Interrupt:
	IPC9bits.IC3IP = 5; 			// Setup IC3 interrupt priority level.
	IFS2bits.IC3IF = 0; 			// Clear IC3 Interrupt Status Flag.
	IEC2bits.IC3IE = 1; 			// Enable IC3 interrupt.

	// Enable Input Capture 4 Interrupt:
	IPC9bits.IC4IP = 5; 			// Setup IC4 interrupt priority level.
	IFS2bits.IC4IF = 0; 			// Clear IC4 Interrupt Status Flag.
	IEC2bits.IC4IE = 1; 			// Enable IC4 interrupt.

}


//--------------------------- MD Command & Commutation ------------------------------

void md_comm(void)

{

	// Update  driving PWM duty cycles:

	switch (md_cmmnd)

		{

			// FORWARD: CW.
			case FHOLD:
			case FORWARD:
			case LATESTAGER:

				if (md_halt_flag == 0) hall_data_comm.hall_bits = hall_data.hall_bits;
				else hall_data_comm.hall_bits = hall_valid_reg[1].hall_bits;
				//switch (hall_data.hall_bits)
				switch (hall_data_comm.hall_bits)
					{
						case 1:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC3RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						case 2:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC5RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						case 3:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						case 4:
							OC1RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							break;
						case 5:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							break;
						case 6:
							OC1RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						default:
							// Do nothing.
							Nop();						// Update PWM cycle.
					}
				break;

			// REVERSE: CCW.
			case RHOLD:
			case REVERSE:
			case LATESTAGEF:

				if (md_halt_flag == 0) hall_data_comm.hall_bits = hall_data.hall_bits;
				else hall_data_comm.hall_bits = hall_valid_reg[1].hall_bits;
				//switch (hall_data.hall_bits)
				switch (hall_data_comm.hall_bits)
					{
						case 1:
							OC1RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						case 2:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							break;
						case 3:
							OC1RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							break;
						case 4:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						case 5:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = PWM_ZERO;			// Update PWM cycle.
							OC3RS = PWM_ZERO;			// Update PWM cycle.
							OC4RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC5RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						case 6:
							OC1RS = PWM_ZERO;			// Update PWM cycle.
							OC2RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC3RS = md_pwm_duty;//PWM_DUTY_CYC;		// Update PWM cycle.
							OC4RS = PWM_ZERO;			// Update PWM cycle.
							OC5RS = PWM_ZERO;			// Update PWM cycle.
							OC6RS = PWM_ZERO;			// Update PWM cycle.
							break;
						default:
							Nop();						// Update PWM cycle.
					}
				break;

			// STOP:
			case START:
			case PAUSE:
			case STOP:

				OC1RS = PWM_ZERO;			// Update PWM cycle.
				OC2RS = PWM_ZERO;			// Update PWM cycle.
				OC3RS = PWM_ZERO;			// Update PWM cycle.
				OC4RS = PWM_ZERO;			// Update PWM cycle.
				OC5RS = PWM_ZERO;			// Update PWM cycle.
				OC6RS = PWM_ZERO;			// Update PWM cycle.
				break;

			default:
				// Do nothing.
				Nop();

		}

}


//------------------------------- Hall Update ----------------------------------

void hall_update(void)
{
	hall_data.hall1 = PORTDbits.RD8;
	hall_data.hall2 = PORTDbits.RD9;
	hall_data.hall3 = PORTDbits.RD10;
	if ((hall_data.hall_bits >= 1) && (hall_data.hall_bits <= 6))
	{
		if (hall_data.hall_bits != hall_valid_reg[0].hall_bits)
		{
			hall_valid_reg[1].hall_bits = hall_valid_reg[0].hall_bits;
			hall_valid_reg[0].hall_bits = hall_data.hall_bits;
		}
	}
	else hall_data.hall_bits = hall_valid_reg[0].hall_bits;
}



