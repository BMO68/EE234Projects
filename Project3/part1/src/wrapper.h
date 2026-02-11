#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define SW_DATA	*((uint32_t *)0x41220000)
#define BTN_DATA *((uint32_t *)0x41200000)

//7-seg control register
#define SEG_CTL *((uint32_t *) 0x43c10000)

//7-seg digit data register
#define SEG_DATA *((uint32_t *) 0x43C10004)

//7-seg decimal point data reg
#define SEG_DP *((uint32_t *) 0x43C10014)

void display_REAL(void);

void display_num(uint16_t n);