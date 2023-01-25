#ifndef MOUSE_H
#define MOUSE_H

#define MOUSE_SPEED_0   0b10
#define MOUSE_SPEED_1   0b01
#define MOUSE_SPEED_2   0b00
#define MOUSE_SPEED_3   0b11

#define MOUSE_VGA       0b01
#define MOUSE_XGA       0x01
#define MOUSE_SXGA      0b10

#define MOUSE_BASEADDR  0x50020000
#define MOUSE_XPOS      (*(volatile unsigned int *)(MOUSE_BASEADDR + 0x0000))
#define MOUSE_YPOS      (*(volatile unsigned int *)(MOUSE_BASEADDR + 0x0004))
#define MOUSE_ZPOS      (*(volatile unsigned int *)(MOUSE_BASEADDR + 0x0008))
#define MOUSE_BTN       (*(volatile unsigned int *)(MOUSE_BASEADDR + 0x000c))
#define MOUSE_CTRL      (*(volatile unsigned int *)(MOUSE_BASEADDR + 0x0010))
#define MOUSE_RESOL     (*(volatile unsigned int *)(MOUSE_BASEADDR + 0x0014))

#define MOUSE_LBTN          0b100
#define MOUSE_CBTN          0b010
#define MOUSE_RBTN          0b001
#define MOUSE_CLICKED(x, c) ((x & c) != 0)

void mouse_init(unsigned int resol, unsigned int speed);
int mouse_read(int *xpos, int *ypos, int *zpos, int *btn);

#endif
