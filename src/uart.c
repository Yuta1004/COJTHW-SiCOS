#include "uart.h"

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
