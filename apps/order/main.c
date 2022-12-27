#include <uart.h>

int main(int argc, char **argv) {
    if (argc == 1) {
        uart_printsln("Is the order a rabbit?");
    } else {
        uart_prints("Is the order a ");
        uart_prints(argv[1]);
        uart_printsln("?");
    }

    return 0;
}
