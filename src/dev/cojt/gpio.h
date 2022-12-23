#ifndef GPIO_H
#define GPIO_H

#define GPIO_BASEADDR   0x50000000
#define RESOL_SET       (*(volatile unsigned int *)(GPIO_BASEADDR + 0x00))
#define RESOL_CTRL      (*(volatile unsigned int *)(GPIO_BASEADDR + 0x04))

#define VGA             0x00
#define XGA             0x01
#define SXGA            0x02

void set_resolution(int resol);

#endif
