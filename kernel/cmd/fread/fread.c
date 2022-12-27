#include "fread.h"
#include "../../fs.h"
#include "../../lib/uart.h"

int cmd_fread(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: fread <FILE_NAME>");
        return 1;
    }

    FS_Entry *fp = f_get(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }

    for (int idx = 0; idx < fp->size; ++ idx) {
        uart_printc(fp->body[idx]);
    }

    return 0;
}
