#include "help.h"
#include "../../lib/uart.h"

int cmd_help(int argc, char **argv) {
    uart_printsln("- osinfo  : Show SiCOS information");
    uart_printsln("- help    : Show default commands");
    uart_printsln("- exec    : Execute a application (.app)");
    uart_printsln("- fcreate : Create a file");
    uart_printsln("- fremove : Remove a file");
    uart_printsln("- fread   : Show file contents");
    uart_printsln("- flist   : Show file list");
    return 0;
}
