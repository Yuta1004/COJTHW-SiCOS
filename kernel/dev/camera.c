#include "camera.h"

void camera_on(unsigned int addr) {
    CAMCTRL = CAMON;
    CAMADDR = addr;
}

void camera_off() {
    CAMCTRL = CAMOFF;
}
