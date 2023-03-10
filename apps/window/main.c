#include <syscall.h>
#include <uart.h>
#include <mouse.h>
#include <draw.h>
#include <string.h>

#include "window.h"
#include "apps/box.h"
#include "apps/cbox.h"
#include "apps/capture.h"
#include "apps/ball.h"
#include "apps/image.h"

#define queue3_push(queue, x) {\
    (queue)[2] = (queue)[1];\
    (queue)[1] = (queue)[0];\
    (queue)[0] = (x);\
}

void draw_background() {
    draw_set_color(0, 0, 136, 136);
    draw_box(0, 0, 1280, 1024);
}

void draw_mouse(int x[3], int y[3], int z[3], int btn[3]) {
    int color[3] = {
        MOUSE_CLICKED(btn[0], MOUSE_LBTN) ? 255 : 0,
        MOUSE_CLICKED(btn[0], MOUSE_CBTN) ? 255 : 0,
        MOUSE_CLICKED(btn[0], MOUSE_RBTN) ? 255 : 0
    };

    draw_set_color(0, color[0], color[1], color[2]);
    draw_box(x[0], y[0], 10, 10);
}

void draw_window(Window *w_list, int m_xpos[3], int m_ypos[3], int m_zpos[3], int m_btn[3]) {
    // クリック判定
    if (MOUSE_CLICKED(m_btn[0], MOUSE_LBTN)) {
        Window *wp = get_clicked_window(w_list, m_xpos[0], m_ypos[0]);
        if (wp != 0) {
            window_liftup(w_list, wp);
            if (wp != 0 && MOUSE_CLICKED(m_btn[1], MOUSE_LBTN)) {
                int dx = m_xpos[0] - m_xpos[1];
                int dy = m_ypos[0] - m_ypos[1];
                wp->x0 += dx;
                wp->y0 += dy;
            }
        }
    }
    else if (MOUSE_CLICKED(m_btn[0], MOUSE_RBTN)) {
        Window *wp = get_clicked_window(w_list, m_xpos[0], m_ypos[0]);
        window_remove(w_list, wp);
    }

    // 描画処理
    for (Window *wp = w_list->next_p; wp != 0; wp = wp->next_p) {
        // 影
        draw_set_color(0, 0, 0, 0);
        draw_box(wp->x0, wp->y0, wp->width+10, wp->height+60);

        // 枠
        draw_set_color(0, 128, 128, 128);
        draw_box(wp->x0, wp->y0, wp->width+8, wp->height+58);

        // ヘッダー
        draw_set_color(0, 0, 0, 150);
        draw_box(wp->x0+4, wp->y0+4, wp->width, 46);

        // ボタンもどきの影
        draw_set_color(0, 0, 0, 0);
        draw_box(wp->x0+wp->width-40, wp->y0+8, 40, 40);

        // ボタンもどき
        draw_set_color(0, 128, 128, 128);
        draw_box(wp->x0+wp->width-40, wp->y0+8, 38, 38);

        // 本体
        draw_set_color(0, 255, 255, 255);
        draw_box(wp->x0+4, wp->y0+54, wp->width, wp->height);
        wp->draw_callback(wp, wp->x0+4, wp->y0+54);
    }
}

void draw(Window *w_list, int m_xpos[3], int m_ypos[3], int m_zpos[3], int m_btn[3]) {
    DRAW_FRAME({
        draw_set_stmode(0);
        draw_background();
        draw_window(w_list, m_xpos, m_ypos, m_zpos, m_btn);
        draw_mouse(m_xpos, m_ypos, m_zpos, m_btn);
    });
}

int main(int argc, char **argv) {
    // ウィンドウ関連変数
    Window *w_list = window_root();

    // マウス関連変数
    int tmp_m_xpos, tmp_m_ypos, tmp_m_zpos, tmp_m_btn;
    int m_xpos[3] = {0, 0, 0};
    int m_ypos[3] = {0, 0, 0};
    int m_zpos[3] = {0, 0, 0};
    int m_btn[3]  = {0, 0, 0};

    // 初期化処理
    mouse_init(MOUSE_SXGA, MOUSE_SPEED_1);
    DRAW_FRAME(draw_background());
    DRAW_FRAME(draw_background());

    uart_printsln("press any key...");

    while (1) {
        // マウスイベント
        if (mouse_read(&tmp_m_xpos, &tmp_m_ypos, &tmp_m_zpos, &tmp_m_btn)) {
            queue3_push(m_xpos, tmp_m_xpos);
            queue3_push(m_ypos, tmp_m_ypos);
            queue3_push(m_zpos, tmp_m_zpos);
            queue3_push(m_btn, tmp_m_btn);
        }

        // 描画
        if (1) {
            draw(w_list, m_xpos, m_ypos, m_zpos, m_btn);
        }

        // コマンド入力
        if (uart_inputc(0) != 0) {
            // プロンプト
            uart_prints(">> ");

            // ユーザ入力待機
            char *cmd = uart_inputs(UART_ECHO);

            // 引数分解
            int sargc = 0;
            char *sargv[16];
            char **ap = sargv;
            for (char *p = cmd; *p != '\0'; ) {
                while (*p == ' ') ++ p;

                sargc ++;
                *(ap++) = p;
                while (*p != ' ' && *p != '\0') ++ p;

                if (*p == '\0') break;
                *(p++) = '\0';
            }
            *ap = 0;

            // コマンド実行
            if (strcmp(sargv[0], "box") == 0) {
                boxapp_new(w_list);
            }
            else if (strcmp(sargv[0], "cbox") == 0) {
                cboxapp_new(w_list);
            }
            else if (strcmp(sargv[0], "ball") == 0) {
                ballapp_new(w_list);
            }
            else if (strcmp(sargv[0], "cap") == 0) {
                capapp_new(w_list);
            }
            else if (strcmp(sargv[0], "image") == 0) {
                if (sargc < 2) {
                    uart_printsln("USAGE: image <FILE_NAME>");
                } else {
                    imgapp_new(w_list, sargv[1]);
                }
            }
            else if (strcmp(sargv[0], "exit") == 0) {
                goto __exit;
            }
            else {
                uart_printc('\"');
                uart_prints(sargv[0]);
                uart_printsln("\" not found...");
            }
        }
    }

__exit:
    window_free(w_list);

    return 0;
}
