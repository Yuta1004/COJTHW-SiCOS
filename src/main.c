#include "std/muldiv.h"
#include "dev/uart.h"
#include "dev/cojt/gpio.h"
#include "dev/cojt/dvi.h"
#include "dev/cojt/ov9655.h"
#include "dev/cojt/xclk.h"
#include "dev/display.h"
#include "dev/camera.h"

int fib(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    init_tpf410();
    init_xclk(XCLK24MHz);
    init_ov9655(OV9655_SXGA);
    RESOL_CTRL = 0;
    RESOL_SET = SXGA;

    DISPCTRL = DISPON;
    DISPADDR = 0x3fa00000;

    CAMCTRL = CAMON;
    CAMADDR = 0x3fa00000;

    uart_init();

    uart_printsln("Hello, I'm COJT-original RISC-V(RV32I) core!");

    for (int n = 1; n <= 15; ++ n) {
        uart_prints("fib(");
        uart_printd(n);
        uart_prints(") = ");
        uart_printdln(fib(n));
    }
}
