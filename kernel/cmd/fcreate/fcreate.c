#include "fcreate.h"
#include "../../fs.h"
#include "../../lib/uart.h"
#include "../../lib/string.h"

int cmd_fcreate(int argc, char **argv) {
    if (argc < 4) {
        uart_printsln("USAGE: fcreate <FILE_NAME> <PERMISSION> <SIZE>");
    }

    unsigned char permission = (unsigned char)strtol(argv[2], 0, 0);
    unsigned int size = (unsigned int)strtol(argv[3], 0, 0);

    if (f_create(argv[1], permission, size) != 0) {
        uart_printsln("Error!");
    }
}
