#include "fcreate.h"
#include "../../fs.h"
#include "../../lib/uart.h"

int cmd_fcreate(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: fcreate <FILE_NAME>");
    }

    int result = f_create(argv[1], 4000);
    if (result != 0) {
        uart_printsln("Error!");
    }
}
