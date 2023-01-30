#include <syscall.h>
#include <draw.h>

#include "../window.h"
#include "ball.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

void ballapp_draw(Window *wp, int x0, int y0) {
    BallStat *bstat = (BallStat*)(wp->statp);
    bstat->x += bstat->vx;
    bstat->y += bstat->vy;
    if (bstat->x < 0 || bstat->x > 400-50) {
        bstat->x = max(0, min(bstat->x, 400-50));
        bstat->vx *= -1;
    }
    if (bstat->y < 0 || bstat->y > 300-50) {
        bstat->y = max(0, min(bstat->y, 300-50));
        bstat->vy *= -1;
    }

    draw_set_color(0, 255, 0, 255);
    draw_box(x0+bstat->x, y0+bstat->y, 50, 50);
}

void ballapp_new(Window *w_list) {
    BallStat *bstat = (BallStat*)SYSCALL_M_ALLOC(sizeof(BallStat));
    bstat->x = 0;
    bstat->y = 0;
    bstat->vx = 5;
    bstat->vy = 5;

    window_new(w_list, 0, 0, 400, 300, ballapp_draw, bstat);
}
