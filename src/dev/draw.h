#ifndef DRAW_H
#define DRAW_H

#include "cojt/regbus.h"

#define DRAW_BASEADDR   (REGBUS_BASEADDR + 0x2000)
#define DRAWCTRL        (*(volatile unsigned int *)(DRAW_BASEADDR + 0x0000))
#define DRAWSTAT        (*(volatile unsigned int *)(DRAW_BASEADDR + 0x0004))
#define DRAWBUFSTAT     (*(volatile unsigned int *)(DRAW_BASEADDR + 0x0008))
#define DRAWCMD         (*(volatile unsigned int *)(DRAW_BASEADDR + 0x000c))
#define DRAWINT         (*(volatile unsigned int *)(DRAW_BASEADDR + 0x0010))

#define DRAWRST         0x02
#define DRAWEXE         0x01
#define DRAWBUSY        0x01
#define DRAWINTENBL     0x01
#define DRAWINTCLR      0x02

void draw_command(int cmd);
void draw_exec();

void draw_set_frame(unsigned int addr, unsigned int width, unsigned int height);
void draw_set_drawarea(unsigned int x0, unsigned int y0, unsigned int width, unsigned int height);
void draw_set_color(unsigned int a, unsigned int r, unsigned g, unsigned int b);

void draw_box(int x0, int y0, unsigned int width, unsigned int height);

#endif
