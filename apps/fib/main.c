#include <uart.h>
#include <string.h>

int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n-1) + fib(n-2);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("Usage: fib <N>");
        return 1;
    }

    int n = (int)strtol(argv[1], 0, 0);
    int result = fib(n);

    uart_prints("fib(");
    uart_printh(n);
    uart_prints(") = ");
    uart_printhln(result);

    return 0;
}
