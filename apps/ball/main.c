#include <uart.h>
#include <string.h>
#include <display.h>
#include <draw.h>

#define min(a, b) (a > b ? b : a)
#define max(a, b) (a > b ? a : b)

int main(int argc, char **argv) {
    int max_frame = 1000;
    if (argc > 1) {
        max_frame = (int)strtol(argv[1], 0, 0);
    }

    display_on();

    DRAW_FRAME({
        draw_set_color(0, 0, 255, 0);
        draw_box(0, 0, 1280, 1024);

        draw_set_color(0, 255, 255, 128);
        draw_box(50, 50, 1180, 924);
    });

    int ox = 50; int oy = 50;
    int px = 50; int py = 50;
    int vx = 5; int vy = 5;
    for (int frame = 0; frame < max_frame; ++ frame) {
        DRAW_FRAME({
            draw_set_color(0, 255, 255, 128);
            draw_box(ox, oy, 100, 100);

            draw_set_color(0, 255, 0, 0);
            draw_box(px, py, 100, 100);
        });

        ox = px; oy = py;
        px += vx; py += vy;
        if (px < 50 || px > 1280-100-50) {
            vx *= -1;
            px = max(50, min(px, 1280-100-50));
        }
        if (py < 50 || py > 1024-100-50) {
            vy *= -1;
            py = max(50, min(py, 1024-100-50));
        }

        for (volatile int cnt = 0; cnt < 5000; ++ cnt);
    }
    return 0;
}
