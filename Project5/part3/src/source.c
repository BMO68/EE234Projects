#include "wrapper.h"

/* ========= ARM IRQ control ========= */
void disable_arm_interrupts(void)
{
    uint32_t cpsr_val;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val |= 0x80U;
    asm volatile("msr cpsr, %0" : : "r"(cpsr_val));
}

void enable_arm_interrupts(void)
{
    uint32_t cpsr_val;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val &= ~0x80U;
    asm volatile("msr cpsr, %0" : : "r"(cpsr_val));
}

/* ========= IRQ table registration ========= */
void register_irq_handler(void (*handler)(void *))
{
    Xil_ExceptionRegisterHandler(5, (Xil_ExceptionHandler)handler, NULL);
}

/* ========= UART1 setup/helpers ========= */
void configure_uart1(void)
{
    /* reset TX and RX */
    UART1_CR = 0x00000003;
    while (UART1_CR & 0x00000003) {
    }

    /* 8-bit, no parity, 1 stop, normal channel mode */
    UART1_MR = 0x00000020;

    /* 115200 baud (same style as the earlier UART project) */
    UART1_BAUDGEN = 0x7C;
    UART1_BAUDDIV = 6;

    /* enable TX and RX */
    UART1_CR = 0x00000014;
}

void uart1_write_char(char c)
{
    while (UART1_SR & UART_SR_TXFULL) {
    }
    UART1_FIFO = (uint32_t)(uint8_t)c;
}

void uart1_puts(const char *s)
{
    while (*s != '\0') {
        uart1_write_char(*s++);
    }
}

void uart1_put_uint(uint32_t value)
{
    char buf[11];
    int i = 0;
    int j;

    if (value == 0U) {
        uart1_write_char('0');
        return;
    }

    while (value > 0U) {
        buf[i++] = (char)('0' + (value % 10U));
        value /= 10U;
    }

    for (j = i - 1; j >= 0; --j) {
        uart1_write_char(buf[j]);
    }
}

/* ========= Global Timer helpers ========= */
uint64_t gtc_read_count(void)
{
    uint32_t hi1, lo, hi2;

    do {
        hi1 = GTC_COUNT_HI;
        lo  = GTC_COUNT_LO;
        hi2 = GTC_COUNT_HI;
    } while (hi1 != hi2);

    return (((uint64_t)hi1) << 32) | lo;
}

void clear_global_timer_interrupt(void)
{
    GTC_ISR = 1U;   /* write 1 to clear event flag */
}

void configure_global_timer_periodic_1s(void)
{
    uint64_t now;
    uint64_t first_compare;

    /* disable timer while configuring */
    GTC_CONTROL = 0U;
    clear_global_timer_interrupt();

    now = gtc_read_count();
    first_compare = now + (uint64_t)GTC_TICKS_1S;

    GTC_COMP_LO = (uint32_t)(first_compare & 0xFFFFFFFFU);
    GTC_COMP_HI = (uint32_t)(first_compare >> 32);

    /* auto-increment by 1 second each compare */
    GTC_AUTO_INC = GTC_TICKS_1S;

    /* EN=1, CE=1, IE=1, AI=1  => 0b1111 = 0xF */
    GTC_CONTROL = 0x0000000FU;
}

/* ========= GIC config for interrupt ID 27 ========= */
void configure_gic_gtc_interrupt(void)
{
    /* ID 27 => ISER0 bit 27, IPR6 byte 3, IPTR6 byte 3, ICFGR1 bits 23:22 */
    ICDDCR = 0U;        /* disable distributor */
    ICCICR = 0x3U;      /* enable signaling to CPU */
    ICCPMR = 0xFFU;     /* allow all priorities */

    ICDICER(0) = (1U << 27);

    ICDIPTR(6) &= ~(0xFFU << 24);
    ICDIPTR(6) |=  (0x01U << 24);     /* target CPU0 */

    ICDIPR(6)  &= ~(0xFFU << 24);
    ICDIPR(6)  |=  (0xA0U << 24);     /* priority */

    ICDICFR(1) &= ~(0x3U << 22);
    ICDICFR(1) |=  (0x1U << 22);      /* same style used in RealDigital examples */

    ICDISER(0) = (1U << 27);

    ICDDCR = 1U;       /* enable distributor */
}