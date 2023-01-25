#include "mouse.h"

void mouse_init(unsigned int resol, unsigned int speed) {
    MOUSE_CTRL = 1<<1;
    MOUSE_RESOL = 1<<4 | resol<<2 | speed;
}

int mouse_read(int *xpos, int *ypos, int *zpos, int *btn) {
    if (MOUSE_CTRL & 0b1) {
        if (xpos != 0) *xpos = MOUSE_XPOS & 0x7ff;
        if (ypos != 0) *ypos = MOUSE_YPOS & 0x7ff;
        if (zpos != 0) *zpos = MOUSE_ZPOS & 0x00f;
        if (btn != 0)  *btn  = MOUSE_BTN  & 0x007;
        MOUSE_CTRL &= ~(0b1);
        return 1;
    } else {
        return 0;
    }
}
