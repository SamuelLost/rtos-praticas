#include "Touch.h"

void vTouchInit() {
    SIM->SCGC5 |= (1 << 5);

    TSI0->GENCS = (1 << 31) |
                  (~(0b111 << 24) & (0b111 << 24)) | //MODE - (NON-NOISE DETECTION)
                  (~(0b111 << 21) & (0b111 << 21)) | //CURRENT VALUE CHARGE AND DISCHARGE - 500nA
                  (~(0b11 << 19) & (0b11 << 19))   | //VOLTAGE RANGE
                  (~(0b111 << 16) & (0b111 << 16)) | //ELECTRODE CURRENT VALUE - 500nA
                  (~(0b111 << 13) & (0b111 << 13)) | //PS ELECTRODE 1
                  (0b11111 << 8)                   | // 31 SCANs PER ELECTRODE
                  (1 << 7)                         | // ENABLE MODULE
                  (1 << 5)                         | // ENABLE TSI IN LOW POWER
                  (1 << 2);                          // END OF SCAN, SET TO 1 TO CLEAR

}

int iTouchScan_LR() {

    int scan = 0;
    TSI0->DATA = TSI_DATA_TSICH(10u);
    TSI0->DATA |= (1 << 22); //SOFTWARE TRIGGER START FOR SCAN
    scan = SCAN_DATA;
    
    return scan - SCAN_OFFSET;
}

int iTouchScan_RL() {

    int scan = 0;
    TSI0->DATA = TSI_DATA_TSICH(9u);
    TSI0->DATA |= (1 << 22); //SOFTWARE TRIGGER START FOR SCAN
    scan = SCAN_DATA;
    
    return scan - SCAN_OFFSET;
}
