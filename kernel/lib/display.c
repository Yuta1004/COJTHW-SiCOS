#include "display.h"

void display_on() {
    DISPCTRL = DISPON;
    DISPADDR = 0x24000000;
}

void display_off() {
    DISPCTRL = DISPOFF;
}
