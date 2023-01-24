#include "display.h"

void display_on() {
    DISPCTRL = DISPON;
}

void display_off() {
    DISPCTRL = DISPOFF;
}

void display_addr(unsigned int addr) {
    DISPADDR = addr;
}

void wait_vblank() {
    DISPCTRL |= 0b10;
    while((DISPCTRL & 0b10) == 0);
}
