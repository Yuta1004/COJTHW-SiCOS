#ifndef DISPLAY_H
#define DISPLAY_H

#include "cojt/regbus.h"

#define DISP_BASEADDR   (REGBUS_BASEADDR + 0x0000)
#define DISPADDR        (*(volatile unsigned int *)(DISP_BASEADDR + 0x0000))
#define DISPCTRL        (*(volatile unsigned int *)(DISP_BASEADDR + 0x0004))
#define DISPINT         (*(volatile unsigned int *)(DISP_BASEADDR + 0x0008))
#define DISPFIFO        (*(volatile unsigned int *)(DISP_BASEADDR + 0x000c))

#define VBLANK          0x02
#define DISPON          0x01
#define DISPOFF         0x00
#define DISPINTENBL     0x01
#define DISPINTCLR      0x02

#endif
