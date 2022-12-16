#ifndef UART_H
#define UART_H

#define Rx_FIFO     (*((volatile unsigned int*)0x80010000))
#define Tx_FIFO     (*((volatile unsigned int*)0x80010004))
#define STAT_REG    (*((volatile unsigned int*)0x80010008))
#define CTRL_REG    (*((volatile unsigned int*)0x8001000C))

#define OK_STAT     4

void uart_init();
void uart_printc(char c);
void uart_prints(char *s);
void uart_printsln(char *s);

#endif
