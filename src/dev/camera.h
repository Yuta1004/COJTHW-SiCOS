#ifndef CAMERA_H
#define CAMERA_H

#include "cojt/regbus.h"

#define CAM_BASEADDR    (REGBUS_BASEADDR + 0x1000)
#define CAMADDR         (*(volatile unsigned int *)(CAM_BASEADDR + 0x0000))
#define CAMCTRL         (*(volatile unsigned int *)(CAM_BASEADDR + 0x0004))
#define CAMINT          (*(volatile unsigned int *)(CAM_BASEADDR + 0x0008))
#define CAMFIFO         (*(volatile unsigned int *)(CAM_BASEADDR + 0x000c))

#define CBLANK          0x02
#define CAMON           0x01
#define CAMOFF          0x00
#define CAMINTENBL      0x01
#define CAMINTCLR       0x02

#endif
