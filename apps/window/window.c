#include <syscall.h>
#include <uart.h>

#include "window.h"

Window *get_top_window(Window *w_list) {
    Window *wp = w_list;
    for (; wp->next_p != 0; wp = wp->next_p);
    return wp;
}

Window *window_root() {
    Window *wp = SYSCALL_M_ALLOC(sizeof(Window));
    wp->x0 = 0;
    wp->y0 = 0;
    wp->width = 0;
    wp->height = 0;
    wp->layer = 0;
    wp->bef_p = 0;
    wp->next_p = 0;
    return wp;
}

void window_new(Window *w_list, int x0, int y0, int width, int height) {
    Window *top_window = get_top_window(w_list);
    Window *wp = SYSCALL_M_ALLOC(sizeof(Window));
    wp->x0 = x0;
    wp->y0 = y0;
    wp->width = width;
    wp->height = height;
    wp->layer = top_window->layer+1;
    wp->bef_p = top_window;
    wp->next_p = 0;
    top_window->next_p = wp;
}
