#ifndef GTC_INTERRUPT_H_
#define GTC_INTERRUPT_H_

#include <stdint.h>
#include "spi.h"   // provides SPI_TXD, SPI_SR, SPI_CR, wait_tx_not_full, SS_AG

// Global Timer registers
#define GTCR0   *((volatile uint32_t *) 0xF8F00200)
#define GTCR1   *((volatile uint32_t *) 0xF8F00204)
#define GTCTRL  *((volatile uint32_t *) 0xF8F00208)
#define GTIS    *((volatile uint32_t *) 0xF8F0020C)
#define GTCVR0  *((volatile uint32_t *) 0xF8F00210)
#define GTCVR1  *((volatile uint32_t *) 0xF8F00214)
#define GTAIR   *((volatile uint32_t *) 0xF8F00218)

// GTCTRL bit positions
#define GTC_ENABLE      (1 << 0)
#define GTC_COMP_ENABLE (1 << 1)
#define GTC_IRQ_ENABLE  (1 << 2)
#define GTC_AUTOINC     (1 << 3)

// GTC runs at half CPU clock: 666.667 MHz / 2 = 333,333,333 Hz
#define GTC_TICKS_PER_SECOND  333333333

void configure_gtc_interrupt(void);
void service_gtc_int(void);
void gtc_start(void);
void gtc_stop(void);

#endif