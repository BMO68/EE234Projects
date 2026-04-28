#include "wrapper.h"


int main(void){

    xadc_select_ch(CH_VP);

    configureBGRLED12();

    init_GPIO_RGB();
    
    for(;;) {
        if(Buttons == 0x1) {
            LEDs = Switches & 0x3FF;
            BGR1((Switches >> 10) & 0x1);
            BGR2((Switches >> 11) & 0x1);
        }
        else if(Buttons == 0x2) {
            uint32_t pot = readVP();
            LEDs = pot & 0x3FF;
            BGR1((pot >> 10) & 0x1);
            BGR2((pot >> 11) & 0x1);
            
            if(pot < Switches) {
                write_GPIO_RGB(0x2);
            }
            else if(pot > Switches) {
                write_GPIO_RGB(0x1);
            }
            else {
                write_GPIO_RGB(0x0);
            }
        }
    }
}