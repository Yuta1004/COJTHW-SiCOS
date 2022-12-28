#include "osinfo.h"
#include "../../lib/uart.h"

int cmd_osinfo(int argc, char **argv) {
    uart_printsln("+-----------------------------------------+");
    uart_printsln("|   ####   #     #####    ####     ####   |");
    uart_printsln("|  #   ##       ##   #   ##   ##  #   ##  |");
    uart_printsln("|  #       #   ##       ##     #  #       |");
    uart_printsln("|  ###     #   #        #      ## ###     |");
    uart_printsln("|    ###   #   #        #      ##   ###   |");
    uart_printsln("|      ##  #   #        #      ##     ##  |");
    uart_printsln("|       #  #   ##       ##     #       #  |");
    uart_printsln("|  #   ##  #    ##   #   ##   ##  #   ##  |");
    uart_printsln("|   ####   #     ####     ####     ####   |");
    uart_printsln("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+");
    uart_printsln("|          SiCOS v0.0.1 (RV32I)           |");
    uart_printsln("|         (c) 2022 Yuta NAKAGAMI          |");
    uart_printsln("+-----------------------------------------+");
    return 0;
}
