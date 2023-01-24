#include "draw.h"

void draw_begin(unsigned int addr) {
    // Frame
    DRAWCMD = 0x20000000;
    DRAWCMD = addr;
    DRAWCMD = 1280<<16 | 1024;

    // Draw Area
    DRAWCMD = 0x21000000;
    DRAWCMD = 0<<16 | 0;
    DRAWCMD = 1280<<16 | 1024;
}

void draw_end() {
    DRAWCMD = 0x0F000000;   // EDOL
    DRAWCTRL = DRAWEXE;
    while ((DRAWSTAT & DRAWBUSY) != 0);
    DRAWCTRL = DRAWRST;
}

void draw_set_color(unsigned int a, unsigned int r, unsigned int g, unsigned int b) {
    DRAWCMD = 0x23000000;
    DRAWCMD = a<<24 | r<<16 | g<<8 | b;
}

void draw_set_stmode(unsigned int mode) {
    DRAWCMD = 0x30000000 | (mode & 0b1);
}

void draw_set_scolor(unsigned int ignore_mask,
                     unsigned int la, unsigned int lr, unsigned int lg, unsigned int lb,
                     unsigned int ha, unsigned int hr, unsigned int hg, unsigned int hb)
{
    DRAWCMD = 0x31000000 | (ignore_mask & 0b1111);
    DRAWCMD = la<<24 | lr<<16 | lg<<8 | lb;
    DRAWCMD = ha<<24 | hr<<16 | hg<<8 | hb;
}

void draw_set_texture(int fmt, unsigned int addr) {
    DRAWCMD = 0x22000000 | fmt;
    DRAWCMD = addr;
}

void draw_box(int x0, int y0, unsigned int width, unsigned int height) {
    DRAWCMD = 0x81000000;
    DRAWCMD = x0<<16 | y0;
    DRAWCMD = width<<16 | height;
}

void draw_tbox(int x0, int y0, unsigned int width, unsigned int height, int sx0, int sy0) {
    DRAWCMD = 0x82000000;
    DRAWCMD = x0<<16 | y0;
    DRAWCMD = width<<16 | height;
    DRAWCMD = sx0<<16 | sy0;
}
