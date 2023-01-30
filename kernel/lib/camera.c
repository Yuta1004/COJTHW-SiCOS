#include "camera.h"

void camera_on(unsigned int addr) {
    CAMCTRL = CAMON;
}

void camera_off() {
    CAMCTRL = CAMOFF;
}

void camera_addr(unsigned int addr) {
    CAMADDR = addr;
}
