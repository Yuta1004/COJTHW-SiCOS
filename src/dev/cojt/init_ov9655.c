#include "init_ov9655.h"

void sccb_write(unsigned int daddr, unsigned waddr, unsigned wdata) {
    while ((SCCB_STAT & SCCB_BUSY) != 0);
    SCCB_DATA = (daddr << 16) | (waddr << 8) | wdata;
}

void init_ov9655(unsigned char *ov9655) {
    for (int i = 0; ; i+= 2) {
        if (ov9655[i] == 0xff && ov9655[i+1] == 0xff)
            return;
        else
            sccb_write(0x60, ov9655[i], ov9655[i+1]);
    }
}
