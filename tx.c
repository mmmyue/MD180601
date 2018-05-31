#include <string.h> 
#include <stdio.h>
#include "tx.h"

unsigned lllb; //numbers of bit in one frame;
unsigned wwwb; //bits transmitted;

struct {
    unsigned v;
    unsigned char id;
    unsigned char nb;
} mdff[32];

struct {
    unsigned char d[0x100];
    unsigned sumb, sumt, idmax;
} mdfmt;

void getsum(void) {
    unsigned i, j, k, l, vv, ii = 0, ss = 0;
    for (i = 0; i < 32; i++) {
        j = mdff[i].nb;

        if (j == 0) break;
        if (j == 0xff)break;
        ss += j;
    }
    mdfmt.idmax = i;
    mdfmt.sumb = ss;
    j = ss + 2;
    j /= 3;
    ss = j;
    mdfmt.sumt = ss;
    l = 0; //left bit;
    ss = 0; // left value
    for (i = 0; i < mdfmt.idmax; i++) {
        j = mdff[i].nb;
        j += l;
        vv = mdff[i].v;
        vv <<= l;
        vv |= ss;
        for (;;) {
            mdfmt.d[ii] = vv & 0b111;
            if (j < 3)break;
            j -= 3;
            vv >>= 3;
            ii++;
        }
        l = j;
        ss = vv;
    }
}

void testfram(void) {
    unsigned i, k;
    for (i = 0; i < 32; i++) {
        k = 10;
        mdff[i].nb = k; // (i + 3) & 0xf;
        k=1<<k;
        k--;
        mdff[i].v = k;
        //   mdff[i].id = i + 1;
    }
    mdff[11].nb = 0xff;
    getsum();
    for (i = 0; i < mdfmt.sumt; i++) printf("%d", mdfmt.d[i]);

    i = mdfmt.idmax;
    i = mdfmt.sumb;

}

unsigned char tx(void) {
    unsigned c;
    unsigned i;
    //find work data position
    for (i = 0; i < 32; i++) {

    }
    if (wwwb > lllb) wwwb = 0;
    else wwwb += 3;

    //    if (wwwb = 0) t(c);
}