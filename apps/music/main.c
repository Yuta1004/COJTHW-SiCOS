#include <uart.h>
#include <syscall.h>
#include <sound.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        uart_printsln("Usage: music <FILE>");
        return 1;
    }

    FS_Entry *fp = SYSCALL_F_GET(argv[1]);
    if (fp == 0) {
        uart_printsln("Can't open the file!");
        return 1;
    }

    sound_init((unsigned int)(fp->body+0x2c), fp->size);
    sound_ctrl(SPLAY | SLOOP);
    sound_vol(200);

    while (1) {
        // プロンプト
        uart_prints("(");
        uart_prints(argv[1]);
        uart_prints(") >> ");

        // ユーザ入力待機
        char *cmd = uart_inputs(UART_ECHO);

        // 引数分解
        int sargc = 0;
        char *sargv[16];
        char **ap = sargv;
        for (char *p = cmd; *p != '\0'; ) {
            while (*p == ' ') ++ p;

            sargc ++;
            *(ap++) = p;
            while (*p != ' ' && *p != '\0') ++ p;

            if (*p == '\0') break;
            *(p++) = '\0';
        }
        *ap = 0;

        // コマンド実行
        if (strcmp(sargv[0], "play") == 0) {
            sound_ctrl(SPLAY | SLOOP);
        }
        else if (strcmp(sargv[0], "pause") == 0) {
            sound_ctrl(SPAUSE | SLOOP);
        }
        else if (strcmp(sargv[0], "stop") == 0) {
            sound_ctrl(SSTOP | SLOOP);
        }
        else if (strcmp(sargv[0], "vol") == 0) {
            if (sargc == 1) {
                uart_printsln("error: vol <VOL>");
            } else {
                sound_vol((int)strtol(sargv[1], 0, 10));
            }
        }
        else if (strcmp(sargv[0], "exit") == 0) {
            sound_ctrl(SSTOP);
            break;
        }
        else {
            uart_printsln("error: command not found");
        }
    }

    return 0;
}
