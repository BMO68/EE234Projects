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
void ttc_delay_ms(uint32_t ms);

void display_4digits(uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0);

void stopwatch_update_buttons(uint8_t *running, uint32_t *sec, uint32_t *cs);

#endif