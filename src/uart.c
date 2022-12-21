#include "uart.h"
#include "muldiv.h"

void dev_wait() {
    while(STAT_REG != OK_STAT);
}

void dev_write(char c) {
    dev_wait();
    Tx_FIFO = c;
}

void uart_init() {
    CTRL_REG = 0b00011;
}

void uart_printd(int d) {
    char buf[32];

    char *p = buf + 30;
    buf[31] = '\0';

    do {
        *(p--) = '0' + mod(d, 10);
        d = div(d, 10);
    } while (d > 0);

    uart_prints(p + 1);
}

void uart_printdln(int d) {
    uart_printd(d);
    uart_printsln("");
}

void uart_printc(char c) {
    dev_write(c);
}

void uart_prints(char *s) {
    for (char *c = s; *c != '\0'; ++ c) {
        dev_write(*c);
    }
}

void uart_printsln(char *s) {
    for (char *c = s; *c != '\0'; ++ c) {
        dev_write(*c);
    }
    dev_write(0x0d);
    dev_write(0x0a);
}
