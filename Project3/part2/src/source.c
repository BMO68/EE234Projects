#include "wrapper.h"

uint16_t ReadButtons(void) { //reads buttons, returns hex value
    return 0xF & BTN_DATA;
}

uint16_t ReadSwitches(void) { //reads switches, returns hex value
    return 0x7 & SW_DATA;
}

uint16_t DecodeButtons(uint16_t buttons[]) { //parses switch values and stores information in "buttons" array
    uint16_t btns = ReadButtons();
    buttons[0] = 0x1 & btns;
    buttons[1] = 0x10 & btns;
}

void ResetCounter(uint16_t digits[]) { //resets the counter;
    for(int i = 0; i < 4; i++)
    {
        digits[i] = 0;
    }
}

void IncrementCounter(uint16_t digits[], uint16_t switches) { //increments the counter, checks for rollover conditions and carries over rollover. If leftmost digit = 10, counter resets
    digits[switches] += 1;
    for(int i = 0; i < 3; i++) {
        if(digits[i] == 10) {
            digits[i+1] += 1;
            digits[i] = 0;
        }
    }
    if(digits[3] == 10) {
        ResetCounter(digits);
    }
}

void UpdateCounter(uint16_t digits[]) { //updates the counter display
    
    uint32_t temp = 0;
    temp = SEG_DATA;
        
    for(int i = 4; i > 0; i--) {
        temp &= ~(0xF << i*8);
        temp |= (digits[i] & 0xF) << (i*8);
        SEG_DATA = temp;
    }
}