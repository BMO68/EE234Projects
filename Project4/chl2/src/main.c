#include "wrapper.h"

//this part doesn't work btw this is just for uhhhh partial credit

int main(void) {

    for(;;) {
        send_to_pc(convert_to_voltage(read_xadc_voltage()));
    }
    
    return 0;
}