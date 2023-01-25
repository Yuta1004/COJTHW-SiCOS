#include <uart.h>
#include <syscall.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("USAGE: count <FILE_NAME>");
        return 1;
    }

    FS_Entry *fp = SYSCALL_F_GET(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }

    int c_num = 0;
    int l_num = 0;
    for (int idx = 0; idx < fp->size; ++ idx) {
        ++ c_num;
        if (fp->body[idx] == '\n') ++ l_num;
    }

    uart_prints("Characters : ");
    uart_printhln(c_num);
    uart_prints("Lines : ");
    uart_printhln(l_num);

    return 0;
}
