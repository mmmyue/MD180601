//mmmyue@outlook.com
// 20180430

#include <string.h>
#include "mdcmd.h"
#include "config.h"
#include "s25fl256l-ming.h"


CAN8B can8d;

enum CANCMD11 {
    CMDTEST = 1, //PC
    CMDRTIME = 2, //PC
    CMDWTIME = 3, //PC
    CMDRDCNF = 4, //PC
    /*NEW CMDS*/
    CMDWRCNF = 5, //Master
    CMDBITS = 7, //Master
    CMDMAX = 9, //Master
    CMDMIN = 11, //PC
    CMDGAMTIME = 13, //PC/Master
    CMDDITIME = 15, //PC
    CMDPWIDTH = 21, //PC
    CMDPOLL = 23, //PC/Master
    CMDCNFREAD = 24, //PC/Master            
    CMDCNFSAVE = 25, //PC/Master            
} mdcmd1;

void canreply(unsigned char ID, unsigned char * dd) {
    mID can2md;
    can2md.message_type = CAN_MSG_DATA;
    can2md.frame_type = CAN_FRAME_STD; // Standard message
    can2md.buffer = 0;
    can2md.data_length = 8;
    can2md.id = ECAN_PC_ID;
    memcpy(can2md.data, dd, 8);
    sendECAN(&can2md);
}

unsigned char wrfllpage(unsigned long pageaddr, unsigned char *d) {
    unsigned char bb[0x1000];
    unsigned char check = 0xff;
    unsigned int i;
    unsigned long addr = pageaddr << 8;
    unsigned long secadd = addr >> 12; // &=0xfffff000;
    FLL4READ(bb, secadd << 12, FLL_S_SIZE);

    for (i = 0; i < 0x1000; i++) {
        check &= bb[i];
        if (check != 0xff) {
            // FLL4SE(addr & 0xfffff000);
            break;
        }
    }
    unsigned long startp = addr * 0xf00;
    for (i = 0; i < 0x100; i++) bb[startp++] = *d++;
    startp = secadd << 12;
    unsigned char *p = bb;
    for (i = 0; i < 16; i++) {
        //FLL4PP(p,startp);
        p += 0x100;
        startp += 0x100;
    }
    return check;
}
//unsigned char rdcnf(unsigned char page, unsigned char *d){
//    FLL_CMD_4READ()
//}
//unsigned char cnfver[FLL_S_SIZE];

void clnwcnfbuf(void) {
    unsigned i, slen = sizeof (Wcnfbuf);
    unsigned char *pw;
    pw = (unsigned char *) &Wcnfbuf;
    //if saving memory is ff
    for (i = 0; i < slen; i++) *pw++ = 0xff;
}

unsigned char RDCNF(unsigned char ver) {
    unsigned slen = sizeof (Rcnfbuf);
    unsigned addr11 = ver & 0xf;
    addr11 *= FLL_S_SIZE;
    return FLL4READ((unsigned char *) &Rcnfbuf, addr11, slen);

}

unsigned char WRCNF(unsigned char ver) {

    unsigned i, slen = sizeof (Rcnfbuf);
    unsigned long addr = ver << 12;
    addr &= 0xf000;

    unsigned char *pw, *pr, check = 0xff;
    pw = (unsigned char *) &Wcnfbuf;
    //if saving memory is 0xff
    for (i = 0; i < slen; i++) check &= pw[i];
    if (check == 0xff) return check;

    //check target mem to erase;
    unsigned char bb[FLL_S_SIZE];
    FLL4READ(bb, addr, FLL_S_SIZE);
    pr = bb;

    for (i = 0; i < slen; i++) {
        check = (pw[i] != pr[i]);
        if (check) break;
    }
    if (check) {
        check = 0xff;
        for (i = 0; i < FLL_S_SIZE; i++) check &= bb[i];
        if (check != 0xff) FLL4SE(addr);

        memcpy(bb, (unsigned char *) &Wcnfbuf, slen);
        pw = bb;

        slen -= 1;
        unsigned char blk256 = slen >> 8;
        blk256++;
        blk256 &= 0xf;
        unsigned paddr = ver << 4;
        paddr &= 0xf0;
        for (i = 0; i < blk256; i++) {
            FLL4PP(pw, paddr);
            pw += 0x100;
            paddr++;
        }
    }
    return check;
}

unsigned char mdcmd(void) {
    CAN8B *d = &can8d;
    unsigned char ver, sta, pos;


    if (mCR.data[1] == ECAN_PC_ID) {
        memcpy(d, mCR.data, 8);
        d->canbus.sid = ECAN_MD_ID;
        mdcmd1 = d->canbus.cmd;
        ver = d->canbus.ver;
        sta = d->canbus.sta & 0b111;
        pos = d->canbus.pos;
        switch (mdcmd1) {
            case CMDTEST:
                d->canbus.pos = 1;
                d->canbus.ddid = 0;
                canreply(ECAN_PC_ID, (unsigned char *) d);
                break;
            case CMDRTIME:
                RDCNF(ver);
                memcpy(&(d->cantime.mddate), &(Rcnfbuf.hhh.cnftime), sizeof (MDDATE));
                canreply(ECAN_PC_ID, (unsigned char *) d);
                break;
            case CMDWTIME:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                memcpy(&(Wcnfbuf.hhh.cnftime), &(d->cantime.mddate), sizeof (MDDATE));
                break;
            case CMDRDCNF:
                RDCNF(ver);
                d->canbus.ddid = Rcnfbuf.frame[sta][pos].id;
                d->canbus.nb = Rcnfbuf.frame[sta][pos].nbits;
                canreply(ECAN_PC_ID, (unsigned char *) d);
                break;
            case CMDWRCNF:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                Wcnfbuf.frame[sta][pos].id = d->canbus.ddid;
                Wcnfbuf.frame[sta][pos].nbits = d->canbus.nb;
                break;
            case CMDMAX:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                Wcnfbuf.frame[sta][pos].max = d->canbusf.fff;
                break;
            case CMDMIN:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                Wcnfbuf.frame[sta][pos].min = d->canbusf.fff;
                break;
            case CMDGAMTIME:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                Wcnfbuf.hhh.gampre = d->canbusf.fff;
                break;
            case CMDDITIME:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                Wcnfbuf.hhh.dipre = d->canbusf.fff;
                break;
            case CMDPWIDTH:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                Wcnfbuf.hhh.pulsew = d->canbusf.fff;
                break;
            case CMDCNFREAD:
                // memcpy((unsigned char *) &Wcnfbuf, (unsigned char *) &Rcnfbuf, slen);
                RDCNF(ver);
                memcpy((unsigned char *) &(d->cantime.mddate), (unsigned char *) &(Rcnfbuf.hhh.cnftime), sizeof (MDDATE));
                canreply(ECAN_PC_ID, (unsigned char *) d);
                break;
            case CMDCNFSAVE:
                memcpy(&(d->cantime.mddate), &(Wcnfbuf.hhh.cnftime), sizeof (MDDATE));
                canreply(ECAN_PC_ID, (unsigned char *) d);
                WRCNF(ver);
                break;

            default:
                canreply(ECAN_PC_ID, (unsigned char *) d);
                break;
        }
    }
    return mCR.data[1];
}

