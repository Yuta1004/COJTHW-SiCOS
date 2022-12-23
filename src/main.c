#include "calc/muldiv.h"
#include "calc/string.h"
#include "dev/uart.h"
#include "dev/display.h"
#include "dev/camera.h"
#include "dev/draw.h"
#include "dev/cojt/gpio.h"
#include "dev/cojt/dvi.h"
#include "dev/cojt/ov9655.h"
#include "dev/cojt/xclk.h"
#include "cmd/test/test.h"

typedef struct {
    char *name;
    int (*fp)(int, char**);
} cmd_info;

cmd_info cmd_info_list[] = {
    {"test", cmd_test}
};

int main() {
    // 周辺機器初期設定
    init_tpf410();
    init_xclk(XCLK24MHz);
    init_ov9655(OV9655_SXGA);

    // 回路初期化
    set_resolution(SXGA);
    uart_init();

    // 起動メッセージ
    uart_printsln("+--------------+");
    uart_printsln("| SiCOS v0.0.1 |");
    uart_printsln("+--------------+");
    uart_printsln("");

    // シェル
    unsigned char stat = 0;
    while (1) {
loop_top:
        // プロンプト
        uart_printc('[');
        uart_printd(stat);
        uart_printc(']');
        uart_prints("> ");

        // ユーザ入力待機
        char *cmd = uart_inputs();

        // 引数分解
        int argc = 0;
        char *argv[16];
        char **ap = argv;
        for (char *p = cmd; *p != '\0'; ) {
            while (*p == ' ') ++ p;

            argc ++;
            *(ap++) = p;
            while (*p != ' ' && *p != '\0') ++ p;

            if (*p == '\0') break;
            *(p++) = '\0';
        }
        *ap = 0;

        // コマンド実行
        for (int idx = 0; idx < sizeof(cmd_info_list)/sizeof(cmd_info); ++ idx) {
            char *name = cmd_info_list[idx].name;
            if (strcmp(argv[0], name) == 0) {
                stat = cmd_info_list[idx].fp(argc, argv);
                uart_printsln("");
                goto loop_top;
            }
        }

        stat = 255;
        uart_prints("Command \"");
        uart_prints(argv[0]);
        uart_printsln("\" is not found.\n");
    }
}
