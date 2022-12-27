#include <uart.h>

int main(int argc, char **argv) {
    uart_prints("argc : ");
    uart_printd(argc);

    uart_prints("\nargv : ");
    for (char **arg = argv; *arg != 0; ++ arg) {
        uart_prints(*arg);
        uart_prints(", ");
    }
    uart_printsln("");

    return argc;
}
