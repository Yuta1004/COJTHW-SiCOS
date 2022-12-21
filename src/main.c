#include "uart.h"
#include "muldiv.h"

int fib(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    uart_init();

    uart_printsln("Hello, I'm COJT-original RISC-V(RV32I) core!");

    for (int n = 1; n <= 15; ++ n) {
        uart_prints("fib(");
        uart_printd(n);
        uart_prints(") = ");
        uart_printdln(fib(n));
    }
}
