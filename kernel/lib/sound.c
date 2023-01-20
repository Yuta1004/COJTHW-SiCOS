#include "sound.h"

void sound_init(unsigned int addr, unsigned int size) {
    SNDADDR = addr;
    SNDSIZE = size & (~0b11);
}

void sound_vol(unsigned char vol) {
    SNDVOL = (unsigned int)vol;
}

void sound_ctrl(unsigned char ctrl) {
    SNDCTRL = (unsigned int)ctrl;
}
