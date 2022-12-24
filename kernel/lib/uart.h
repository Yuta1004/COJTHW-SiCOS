#ifndef UART_H
#define UART_H

#define UART_BASEADDR   0x50050000
#define UARTRX          (*((volatile unsigned int*)(UART_BASEADDR + 0x0)))
#define UARTTX          (*((volatile unsigned int*)(UART_BASEADDR + 0x4)))
#define UARTSTAT        (*((volatile unsigned int*)(UART_BASEADDR + 0x8)))
#define UARTCTRL        (*((volatile unsigned int*)(UART_BASEADDR + 0xC)))

#define OK_STAT     4

void uart_init();
void uart_printd(int d);
void uart_printdln(int d);
void uart_printc(char c);
void uart_prints(char *s);
void uart_printsln(char *s);
char uart_inputc();
char *uart_inputs();

#endif
