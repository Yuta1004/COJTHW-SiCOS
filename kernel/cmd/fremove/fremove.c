#include "fremove.h"
#include "../../fs.h"
#include "../../lib/uart.h"

int cmd_fremove(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: fremove <FILE_NAME>");
        return 1;
    }

    f_remove(argv[1]);

    return 0;
}
