#include <draw.h>

#include "../window.h"
#include "cbox.h"

void cboxapp_draw(Window *wp, int x0, int y0) {
    draw_set_brendmode(1);

    draw_set_color(128, 255, 0, 0);
    draw_box(x0+20, y0+20, 150, 150);

    draw_set_color(128, 0, 255, 0);
    draw_box(x0+130, y0+70, 150, 150);

    draw_set_color(128, 0, 0, 255);
    draw_box(x0+80, y0+130, 150, 150);

    draw_set_brendmode(0);
}

void cboxapp_new(Window *w_list) {
    window_new(w_list, 0, 0, 300, 300, cboxapp_draw, 0);
}
