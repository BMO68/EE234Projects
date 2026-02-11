#include "wrapper.h"
#define ZERO 0x0
#define ONE 0x1
#define TWO 0x2
#define THREE 0x3
#define FOUR 0x4


uint16_t Read_Switches(void) {
	return 0xFFF & SW_DATA;
}

uint16_t Read_Buttons(void) {
	return 0xF & BTN_DATA;
}

void Display_Number(int segment_display, uint16_t value)
{
		uint32_t temp = SEG_DATA;
		temp &= ~(0xF << segment_display*8);
		temp |= (value & 0xF) << (segment_display*8);
		SEG_DATA = temp;
}