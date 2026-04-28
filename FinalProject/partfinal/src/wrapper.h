#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdio.h>
#include <stdint.h>

#define Buttons *((uint32_t*)0x41200000)
#define LEDs *((uint32_t*)0x41210000)
#define Switches *((uint32_t*)0x41220000)

#define RGB_EN(i) *((uint32_t*)(0x43C00000+(i*0x10))) // B1(0) G1(1) R1(2) B2(3) G2(4) R2(5)
#define RGB_PERIOD(i) *((uint32_t*)(0x43C00004+(i*0x10))) // B1(0) G1(1) R1(2) B2(3) G2(4) R2(5)
#define RGB_WIDTH(i) *((uint32_t*)(0x43C00008+(i*0x10))) // B1(0) G1(1) R1(2) B2(3) G2(4) R2(5)

#define XADC_BASE 0x43C50000
#define XADC_CTL (*((uint32_t *)(XADC_BASE+0x300)))
#define VP *((uint32_t*)(XADC_BASE+0x020C)) // Bipolar voltage between VP and VN or unipolar voltage between VP and GND (set in CR0), data in bits 15-4

#define CH_VCCINT	0
#define CH_TEMP		1
#define CH_VCCAUX	2
#define CH_VP		3

// System Level Control Register Definitions
#define SLCR_LOCK	*((uint32_t *) 0xF8000004)
#define SLCR_UNLOCK	*((uint32_t *) 0xF8000008)
#define UNLOCK_KEY	0xDF0D
#define LOCK_KEY	0x767B

//  MIO pins register definitions
#define MIO_16		*((uint32_t *) 0xF8000740)
#define MIO_17		*((uint32_t *) 0xF8000744)
#define MIO_18		*((uint32_t *) 0xF8000748)
#define MIO_50		*((uint32_t *) 0xF80007C8)
#define MIO_51		*((uint32_t *) 0xF80007CC)

//output data register
#define GPIO_DATA(n)		*(((uint32_t*) 0xE000A040)+n)

//input data register
#define GPIO_DATA_RO(n) 	*(((uint32_t*) 0xE000A060)+n)

//direction register
#define GPIO_DIRM(n) 		*(((uint32_t*) 0xE000A204) + 16*n)

//output enable register
#define GPIO_OEN(n) 		*(((uint32_t*) 0xE000A208) + 16*n)

//RGB LED channels are bits 16-18, in bank 0
#define RGB_MASK 0x70000	

uint32_t readVP(void);

void xadc_select_ch(uint8_t ch);

void configureBGRLED12(void);

void configure_PS_MIO(void);

void set_GPIO_RGB_output();

void set_GPIO_RGB_input();

void en_GPIO_RGB_output();

void dis_GPIO_RGB_output();

void write_GPIO_RGB(uint32_t val);

void init_GPIO_RGB();

void BGR1(uint32_t val);

void BGR2(uint32_t val);

#endif