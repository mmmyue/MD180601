


//*******************************************************************************
// 																				*
//		PPS Motor Drive Firmware												*
//		File:           	   	tmr.c											*
//		PPS Inc. 	cli 		2011.03.24										*
// 																				*
//*******************************************************************************



#include <xc.h>		// Register definitions

#include "tmr.h"         		// Timer data definitions.
#include "md.h"         		// Timer data definitions.



//---------------------------------------------------------------------
//           Data Definitions
//---------------------------------------------------------------------



//---------------------------------------------------------------------
//           Functions
//---------------------------------------------------------------------



//------------------------------- Timer1 Initialization ----------------------------------

void tmr1_init(unsigned int t10ms) {
    // Timer1 Initialization:
    T1CONbits.TON = 0; // Disable Timer1.
    T1CONbits.TCS = 0; // Select internal instruction clock.
    T1CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T1CONbits.TCKPS = 0b11; // Select 1:256 Prescaler.
    TMR1 = 0x0000; // Clear Timer1 register.
    PR1 = t10ms; // Load the period value.(4M/256=16K for 1 second)

}


//------------------------------- Timer1 INT Enable ----------------------------------

void tmr1_int_enable(void) {

    // Timer1 Interrupt Initialization:
    IPC0bits.T1IP = 0x05; // Set Timer1 Interrupt Priority Level: Level 1.
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag.
    IEC0bits.T1IE = 1; // Enable Timer1 Interrupt.

}


//------------------------------- Timer2 Initialization ----------------------------------

void tmr2_init(unsigned int pr2_period) {

    // Timer2 Initialization:
    T2CONbits.TON = 0; // Disable Timer2.
    T2CONbits.TCS = 0; // Select internal instruction clock.
    T2CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T2CONbits.TCKPS = 0b00; // Select 1:1 Prescaler.
    TMR2 = 0x0000; // Clear Timer2 register.
    PR2 = pr2_period; // Load the period value.

}


//------------------------------- Timer2 INT Enable ----------------------------------

void tmr2_int_enable(void) {

    // Timer2 Interrupt Initialization:
    IPC1bits.T2IP = 0x01; // Set Timer2 Interrupt Priority Level: Level 1.
    IFS0bits.T2IF = 0; // Clear Timer1 Interrupt Flag.
    IEC0bits.T2IE = 1; // Enable Timer2 Interrupt.

}


//------------------------------- Timer3 Initialization ----------------------------------

void tmr3_init(unsigned int pr3_period) {

    // Timer3 Initialization:
    T3CONbits.TON = 0; // Disable Timer3.
    T3CONbits.TCS = 0; // Select internal instruction clock.
    T3CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T3CONbits.TCKPS = 0b00; // Select 1:1 Prescaler.
    TMR3 = 0x0000; // Clear Timer3 register.
    PR3 = pr3_period; // Load the period value.

}


//------------------------------- Timer3 INT Enable ----------------------------------

void tmr3_int_enable(void) {

    // Timer2 Interrupt Initialization:
    IPC2bits.T3IP = 0x01; // Set Timer2 Interrupt Priority Level: Level 1.
    IFS0bits.T3IF = 0; // Clear Timer1 Interrupt Flag.
    IEC0bits.T3IE = 1; // Enable Timer2 Interrupt.

}

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T1Interrupt(void) {
    cnt10ms++;
    IFS0bits.T1IF = 0;
}
