#include <syscall.h>
#include <uart.h>

#include "window.h"

Window *get_top_window(Window *w_list) {
    Window *wp = w_list;
    for (; wp->next_p != 0; wp = wp->next_p);
    return wp;
}

Window *get_clicked_window(Window *w_list, int x, int y) {
    for (Window *wp = get_top_window(w_list); wp != 0; wp = wp->bef_p) {
        int x0 = wp->x0, y0 = wp->y0;
        int x1 = x0 + wp->width, y1 = y0 + wp->height;
        if (x0 <= x && x <= x1 && y0 <= y && y <= y1) {
            return wp;
        }
    }
    return 0;
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

void window_new(
    Window *w_list,
    int x0,
    int y0,
    int width,
    int height,
    void (*draw_callback)(Window*, int, int),
    void *statp
) {
    Window *top_window = get_top_window(w_list);
    Window *wp = SYSCALL_M_ALLOC(sizeof(Window));
    wp->x0 = x0;
    wp->y0 = y0;
    wp->width = width;
    wp->height = height;
    wp->draw_callback = draw_callback;
    wp->statp = statp;
    wp->layer = top_window->layer+1;
    wp->bef_p = top_window;
    wp->next_p = 0;
    top_window->next_p = wp;
}

void window_liftup(Window *w_list, Window *target) {
    if (target->next_p != 0) {
        Window *top_window = get_top_window(w_list);
        target->bef_p->next_p = target->next_p;
        target->next_p->bef_p = target->bef_p;
        top_window->next_p = target;
        target->bef_p = top_window;
        target->next_p = 0;
    }
}

void window_remove(Window *w_list, Window *target) {
    Window *top_window = get_top_window(w_list);
    target->bef_p->next_p = target->next_p;
    if (target->next_p != 0) {
        target->next_p->bef_p = target->bef_p;
    }

    if (target->statp != 0) {
        SYSCALL_M_FREE(target->statp);
    }
    SYSCALL_M_FREE(target);
}

void window_free(Window *w_list) {
    for (Window *wp = get_top_window(w_list); wp != 0;) {
        Window *tmpp = wp->bef_p;
        if (wp->statp != 0) {
            SYSCALL_M_FREE(wp->statp);
        }
        SYSCALL_M_FREE(wp);
        wp = tmpp;
    }
}
