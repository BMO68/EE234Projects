#include "wrapper.h"

int main(void) // *MOST* of this is just the sample code RealDigital provides
{
	SEG_DATA = 0;
	SEG_CTL = 0x01;
	SEG_DATA = 0x80808080;
	for(;;)
	{
		for(int i = 0; i < 3; i++)
		{

			uint16_t value = 0xF & Read_Switches()>>(4*i);
			Display_Number(i, value);
		
			
		}

		uint16_t value = Read_Buttons();
		Display_Number(0x3, value);

	}
	return 1;
}