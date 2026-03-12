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
    reg &= ~TTC_CLKCNT_CS_MASK;
    reg &= ~TTC_CLKCNT_CE_MASK;
    reg |= TTC_CLKCNT_PS_EN;
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
    reg |= TTC_CNTL_IM_MASK;
    reg &= ~TTC_CNTL_DC_MASK;
    reg &= ~TTC_CNTL_ME_MASK;
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

/* default mode display: one byte per digit, low nibble used */
void display_4digits(uint8_t d3, uint8_t d2, uint8_t d1, uint8_t d0)
{
    uint32_t temp = 0;

    SEG_CTL = 1;

    temp |= ((uint32_t)(d0 & 0x0F)) << 0;
    temp |= ((uint32_t)(d1 & 0x0F)) << 8;
    temp |= ((uint32_t)(d2 & 0x0F)) << 16;
    temp |= ((uint32_t)(d3 & 0x0F)) << 24;

    temp |= 0x80808080U;   /* decimal points off */
    SEG_DATA = temp;
}

/* show signed error in centiseconds
   positive = early
   negative = late, with minus sign in leftmost digit */
void display_signed_score(int32_t cs)
{
    uint32_t temp = 0;
    uint32_t mag;

    /* Custom mode: each byte is raw segment data */
    SEG_CTL = 3;

    /* Active-low segment patterns in GFEDCBA order
       based on Blackboard custom mode behavior */
    static const uint8_t seg_digit[10] = {
        0x40, /* 0 */
        0x79, /* 1 */
        0x24, /* 2 */
        0x30, /* 3 */
        0x19, /* 4 */
        0x12, /* 5 */
        0x02, /* 6 */
        0x78, /* 7 */
        0x00, /* 8 */
        0x10  /* 9 */
    };

    /* minus sign: segment G on only */
    const uint8_t minus_seg = 0x3F;

    /* blank digit: all segments off */
    const uint8_t blank_seg = 0x7F;

    if (cs < 0) {
        mag = (uint32_t)(-cs);

        /* leftmost digit = minus sign */
        temp |= ((uint32_t)minus_seg) << 24;
        temp |= ((uint32_t)seg_digit[(mag / 100) % 10]) << 16;
        temp |= ((uint32_t)seg_digit[(mag / 10) % 10]) << 8;
        temp |= ((uint32_t)seg_digit[mag % 10]) << 0;
    } else {
        mag = (uint32_t)cs;

        /* blank sign column for positive values */
        temp |= ((uint32_t)blank_seg) << 24;
        temp |= ((uint32_t)seg_digit[(mag / 100) % 10]) << 16;
        temp |= ((uint32_t)seg_digit[(mag / 10) % 10]) << 8;
        temp |= ((uint32_t)seg_digit[mag % 10]) << 0;
    }

    /* decimal points off */
    temp |= 0x80808080U;

    SEG_DATA = temp;
}

/* pseudo-random start value from free-running TTC counter
   returns 100..999 centiseconds = 1.00s .. 9.99s */
uint32_t random_start_cs(void)
{
    uint32_t raw = TTCO_CNTVAL_1;
    return 100U + (raw % 900U);
}