#include "wrapper.h"

int main(void) { //Main function which combines source functions to read switches, read buttons, and drive display based on inputs

    uint16_t btns[2] = { 0 };
    uint16_t digits[4] = { 0 };

    SEG_CTL = 0x01;
    SEG_DATA = 0x80808080;
    
    for(;;) {

        Delay();

        DecodeButtons(btns); //Step 1: Read and store buttons in btns array
        if(btns[0] == 1) { //if the first button (rightmost) is pressed...
            IncrementCounter(digits, ReadSwitches()); //IncrementCounter is called and "digits" array and Function is called to pass switch values as arguements
        }
        if(btns[1] == 2) { //if the ssecond button (left of the rightmost button) is pressed...
            ResetCounter(digits);
        }
        UpdateCounter(digits); //Step 2: Update display with "digits" array, with 0 being rightmost digit and 3 being leftmost display
    }

    return 1;
}