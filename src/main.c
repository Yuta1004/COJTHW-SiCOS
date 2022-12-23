#include "calc/muldiv.h"
#include "dev/uart.h"
#include "dev/display.h"
#include "dev/camera.h"
#include "dev/draw.h"
#include "dev/cojt/gpio.h"
#include "dev/cojt/dvi.h"
#include "dev/cojt/ov9655.h"
#include "dev/cojt/xclk.h"

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
    while (1) {
        // プロンプト
        uart_prints("> ");

        // ユーザ入力待機
        char *cmd = uart_inputs();

        uart_prints("Exec => \"");
        uart_prints(cmd);
        uart_printsln("\"\n");
    }
}
