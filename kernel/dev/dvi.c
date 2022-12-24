#include "dvi.h"

void init_iic(void) {
    IIC_CTRLREG = 0x02; // reset tx fifo
    IIC_CTRLREG = 0x01; // enable iic
}

void iic_write(unsigned int daddr, unsigned int waddr, unsigned int wdata) {
    IIC_TXREG = 0x100 | daddr;  // select
    IIC_TXREG = waddr;          // address
    IIC_TXREG = 0x200 | wdata;  // data
    while ((IIC_STATUSREG & (IIC_TX_FIFO_EMPTY | IIC_BUS_BUSY)) != IIC_TX_FIFO_EMPTY);
}

void iic_switch(int IICSEL){
    init_iic();
    IIC_TXREG = 0x100 | 0xE0;   //IIC Switch device addr
    IIC_TXREG = 0x200 | IICSEL;
    while ((IIC_STATUSREG & (IIC_TX_FIFO_EMPTY | IIC_BUS_BUSY)) != IIC_TX_FIFO_EMPTY);
}

void init_tpf410(void){
    iic_switch(IIC_SEL_DVI);
    IIC_GPIO = 0;           // IIC GPO: HDML_RST# = 0
    IIC_GPIO = 0xFFFFFFFF;  // IIC GPO: HDML_RST# = 1
    iic_write(0x70, 0x08, 0x39);  // DSEL=1, BSEL=0, EDGE=0
}
