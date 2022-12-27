#include "exec.h"
#include "../../fs.h"
#include "../../lib/uart.h"

int cmd_exec(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: exec <APP>");
        return 1;
    }

    FS_Entry *fp = f_get(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }

    int (*app)(int, char**) = (int (*)(int, char**))(fp->body);
    return app(argc-1, argv+1);
}
