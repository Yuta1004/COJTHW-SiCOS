#ifndef M_APPS_BALL_H
#define M_APPS_BALL_H

#include "../window.h"

typedef struct {
    int x, y;
    int vx, vy;
} BallStat;

void ballapp_new(Window *w_list);

#endif
