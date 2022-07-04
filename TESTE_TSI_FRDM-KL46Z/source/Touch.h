#ifndef TOUCH_H

#define TOUCH_H

#include "MKL46Z4.h"

//prototypes
void vTouchInit();
int iTouchScan_LR();
int iTouchScan_RL();

#define SCAN_OFFSET 615 //Offset para o intervalo de scan
#define SCAN_DATA (TSI0->DATA & 0xFFFF) //Acessando os 16 bits de TSI0_DATA_TSICNT

#endif //TOUCH_H
