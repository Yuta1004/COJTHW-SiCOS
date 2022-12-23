#include "display.h"

void display_on(unsigned int addr) {
    DISPCTRL = DISPON;
    DISPADDR = addr;
}

void display_off() {
    DISPCTRL = DISPOFF;
}
