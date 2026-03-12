#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define SW_DATA *((uint32_t*)0x41220000)
#define BTN_DATA *((uint32_t*)0x41200000)

/* 7-seg control register */
#define SEG_CTL *((uint32_t*)0x43C10000)

/* 7-seg digit data register */
#define SEG_DATA *((uint32_t*)0x43C10004)

/* 7-seg decimal point data register */
#define SEG_DP *((uint32_t*)0x43C10014)

/* LED register */
#define LED *((uint32_t*)0x41210000)

/* TTC0 Registers below: */

/* Clock control register TTC input clock (read/write)
CE: Select negative edge of clock (1 to select); only used for external clock if external clock selected
CS: Clock source (1 for external clock, 0 for 111MHz processor clock)
PRESCALE: Prescaler for dividing input clock by 2^(N + 1)
EN: Prescale enable (1 to enable use of clock prescale) */
#define TTCO_CLKCNT_1 *((uint32_t*)0xF8001000)

/* Counter control register (read/write)
PL: Waveform polarity (1 for 1-0 transition on match; 0 for 0-1 transition on match)
OW: Output waveform enable (1 to enable output waveform)
CR: Reset counter (1 to reset). Counter resets/restarts and CR bit automatically clears
ME: Match enable (1 to enable). Enables interrupt to be generated when any match occurs
DC: Decrement (1 to cause counter to down count)
IM: Interval mode (1 to enable interval mode; counter reset and interrupts generated at set interval)
OD: Disable counter (1 to disable/freeze counter, 0 to allow counter to count) */
#define TTCO_CNTL_1 *((uint32_t*)0xF800100C)

/* Counter value register (read only)
CNTVAL: Current counter value */
#define TTCO_CNTVAL_1 *((uint32_t*)0xF8001018)

/* Interval value register (read/write)
INTVAL: Interval value. Maximum value counter will count to before reset */
#define TTCO_INTVAL_1 *((uint32_t*)0xF8001024)

/* Match value register 1 (read/write)
MATCH: Match value. When match enabled, interrupt generated when count value equals match value */
#define TTCO_MATCH_1 *((uint32_t*)0xF8001030)

/* Interrupt status register (read only; clear on read)
EV: Event timer overflow
CO: Counter overflow
M3: Match 3 occurred
M2: Match 2 occurred
M1: Match 1 occurred
I: Interval occurred */
#define TTCO_ISR_1 *((uint32_t*)0xF8001054)

/* Interrupt enable register (read/write)
EV: Event timer overflow (1 to enable)
CO: Counter overflow (1 to enable)
M3: Match 3 occurred (1 to enable)
M2: Match 2 occurred (1 to enable)
M1: Match 1 occurred (1 to enable)
I: Interval occurred (1 to enable) */
#define TTCO_IER_1 *((uint32_t*)0xF8001060)

/* Event control register (read/write)
ED: Event timer disable (0 to disable). When 0, event timer stops on overflow, when 1, not disabled
EL: Event level (1 to count when input is low, 0 to count when input is high)
EN: Enable event timer (1 to enable) */
#define TTCO_EVENTCNTL_1 *((uint32_t*)0xF800106C)

/* Event register (read only)
EVENT: Count value. Value is duration of input waveform high or low time (set by EL bit above) */
#define TTCO_EVENT_1 *((uint32_t*)0xF8001078)

/* TTC bit masks */
#define TTC_CLKCNT_PS_EN        0x00000001U
#define TTC_CLKCNT_PS_SHIFT     1U
#define TTC_CLKCNT_PS_MASK      0x0000001EU
#define TTC_CLKCNT_CS_MASK      0x00000020U
#define TTC_CLKCNT_CE_MASK      0x00000040U

#define TTC_CNTL_OD_MASK        0x00000001U
#define TTC_CNTL_IM_MASK        0x00000002U
#define TTC_CNTL_DC_MASK        0x00000004U
#define TTC_CNTL_ME_MASK        0x00000008U
#define TTC_CNTL_CR_MASK        0x00000010U
#define TTC_CNTL_OW_MASK        0x00000020U
#define TTC_CNTL_PL_MASK        0x00000040U

#define TTC_ISR_INTERVAL_MASK   0x00000001U

#endif