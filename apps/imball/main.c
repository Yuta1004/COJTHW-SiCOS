#include <uart.h>
#include <string.h>
#include <display.h>
#include <draw.h>
#include <syscall.h>

#define min(a, b) (a > b ? b : a)
#define max(a, b) (a > b ? a : b)

int main(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: imball <FILE_NAME>");
        return 1;
    }

    FS_Entry *fp = SYSCALL_F_GET(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }
    int width = *((int*)(fp->body));
    int height = *((int*)(fp->body+4));

    uart_printsln("press any key...");

    DRAW_FRAME({
        draw_set_stmode(0);

        draw_set_color(0, 0, 255, 0);
        draw_box(0, 0, 1280, 1024);

        draw_set_color(0, 255, 255, 128);
        draw_box(50, 50, 1180, 924);
    });

    DRAW_FRAME({
        draw_set_stmode(0);

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
            draw_set_stmode(0);
            draw_set_color(0, 255, 255, 128);
            draw_box(ox2, oy2, width, height);

            draw_set_stmode(1);
            draw_set_scolor(ALPHA,
                            0, 0, 0, 0,
                            0, 0, 0, 0);
            draw_set_texture(0, (unsigned int)(fp->body+8));
            draw_tbox(px, py, width, height, 0, 0);
        });

        ox2 = ox1; oy2 = oy1;
        ox1 = px; oy1 = py;
        px += vx; py += vy;
        if (px < 50 || px > 1280-50-width) {
            vx *= -1;
            px = max(50, min(px, 1280-50-width));
        }
        if (py < 50 || py > 1024-50-height) {
            vy *= -1;
            py = max(50, min(py, 1024-50-height));
        }

        if (uart_inputc(0) != 0) {
            break;
        }
    }

    return 0;
}
