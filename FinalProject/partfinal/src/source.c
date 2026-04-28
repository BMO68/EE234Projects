#include "wrapper.h"

//configures the xadc to sample the given channel
void xadc_select_ch(uint8_t ch)
{
	uint32_t reg_temp;

	//mask to only get 5 bits
	ch&=0x1F;

	reg_temp = XADC_CTL;

	//set [4:0] to the channel bits given
	reg_temp &= 0xFFE0;
	reg_temp |= ch;

	XADC_CTL = reg_temp;
}
void configureBGRLED12(void) {
    RGB_PERIOD(0) = 0x1000;
    RGB_PERIOD(1) = 0x1000;
    RGB_PERIOD(2) = 0x1000;
    
    RGB_WIDTH(0) = 0xFF;
    RGB_WIDTH(1) = 0xFF;
    RGB_WIDTH(2) = 0xFF;

    RGB_PERIOD(3) = 0x1000;
    RGB_PERIOD(4) = 0x1000;
    RGB_PERIOD(5) = 0x1000;
    
    RGB_WIDTH(3) = 0xFF;
    RGB_WIDTH(4) = 0xFF;
    RGB_WIDTH(5) = 0xFF;
}

uint32_t readVP(void) {
    return (VP >> 4);
}

void BGR1(uint32_t val) {
    //RGB_EN(0) = val;
    RGB_EN(1) = val;
    //RGB_EN(2) = val;
}

void BGR2(uint32_t val) {
    //RGB_EN(3) = val;
    RGB_EN(4) = val;
    //RGB_EN(5) = val;
}


// Configure MIO pins for the Blackboard's PS-connected buttons and LEDs
void configure_PS_MIO(void) {	
	SLCR_UNLOCK = UNLOCK_KEY;	//unlock SLCRs
	MIO_50 = 0x0600; // BTN4 is LVCMOS33
	MIO_51 = 0x0600; // BTN5 is LVCMOS33
	MIO_16 = 0x1600; // RGB_LED_B is LVCMOS33 with disabled input buffer
	MIO_17 = 0x1600; // RGB_LED_R is LVCMOS33 with disabled input buffer
	MIO_18 = 0x1600; // RGB_LED_G is LVCMOS33 with disabled input buffer
	SLCR_LOCK = LOCK_KEY;	//relock SLCRs
}

//configures MIO 16,17,18 as outputs
void set_GPIO_RGB_output()
{ 
	GPIO_DIRM(0) = RGB_MASK ;
}

//configures MIO 16,17,18 as inputs
void set_GPIO_RGB_input()
{
	GPIO_DIRM(0) &= ~RGB_MASK ; 
}

//enables the output of bank0 16,17,18
void en_GPIO_RGB_output()
{

	GPIO_OEN(0) |= RGB_MASK ; 
}

//disables output of bank0 16-18
void dis_GPIO_RGB_output()
{
	GPIO_OEN(0) &= ~RGB_MASK;
}

//writes the passed value into the 3 outputs for the RGB LED's
void write_GPIO_RGB(uint32_t val)
{
	val = (0x7&val)<<16;	//use only bottom 3 bits, and shift to place
	GPIO_DATA(0) = (GPIO_DATA(0)&~RGB_MASK) | val;	//change only RGB bits
}


//Configures RGB Connected GPIO as outputs on channels
//initializes value to zero and enables output
void init_GPIO_RGB()
{
	dis_GPIO_RGB_output();
	set_GPIO_RGB_output();	//configure as output
	write_GPIO_RGB(0);	//clear value of RGBs
	en_GPIO_RGB_output();
}