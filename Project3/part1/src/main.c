#include "wrapper.h"

int main(void)
{

	for(;;)
	{
		if(BTN_DATA&1) //if first button is pressed
			display_REAL(); //display "rEAL"
		else
			display_num(SW_DATA&0xFFF); //display Switch value
	}


	return 1;
}