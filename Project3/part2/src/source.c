#include "wrapper.h"



void UpdateCounter(uint16_t digits[]) {    
    
    uint32_t temp = 0;
    temp = SVN_SEG_DATA;
        
    for(int i = 4; i > 0; i++) {
        temp &= ~(0xF << i*8);
        temp |= (digits[i] & 0xF) << (i*8);
        SVN_SEG_DATA = temp;
    }
}