#include <xc.h>
#include <string.h>

#include <delay.h>
#include "md.h"
#include "mdtimers.h"         		// Timer data definitions.
#include "ecantest.h"         		// Timer data definitions.

#include "spi1.h"
#include "s25fl256l-ming.h"
#include "mdcmd.h"
#include "adc12b.h"			// ADC Header File.

extern CAN8B can8d;
extern void canreply(unsigned char ID, unsigned char * dd);
extern void testfram(void) ;

int main(void) {
    //  uint16_t adcResult;
    unsigned cnt500ms, i, j;

    CAN8B *dd = &can8d;
    /* Call the System Initialize routine*/
    SYS_Initialize();
    // Timer1 Operations:
    initTimer();

    initECAN();
    initDMAECAN();

    /* Interrupt enable control register 2, Enable ECAN1 Interrupt */
    IEC2bits.C1IE = 1;
    /* ECAN module interrupt enable register, TX buffer interrupt enable bit, enable Transmit interrupt */
    C1INTEbits.TBIE = 1;
    /* ECAN module interrupt enable register, RX buffer interrupt enable bit, Enable Receive interrupt */
    C1INTEbits.RBIE = 1;

    mID can2md;

    can2md.message_type = CAN_MSG_DATA;
    can2md.frame_type = CAN_FRAME_STD; // Standard message
    can2md.buffer = 0;
    can2md.data_length = 8;
    can2md.id = ECAN_PC_ID;


    adc1_init();
    adc1_int_disable(); // Interrupt Disable.

    AD1CHS0bits.CH0SA = 0; // Choose AN0 to sample.

 
    FCS_TRIS = 0;
  
//    unsigned long FID;
    FCS = 1;
    SPI1INTInit();
#ifdef FLASH_TEST    
    FID = RD_FID();

    //test S25FL256L FLASH
    unsigned char d[0x100], s1[0x100];

    FLL4READ(s1, 0x10 * FLL_PAGE_SIZE, 0x100);

    for (i = 0; i < 0x100; i++) {
        d[i] = i;
    }
    d[0] = 'a';
    //   FLL4PP(d, 0x10);
    unsigned long ll = 0x10 * FLL_PAGE_SIZE;
    //   FLL4PP(d, 0x10);
    // FLL4SE(ll);

    FLL4READ(s1, ll, 0x100);
#endif
    
    clnwcnfbuf();

    testfram() ;

    while (1) {
        if (mCR.buffer_status == CAN_BUF_FULL) {
            mCR.buffer_status = CAN_BUF_EMPTY;
            mdcmd();
        }
        cnt500ms = mdtimer.tmr1s % 20;
        if (cnt500ms > 9) {
            LED1 = mdtimer.tmr10ms>>3;
            LED0 = !LED1;
        } else LED0 = (mdtimer.tmr10ms >> 5);
        
        if (mdtimer.tmrcan100ms > 9) {

            AD1CHS0bits.CH0SA = 0; // Choose AN0 to sample.
            dd->i[0] = 0x4006;
            dd->i[1]++;
            can8d.i[2] = mdtimer.t2;
            can8d.i[3] = ADC1BUF0;

            canreply(ECAN_PC_ID, (unsigned char *) dd);

            mdtimer.tmrcan100ms = 8;
        }
    }
}
