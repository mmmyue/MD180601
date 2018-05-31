#include "ecantest.h"

void test_EM(void) {
 
    unsigned char  d[0x100];
    int i;
    for(i=0;i<8;i++) d[i]=i;

    if (mdtimer.tmr1s > 5) {
        d[2] = mdtimer.t1 & 0xff;
        toEM(d, 0);
        mdtimer.tmr1s = 3;
    }
}

void toEM(unsigned char *mm, unsigned char cmd) {
    unsigned char i;
    mID can2md;

    can2md.message_type = CAN_MSG_DATA;
    can2md.frame_type = CAN_FRAME_STD; // Standard message
    can2md.buffer = 0;
    can2md.data_length = 8;
    can2md.id = ECAN_PC_ID;
    can2md.data[0] = cmd;
    can2md.data[1] = ECAN_MD_ID;


    for (i = 0; i < 6; i++) {
        can2md.data[i + 2] = mm[i];
    }
    sendECAN(&can2md);


}
