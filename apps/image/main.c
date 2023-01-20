#include <uart.h>
#include <syscall.h>
#include <string.h>
#include <draw.h>
#include <uart.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        uart_printsln("USAGE: image <FILE_NAME> <WIDTH> <HEIGHT> <FMT>");
        uart_printsln("    - FMT : 0 -> ARGB8888, 1 -> RGB888");
        return 1;
    }
    int width = (int)strtol(argv[2], 0, 10);
    int height = (int)strtol(argv[3], 0, 10);
    int fmt = (int)strtol(argv[4], 0, 10);

    FS_Entry *fp = SYSCALL_F_GET(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }

    int x = 0, y = 0;
    while (1) {
        DRAW_FRAME({
            draw_set_color(0, 0, 0, 0);
            draw_box(0, 0, 1280, 1024);

            draw_set_texture(fmt, (unsigned int)fp->body);
            draw_tbox(x, y, width, height, 0, 0);
        });

        char key = uart_inputc(0);
        if (key == 'k') y -= 5;
        if (key == 'j') y += 5;
        if (key == 'h') x -= 5;
        if (key == 'l') x += 5;
        if (key == 'q') break;
    }

    return 0;
}
