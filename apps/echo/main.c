#include <uart.h>

int main(int argc, char **argv) {
    for (int idx = 1; idx < argc; ++ idx) {
        uart_prints(argv[idx]);
        if (idx < argc-1) {
            uart_printc(' ');
        }
    }
    uart_printsln("");
    return 0;
}
