#include "TTC.h"

/* Bit masks based on the TTC register descriptions */
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

#define TTC_ISR_INTERVAL_MASK   0x00000001U

/* Blackboard FPGA pushbuttons */
#define BTN0_MASK               0x00000001U   /* toggle start/stop */
#define BTN1_MASK               0x00000002U   /* clear */

/* internal helper: wait until selected button(s) released */
static void wait_for_button_release(uint32_t mask)
{
    while (BTN_DATA & mask) {
    }
}

void ttc_disable(void)
{
    TTCO_CNTL_1 |= TTC_CNTL_OD_MASK;
}

void ttc_set_clock(uint8_t prescale)
{
    uint32_t reg = 0U;

    /* CS = 0 for processor clock */
    reg &= ~TTC_CLKCNT_CS_MASK;

    /* CE = 0, do not use negative edge */
    reg &= ~TTC_CLKCNT_CE_MASK;

    /* EN = 1 to enable prescaler */
    reg |= TTC_CLKCNT_PS_EN;

    /* PRESCALE = N, divides input clock by 2^(N+1) */
    reg |= (((uint32_t)prescale << TTC_CLKCNT_PS_SHIFT) & TTC_CLKCNT_PS_MASK);

    TTCO_CLKCNT_1 = reg;
}

void ttc_set_interval(uint16_t interval)
{
    TTCO_INTVAL_1 = (uint32_t)interval;
}

void ttc_enable_interval_interrupt(void)
{
    TTCO_IER_1 = TTC_ISR_INTERVAL_MASK;
}

void ttc_reset(void)
{
    TTCO_CNTL_1 |= TTC_CNTL_CR_MASK;
}

void ttc_enable_interval_mode(void)
{
    uint32_t reg = TTCO_CNTL_1;

    /* IM = 1 enables interval mode */
    reg |= TTC_CNTL_IM_MASK;

    /* DC = 0 causes counter to count up */
    reg &= ~TTC_CNTL_DC_MASK;

    /* ME = 0 disables match mode */
    reg &= ~TTC_CNTL_ME_MASK;

    /* OD = 0 lets counter count */
    reg &= ~TTC_CNTL_OD_MASK;

    TTCO_CNTL_1 = reg;
}

void ttc_init(uint16_t interval, uint8_t prescale)
{
    ttc_disable();
    ttc_set_clock(prescale);
    ttc_set_interval(interval);
    ttc_enable_interval_interrupt();
    ttc_reset();
    ttc_enable_interval_mode();
}

void ttc_wait_for_tick(void)
{
    while ((TTCO_ISR_1 & TTC_ISR_INTERVAL_MASK) == 0U) {
    }
}

void ttc_delay_ms(uint32_t ms)
{
    while (ms > 0U) {
        ttc_wait_for_tick();
        ms--;
    }
}

/* 7-segment display function
   d3 d2 d1 d0 = left to right digits */
void display_4digits(uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
    uint32_t temp = 0;

    /* enable display in default mode */
    SEG_CTL = 1;

    /* one byte per digit */
    temp |= ((uint32_t)(d0 & 0x0F)) << 0;
    temp |= ((uint32_t)(d1 & 0x0F)) << 8;
    temp |= ((uint32_t)(d2 & 0x0F)) << 16;
    temp |= ((uint32_t)(d3 & 0x0F)) << 24;

    /* decimal points off */
    temp |= 0x80808080;

    SEG_DATA = temp;
}

/* Button controls:
   BTN0 toggles running/stopped
   BTN1 clears stopwatch to 00.00 and stops
*/
void stopwatch_update_buttons(uint8_t *running, uint32_t *sec, uint32_t *cs)
{
    if (BTN_DATA & BTN0_MASK) {
        *running = !(*running);
        wait_for_button_release(BTN0_MASK);
    }

    if (BTN_DATA & BTN1_MASK) {
        *running = 0;
        *sec = 0;
        *cs = 0;
        wait_for_button_release(BTN1_MASK);
    }
}