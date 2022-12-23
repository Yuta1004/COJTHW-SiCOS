#ifndef DVI_H
#define DVI_H

#define IIC_BASEADDR    0x41600000
#define IIC_CTRLREG     (*((volatile unsigned int*)(IIC_BASEADDR + 0x100)))
#define IIC_STATUSREG   (*((volatile unsigned int*)(IIC_BASEADDR + 0x104)))
#define IIC_TXREG       (*((volatile unsigned int*)(IIC_BASEADDR + 0x108)))
#define IIC_GPIO        (*((volatile unsigned int*)(IIC_BASEADDR + 0x124)))

#define IIC_SEL_DVI         0x04
#define IIC_TX_FIFO_EMPTY   0x80
#define IIC_BUS_BUSY        0x04
#define IIC_TX_FIFO_FULL    0x10

void init_iic();
void iic_write(unsigned int daddr, unsigned int waddr, unsigned int wdata);
void iic_switch(int IICSEL);
void init_tpf410();

#endif
