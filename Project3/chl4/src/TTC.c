#include "TTC.h"

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

void ttc_disable(void)
{
    TTCO_CNTL_1 |= TTC_CNTL_OD_MASK;
}

void ttc_set_clock(uint8_t prescale)
{
    uint32_t reg = 0U;

    reg &= ~TTC_CLKCNT_CS_MASK;   /* use processor clock */
    reg &= ~TTC_CLKCNT_CE_MASK;   /* no negative-edge clocking */
    reg |= TTC_CLKCNT_PS_EN;      /* enable prescaler */
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

    reg |= TTC_CNTL_IM_MASK;      /* interval mode */
    reg &= ~TTC_CNTL_DC_MASK;     /* count up */
    reg &= ~TTC_CNTL_ME_MASK;     /* no match mode */
    reg &= ~TTC_CNTL_OD_MASK;     /* enable counting */

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

void display_4digits(uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
    uint32_t temp = 0U;

    /* enable display in default mode */
    SEG_CTL = 1U;

    /* one byte per digit, low nibble used in default mode */
    temp |= ((uint32_t)(d0 & 0x0F)) << 0;
    temp |= ((uint32_t)(d1 & 0x0F)) << 8;
    temp |= ((uint32_t)(d2 & 0x0F)) << 16;
    temp |= ((uint32_t)(d3 & 0x0F)) << 24;

    /* decimal points off */
    temp |= 0x80808080U;

    SEG_DATA = temp;
}

void display_ms(uint32_t ms)
{
    if (ms > 9999U) {
        ms = 9999U;
    }

    display_4digits(
        (ms / 1000U) % 10U,
        (ms / 100U) % 10U,
        (ms / 10U) % 10U,
        ms % 10U
    );
}

uint32_t random_delay_ms(void)
{
    uint32_t raw = TTCO_CNTVAL_1;
    return 1000U + (raw % 9000U);
}