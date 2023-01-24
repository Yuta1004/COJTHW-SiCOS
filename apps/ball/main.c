#include <uart.h>
#include <string.h>
#include <display.h>
#include <draw.h>

#define min(a, b) (a > b ? b : a)
#define max(a, b) (a > b ? a : b)

int main(int argc, char **argv) {
    uart_printsln("press any key...");

    DRAW_FRAME({
        draw_set_color(0, 0, 255, 0);
        draw_box(0, 0, 1280, 1024);

        draw_set_color(0, 255, 255, 128);
        draw_box(50, 50, 1180, 924);
    });

    DRAW_FRAME({
        draw_set_color(0, 0, 255, 0);
        draw_box(0, 0, 1280, 1024);

        draw_set_color(0, 255, 255, 128);
        draw_box(50, 50, 1180, 924);
    });

    int ox1 = 50, oy1 = 50;
    int ox2 = 50, oy2 = 50;
    int px  = 50, py  = 50;
    int vx  = 5,  vy  = 5;
    while(1) {
        DRAW_FRAME({
            draw_set_color(0, 255, 255, 128);
            draw_box(ox1, oy1, 100, 100);

            draw_set_color(0, 255, 255, 128);
            draw_box(ox2, oy2, 100, 100);

            draw_set_color(0, 255, 0, 0);
            draw_box(px, py, 100, 100);
        });

        ox2 = ox1; oy2 = oy1;
        ox1 = px; oy1 = py;
        px += vx; py += vy;
        if (px < 50 || px > 1280-100-50) {
            vx *= -1;
            px = max(50, min(px, 1280-100-50));
        }
        if (py < 50 || py > 1024-100-50) {
            vy *= -1;
            py = max(50, min(py, 1024-100-50));
        }

        if (uart_inputc(0) != 0) {
            break;
        }
    }

    return 0;
}
