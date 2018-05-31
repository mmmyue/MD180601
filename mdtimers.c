#include "mdtimers.h"

MDTimer mdtimer;
MDDATE mddate;

void initTimer(void) {

    /***************************************************************************************************
                                        Timer1: Elapse Time.
     ***************************************************************************************************/
    // TxCON: Time control register; Timer1 Initialization:
    T1CONbits.TON = 0; // Disable Timer1
    T1CONbits.TCS = 0; // Select internal instruction clock.
    T1CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T1CONbits.TCKPS = 0b11; // Select 1:256 Prescaler.
    TMR1 = 0x00; // Clear Timer1 register.
    // Load the period value.(5M*10m/256=160.)
    //#define T10mS Fcy*0.01/256
    PR1 = TMR1_10msPERIOD; // 10 ms
    // Timer2 Interrupt Initialization:
    IPC0bits.T1IP = 0x02; // Set Timer1 Interrupt Priority Level: Level 2.   
    IFS0bits.T1IF = 0; // Clear Timer1 Interrupt Flag.
    IEC0bits.T1IE = 1; // Enable Timer1 Interrupt.
    // Start Timer1:
    T1CONbits.TON = 1; // Start Timer1.

    /***************************************************************************************************
                                        Timer2: PING/4s.
     ***************************************************************************************************/
    // TxCON: Time control register; Timer2 Initialization:
    T2CONbits.TON = 0; // Disable Timer2
    T2CONbits.TCS = 0; // Select internal instruction clock.
    T2CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T2CONbits.TCKPS = 0b11; // Select 1:256 Prescaler.
    TMR2 = 0x00; // Clear Timer2 register.
    PR2 = Fcy / 256; //1s 
    // Timer2 Interrupt Initialization:
    IPC1bits.T2IP = 0x01; // Set Timer2 Interrupt Priority Level: Level 1.   
    IFS0bits.T2IF = 0; // Clear Timer2 Interrupt Flag.
    IEC0bits.T2IE = 1; // Enable Timer2 Interrupt.
    // Start Timer2:
    T2CONbits.TON = 1; // Start Timer2.

    /***************************************************************************************************
                                        Timer3: rt_wpr/s.
     ***************************************************************************************************/
    // TxCON: Time control register; Timer3 Initialization:
    T3CONbits.TON = 0; // Disable Timer3
    T3CONbits.TCS = 0; // Select internal instruction clock.
    T3CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T3CONbits.TCKPS = 0b11; // Select 1:256 Prescaler.
    TMR3 = 0x00; // Clear Timer3 register.
    PR3 = 0x1C20; //ERIC: every 1s acquire data from WPR.
    // Timer3 Interrupt Initialization:
    IPC2bits.T3IP = 0x01; // Set Timer3 Interrupt Priority Level: Level 1.   
    IFS0bits.T3IF = 0; // Clear Timer3 Interrupt Flag.
    IEC0bits.T3IE = 1; // Enable Timer3 Interrupt.
    // Start Timer2:
    // T3CONbits.TON = 1; // Start Timer3.

    /***************************************************************************************************
                                        Timer4: Timeout timer.
        This timer4 is servicing the RX_ISR. Initially the timer is closed until RX interrupts. In side
        the ISR, open the timer4, and the timer is going to counts. If the timer4 overflows, which means
        the time exceeds 5ms (receive complete threshold) so that we know that receive operation is 
        complete. Then the flag rises up, in the main.c we go to handle the rx buffer.
            baud rate = 9600, (1/9600)*10*3 = 3ms 
            10 bits = (start+byte+stop)
     ***************************************************************************************************/
    // TxCON: Time control register; Timer4 Initialization:
    T4CONbits.TON = 0; // Disable Timer4
    T4CONbits.TCS = 0; // Select internal instruction clock.
    T4CONbits.TGATE = 0; // Disable Gated Timer Mode.
    T4CONbits.TCKPS = 0b11; // Select 1:256 Prescaler.
    TMR4 = 0x00; // Clear Timer4 register.
    PR4 = 0x41; //ERIC: every 4ms = 0.004s; 0.004 * 7200 = 29 = 0x41.
    // Timer3 Interrupt Initialization:
    IPC6bits.T4IP = 0x01; // Set Timer4 Interrupt Priority Level: Level 1.   
    IFS1bits.T4IF = 0; // Clear Timer4 Interrupt Flag.
    IEC1bits.T4IE = 1; // Enable Timer4 Interrupt.
    //DONT start timer4 yet.
    //T4CONbits.TON=1;				//Start Timer4.
    //    PORTDbits.RD0 = 1; // R/D en
}

//--------------------------------- Timer1 ISR -----------------------------------------
// 10ms for lLED

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T1Interrupt(void) {
    static unsigned char i = 0, j = 0,l=0;
    i++;
    mdtimer.t1++;
    mdtimer.tmr10ms++;
    l++;
    if(l>4){
        l=0;
        mdtimer.txtk++;
    }
    
    if (i > 9) {
        i = 0;
        mdtimer.tmr100ms++;
        mdtimer.tmrcan100ms++;
        j++;
        if(j>9){
            mdtimer.tmr1s++;
            j=0;
        }
    }
    // Clear Timer1 Interrupt Flag.
    IFS0bits.T1IF = 0;
}


//--------------------------------- Timer2 ISR -----------------------------------------
// 1sec for CAN cycle send message 

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T2Interrupt(void) {
    mdtimer.t2++;
   // mdtimer.tmr1s++;
    // Clear Timer2 Interrupt Flag.
    IFS0bits.T2IF = 0;
}

//--------------------------------- Timer3 ISR -----------------------------------------
// Retreive WPR data/s

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T3Interrupt(void) {
    mdtimer.t3++;
    IFS0bits.T3IF = 0;
}

//--------------------------------- Timer4 ISR -----------------------------------------
//Receive complete threshold.

void __attribute__((__interrupt__, __shadow__, no_auto_psv)) _T4Interrupt(void) {
    //rx_complete = 1;
    mdtimer.t4++;
    //disable timer 4.
    //T4CONbits.TON = 0;
    // Clear Timer4 Interrupt Flag.
    IFS1bits.T4IF = 0;
}
