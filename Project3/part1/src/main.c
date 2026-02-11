#include "wrapper.h"

int main(void)
{
	SEG_DATA = 0;
	SEG_CTL = 0x01;
	SEG_DATA = 0x80808080;
	for(;;)
	{
		for(int i = 0; i < 4; i++)
		{

			uint16_t value = 0xF & Read_Switches()>>(4*i);
			Display_Number(i, value);

			value = Read_Buttons();
			Display_Number(0x3, value);

		}

	}
	return 1;
}