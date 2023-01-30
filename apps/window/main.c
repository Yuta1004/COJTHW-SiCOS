#include <uart.h>
#include <mouse.h>
#include <draw.h>

#include "window.h"

#define queue3_push(queue, x) {\
    (queue)[2] = (queue)[1];\
    (queue)[1] = (queue)[0];\
    (queue)[0] = (x);\
}

void draw_background() {
    DRAW_FRAME({
        draw_set_stmode(0);
        draw_set_color(0, 128, 128, 128);
        draw_box(0, 0, 1280, 1024);
    });

    DRAW_FRAME({
        draw_set_stmode(0);
        draw_set_color(0, 128, 128, 128);
        draw_box(0, 0, 1280, 1024);
    });
}

void draw_mouse(int x[3], int y[3], int z[3], int btn) {
    int color[3] = {
        MOUSE_CLICKED(btn, MOUSE_LBTN) ? 255 : 0,
        MOUSE_CLICKED(btn, MOUSE_CBTN) ? 255 : 0,
        MOUSE_CLICKED(btn, MOUSE_RBTN) ? 255 : 0
    };

    draw_set_stmode(0);

    draw_set_color(0, 128, 128, 128);
    draw_box(x[2], y[2], 10, 10);

    draw_set_color(0, color[0], color[1], color[2]);
    draw_box(x[0], y[0], 10, 10);
}

void draw_window(Window *w_list) {
    for (Window *wp = w_list->next_p; wp != 0; wp = wp->next_p) {
        draw_set_color(0, 200, 100, 100);
        draw_box(wp->x0, wp->y0, wp->width, wp->height);
    }
}

void draw(Window *w_list, int m_xpos[3], int m_ypos[3], int m_zpos[3], int m_btn) {
    DRAW_FRAME({
        draw_window(w_list);
        draw_mouse(m_xpos, m_ypos, m_zpos, m_btn);
    });
}

int main(int argc, char **argv) {
    // ウィンドウ関連変数
    Window *w_list = window_root();

    // マウス関連変数
    int tmp_m_xpos, tmp_m_ypos, tmp_m_zpos, m_btn;
    int m_xpos[3] = {0, 0, 0};
    int m_ypos[3] = {0, 0, 0};
    int m_zpos[3] = {0, 0, 0};

    // 初期化処理
    mouse_init(MOUSE_SXGA, MOUSE_SPEED_1);
    draw_background();

    while (1) {
        // マウスイベント
        if (mouse_read(&tmp_m_xpos, &tmp_m_ypos, &tmp_m_zpos, &m_btn)) {
            queue3_push(m_xpos, tmp_m_xpos);
            queue3_push(m_ypos, tmp_m_ypos);
            queue3_push(m_zpos, tmp_m_zpos);
            draw(w_list, m_xpos, m_ypos, m_zpos, m_btn);
        }

        // キー入力
        char key = uart_inputc(0);
        switch (key) {
            case 0:
                break;

            case 'w':
                window_new(w_list, 0, 0, 100, 100);
                break;

            default:
                goto __exit;
        }
    }

__exit:
    return 0;
}
