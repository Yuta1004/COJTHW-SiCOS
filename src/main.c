#include "calc/muldiv.h"
#include "dev/uart.h"
#include "dev/display.h"
#include "dev/camera.h"
#include "dev/draw.h"
#include "dev/cojt/gpio.h"
#include "dev/cojt/dvi.h"
#include "dev/cojt/ov9655.h"
#include "dev/cojt/xclk.h"

int main() {
    /* 周辺機器初期設定 */
    init_tpf410();
    init_xclk(XCLK24MHz);
    init_ov9655(OV9655_SXGA);

    /* 回路初期化 */
    set_resolution(SXGA);
    uart_init();

    display_on(0x3fa00000);

    draw_set_frame(0x3fa00000, 1280, 1024);
    draw_set_drawarea(0, 0, 1280, 1024);

    draw_set_color(0, 0, 255, 0);
    draw_box(0, 0, 1280, 1024);

    int ox = 0; int oy = 0;
    int px = 0; int py = 0;
    int vx = 5; int vy = 5;
    while (1) {
        draw_set_frame(0x3fa00000, 1280, 1024);
        draw_set_drawarea(0, 0, 1280, 1024);

        draw_set_color(0, 0, 255, 0);
        draw_box(ox, oy, 100, 100);

        draw_set_color(0, 255, 0, 0);
        draw_box(px, py, 100, 100);

        draw_exec();

        ox = px; oy = py;
        px += vx; py += vy;
        if (px < 0 || px > 1280-100) {
            vx *= -1;
        }
        if (py < 0 || py > 1024-100) {
            vy *= -1;
        }

        for (volatile int cnt = 0; cnt < 5000; ++ cnt);
    }
}
