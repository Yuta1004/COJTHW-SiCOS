#include <draw.h>

#include "../window.h"
#include "capture.h"

void capapp_draw(Window *wp, int x0, int y0) {
    draw_set_texture(ARGB8888, 0x23000000);
    draw_tbox(x0, y0, 320, 240, 0, 0);
}

void capapp_new(Window *w_list) {
    window_new(w_list, 0, 0, 320, 240, capapp_draw, 0);
}
