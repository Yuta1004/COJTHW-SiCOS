#include "draw.h"

void draw_command(int cmd) {
    DRAWCMD = cmd;
}

void draw_exec() {
    draw_command(0x0F000000);   // EDOL
    DRAWCTRL = DRAWEXE;
    while ((DRAWSTAT & DRAWBUSY) != 0);
    DRAWCTRL = DRAWRST;
}

void draw_set_frame(unsigned int addr, unsigned int width, unsigned int height) {
    draw_command(0x20000000);
    draw_command(addr);
    draw_command(width<<16 | height);
}

void draw_set_drawarea(unsigned int x0, unsigned int y0, unsigned int width, unsigned int height) {
    draw_command(0x21000000);
    draw_command(x0<<16 | y0);
    draw_command(1280<<16 | 1024);
}

void draw_set_color(unsigned int a, unsigned int r, unsigned int g, unsigned int b) {
    draw_command(0x23000000);
    draw_command(a<<24 | r<<16 | g<<8 | b);
}

void draw_box(int x0, int y0, unsigned int width, unsigned int height) {
    draw_command(0x81000000);
    draw_command(x0<<16 | y0);
    draw_command(width<<16 | height);
}
