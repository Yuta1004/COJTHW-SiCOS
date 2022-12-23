#include "gpio.h"

void set_resolution(int resol) {
    RESOL_CTRL = 0;
    RESOL_SET = resol;
}
