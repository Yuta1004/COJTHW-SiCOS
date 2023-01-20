#ifndef SOUND_H
#define SOUND_H

#include "regbus.h"

#define SND_BASEADDR    (REGBUS_BASEADDR + 0x3000)
#define SNDADDR         (*(volatile unsigned int *)(SND_BASEADDR + 0x0000))
#define SNDSIZE         (*(volatile unsigned int *)(SND_BASEADDR + 0x0004))
#define SNDVOL          (*(volatile unsigned int *)(SND_BASEADDR + 0x0008))
#define SNDCTRL         (*(volatile unsigned int *)(SND_BASEADDR + 0x000c))
#define SNDSTAT         (*(volatile unsigned int *)(SND_BASEADDR + 0x0010))

#define SLOOP   0b100
#define SPLAY   0b001
#define SPAUSE  0b010
#define SSTOP   0b011

void sound_init(unsigned int addr, unsigned int size);
void sound_vol(unsigned char vol);
void sound_ctrl(unsigned char ctrl);

#endif
