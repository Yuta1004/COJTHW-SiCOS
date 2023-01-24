#include <uart.h>
#include <syscall.h>
#include <string.h>
#include <draw.h>
#include <uart.h>

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
            draw_set_color(0, 0, 0, 0);
            draw_box(0, 0, 1280, 1024);

            draw_set_texture(0, (unsigned int)(fp->body+8));
            draw_tbox(x, y, width, height, 0, 0);
        });

        char key = uart_inputc(UART_HOLD);
        if (key == 'k') y -= 5;
        if (key == 'j') y += 5;
        if (key == 'h') x -= 5;
        if (key == 'l') x += 5;
        if (key == 'q') break;
    }

    return 0;
}
