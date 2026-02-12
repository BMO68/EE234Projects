#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#endif

#define SW_DATA	*((uint32_t*)0x41220000)
#define BTN_DATA *((uint32_t*)0x41200000)

//7-seg control register
#define SEG_CTL *((uint32_t*)0x43c10000)

//7-seg digit data register
#define SEG_DATA *((uint32_t*)0x43C10004)

//7-seg decimal point data reg
#define SEG_DP *((uint32_t*)0x43C10014)

//LED
#define LED *((uint32_t*)0x41210000)

uint16_t ReadButtons(void);

uint16_t ReadSwitches(void);

uint16_t DecodeButtons(uint16_t buttons[]);

void ResetCounter(uint16_t digits[]);

void IncrementCounter(uint16_t digits[], uint16_t switches);

void UpdateCounter(uint16_t digits[]);