#include "wrapper.h"

uint16_t ReadButtons(void) { //reads buttons, returns hex value
    return 0xF & BTN_DATA;
}

uint16_t ReadSwitches(void) { //reads switches, returns hex value
    return 0x7 & SW_DATA;
}

void DecodeButtons(uint16_t buttons[]) { //parses switch values and stores information in "buttons" array
    uint16_t btns = ReadButtons();
    if((btns & 0x1) == 0x1) {
        buttons[0] = buttons[0] ^ 0x1;
    }
    buttons[1] = 0x02 & btns;
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
        
    for(int i = 3; i > -1; i--) {
        temp &= ~(0xF << i*8);
        temp |= (digits[i] & 0xF) << (i*8);
        SEG_DATA = temp;
    }
}

void Delay(void) { //Delay function to aid with actually being able to see incrementation
    for(int i = 8000000; i != 0; i--) {
        
    }
}