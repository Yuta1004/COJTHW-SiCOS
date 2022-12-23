#include "dvi.h"
#include "xclk.h"

#define CDCE925_BYTE_RW 0x80

void init_xclk(unsigned char *XCLK) {
    iic_switch(IIC_SEL_DVI);
    for (int i = 0; i < 48; ++ i) {
        iic_write(0xC8, CDCE925_BYTE_RW | i, XCLK[i]);
    }
}
