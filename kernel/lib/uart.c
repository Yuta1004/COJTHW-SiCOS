#include "uart.h"
#include "muldiv.h"

void dev_wait() {
    while(UARTSTAT != OK_STAT);
}

void dev_write(char c) {
    dev_wait();
    UARTTX = c;
}

void uart_init() {
    UARTCTRL = 0b00011;
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

char uart_inputc() {
    while ((UARTSTAT & 0x01) == 0);

    char ic = (char)(UARTRX & 0xff);
    uart_printc(ic);

    return ic;
}

char *uart_inputs() {
    static char buf[256];

    for (char *p = buf; ; ++ p) {
        char ic = uart_inputc();
        if (ic == '\n') {           // 改行文字
            *p = '\0';
            break;
        } else if (ic == '\b') {    // バックスペース
            if (p == buf) p -= 1;
            if (p > buf)  p -= 2;
        } else {
            *p = ic;
        }
    }

    return buf;
}
