#include <uart.h>
#include <syscall.h>
#include <string.h>
#include <draw.h>
#include <uart.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: image <FILE_NAME>");
        return 1;
    }

    FS_Entry *fp = SYSCALL_F_GET(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }

    int width = *((int*)(fp->body));
    int height = *((int*)(fp->body+4));
    int x = (1280-width) >> 1;
    int y = height > 1024 ? 0 : (1024-height) >> 1;

    while (1) {
        DRAW_FRAME({
            draw_set_stmode(0);

            draw_set_color(0, 0, 0, 0);
            draw_box(0, 0, 1280, 1024);

            draw_set_texture(0, (unsigned int)(fp->body+8));
            draw_tbox(x, y, width, height, 0, 0);
        });

        char key = uart_inputc(UART_HOLD);
        if (key == 'k') y = max(0, min(y-5, 1024-height));
        if (key == 'j') y = max(0, min(y+5, 1024-height));
        if (key == 'h') x = max(0, min(x-5, 1280-width));
        if (key == 'l') x = max(0, min(x+5, 1280-width));
        if (key == 'q') break;
    }

    return 0;
}
