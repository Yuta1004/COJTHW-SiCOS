#include <syscall.h>
#include <draw.h>
#include <uart.h>

#include "../window.h"
#include "image.h"

void imgapp_draw(Window *wp, int x0, int y0) {
    draw_set_texture(ARGB8888, (unsigned int)(wp->statp));
    draw_tbox(x0, y0, wp->width, wp->height, 0, 0);
}

void imgapp_new(Window *w_list, char *fname) {
    FS_Entry *fp = SYSCALL_F_GET(fname);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return;
    }
    int width = *((int*)(fp->body));
    int height = *((int*)(fp->body+4));

    window_new(w_list, 0, 0, width, height, imgapp_draw, (void*)(fp->body));
}
