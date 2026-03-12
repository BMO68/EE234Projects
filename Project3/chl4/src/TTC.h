#ifndef TTC_H
#define TTC_H

#include "wrapper.h"

void ttc_disable(void);
void ttc_set_clock(uint8_t prescale);
void ttc_set_interval(uint16_t interval);
void ttc_enable_interval_interrupt(void);
void ttc_enable_interval_mode(void);
void ttc_reset(void);
void ttc_init(uint16_t interval, uint8_t prescale);

void ttc_wait_for_tick(void);

/* display helpers */
void display_4digits(uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0);
void display_ms(uint32_t ms);

/* pseudo-random wait generator: returns 1000..9999 ms */
uint32_t random_delay_ms(void);

#endif