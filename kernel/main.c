#include "fs.h"
#include "mem.h"
#include "lib/muldiv.h"
#include "lib/string.h"
#include "lib/uart.h"
#include "lib/display.h"
#include "lib/camera.h"
#include "lib/mouse.h"
#include "lib/draw.h"
#include "dev/gpio.h"
#include "dev/dvi.h"
#include "dev/ov9655.h"
#include "dev/xclk.h"
#include "cmd/osinfo/osinfo.h"
#include "cmd/help/help.h"
#include "cmd/fcreate/fcreate.h"
#include "cmd/flist/flist.h"
#include "cmd/fremove/fremove.h"
#include "cmd/fread/fread.h"
#include "cmd/exec/exec.h"

typedef struct {
    char *name;
    int (*fp)(int, char**);
} cmd_info;

cmd_info cmd_info_list[] = {
    {"osinfo", cmd_osinfo},
    {"help", cmd_help},
    {"fcreate", cmd_fcreate},
    {"flist", cmd_flist},
    {"fremove", cmd_fremove},
    {"fread", cmd_fread},
    {"exec", cmd_exec}
};

int main() {
    // 回路初期化
    set_resolution(SXGA);
    uart_init();

    // 起動メッセージ
    cmd_osinfo(0, 0);
    uart_printsln("");

    // 周辺機器初期設定
    uart_prints("< STARTUP > Setting Devices ... ");
    init_tpf410();
    init_xclk(XCLK24MHz);
    init_ov9655(OV9655_SXGA);
    uart_printsln("OK");

    // VRAM初期化
    uart_prints("< STARTUP > Initializing VRAM ... ");
    DRAW_FRAME({
        draw_set_color(0, 0, 0, 0);
        draw_box(0, 0, 1280, 1024);
    });
    display_on();
    uart_printsln("OK");

    // ファイルシステム初期化
    uart_prints("< STARTUP > Initializing File System ... ");
    fs_init();
    uart_printsln("OK");

    // メモリアロケータ初期化
    uart_prints("< STARTUP > Initializing Memory Allocator ... ");
    mem_alloc_table_init();
    uart_printsln("OK");

    uart_printsln("");

    // シェル
    unsigned char stat = 0;
    while (1) {
loop_top:
        // プロンプト
        uart_printc('[');
        uart_printd(stat);
        uart_printc(']');
        uart_prints(" $ ");

        // ユーザ入力待機
        char *cmd = uart_inputs(UART_ECHO);

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
