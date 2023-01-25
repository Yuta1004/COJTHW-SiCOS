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

void uart_printh(int d) {
    char buf[32];

    char *p = buf + 30;
    buf[31] = '\0';

    do {
        char mod16 = d & 0xf;
        *(p--) = mod16 < 10 ? ('0' + mod16) : ('A' + (mod16-10));
        d >>= 4;
    } while (d > 0);

    uart_prints("0x");
    uart_prints(p + 1);
}

void uart_printhln(int d) {
    uart_printh(d);
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

char uart_inputc(int settings) {
    if (settings & UART_HOLD) {
        while ((UARTSTAT & 0x01) == 0);
    } else if ((UARTSTAT & 0x01) == 0) {
        return 0;
    }

    char ic = (char)(UARTRX & 0xff);
    if (settings & UART_ECHO) {
        uart_printc(ic);
    }

    return ic;
}

char *uart_inputs(int settings) {
    static char buf[256];

    for (char *p = buf; ; ++ p) {
        char ic = uart_inputc(settings | UART_HOLD);
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
