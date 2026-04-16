#include "wrapper.h"

/* ========= ARM IRQ enable/disable ========= */
void disable_arm_interrupts(void)
{
    uint32_t cpsr;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr));
    cpsr |= 0x80U;
    asm volatile("msr cpsr, %0" : : "r"(cpsr));
}

void enable_arm_interrupts(void)
{
    uint32_t cpsr;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr));
    cpsr &= ~0x80U;
    asm volatile("msr cpsr, %0" : : "r"(cpsr));
}

/* Xilinx IRQ vector-table registration */
void register_irq_handler(void (*handler)(void *))
{
    Xil_ExceptionRegisterHandler(5, (Xil_ExceptionHandler)handler, NULL);
}

/* ========= GIC helpers ========= */
void configure_gic_uart1(void)
{
    /* interrupt 82 => ICDISER(2) bit 18, ICDIPR(20) byte 2, ICDIPTR(20) byte 2 */
    ICDDCR = 0U;
    ICCICR = 0x3U;
    ICCPMR = 0xFFU;

    ICDICER(2) = (1U << 18);

    ICDIPTR(20) &= ~(0xFFU << 16);
    ICDIPTR(20) |=  (0x01U << 16);      /* CPU0 */

    ICDIPR(20) &= ~(0xFFU << 16);
    ICDIPR(20) |=  (0xA0U << 16);

    ICDICFR(5) &= ~(0x3U << 4);
    ICDICFR(5) |=  (0x1U << 4);

    ICDISER(2) = (1U << 18);

    ICDDCR = 1U;
}

void configure_gic_gpio(void)
{
    /* interrupt 52 => example mapping from RealDigital */
    ICDDCR = 0U;
    ICCICR = 0x3U;
    ICCPMR = 0xFFU;

    ICDICER(1) = (1U << 20);

    ICDIPTR(13) &= ~0xFFU;
    ICDIPTR(13) |=  0x01U;              /* CPU0 */

    ICDIPR(13) &= ~0xFFU;
    ICDIPR(13) |=  0xA0U;

    ICDICFR(3) &= ~0x300U;
    ICDICFR(3) |=  0x100U;

    ICDISER(1) = (1U << 20);

    ICDDCR = 1U;
}

void configure_gic_gtc(void)
{
    /* interrupt 27 => ISER0 bit 27 */
    ICDDCR = 0U;
    ICCICR = 0x3U;
    ICCPMR = 0xFFU;

    ICDICER(0) = (1U << 27);

    ICDIPTR(6) &= ~(0xFFU << 24);
    ICDIPTR(6) |=  (0x01U << 24);       /* CPU0 */

    ICDIPR(6) &= ~(0xFFU << 24);
    ICDIPR(6) |=  (0xA0U << 24);

    ICDICFR(1) &= ~(0x3U << 22);
    ICDICFR(1) |=  (0x1U << 22);

    ICDISER(0) = (1U << 27);

    ICDDCR = 1U;
}

/* ========= UART helpers ========= */
void configure_uart1(void)
{
    /* reset TX and RX */
    UART1_CR = 0x00000003U;
    while (UART1_CR & 0x00000003U) {
    }

    /* normal mode, 8-bit, no parity, 1 stop */
    UART1_MR = 0x00000020U;

    /* standard Blackboard/RealDigital example values for 115200 */
    UART1_BAUDGEN = 0x7CU;
    UART1_BAUDDIV = 6U;
    UART1_RXTOUT  = 0U;

    /* enable TX and RX */
    UART1_CR = 0x00000014U;
}

void configure_uart1_interrupt(void)
{
    UART1_IDR  = 0x1FFFU;      /* disable all first */
    UART1_ISR  = 0x1FFFU;      /* clear stale sticky flags */
    UART1_RXWM = 1U;           /* interrupt when FIFO has >= 1 byte */
    UART1_IER  = UART_INT_RTR; /* unmask RX trigger interrupt */
}

int uart1_rx_empty(void)
{
    return (UART1_SR & UART_SR_RXEMPTY) != 0U;
}

char uart1_read_char(void)
{
    return (char)(UART1_FIFO & 0xFFU);
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

void uart1_clear_rx_interrupt_flag(void)
{
    UART1_ISR = UART_INT_RTR;
}

/* ========= RGB LED helpers ========= */
static void rgb_write_raw(uint32_t val3)
{
    uint32_t regval;

    regval = GPIO_DATA(RGB_BANK);
    regval &= ~RGB_MASK;
    regval |= ((val3 & 0x7U) << 16);
    GPIO_DATA(RGB_BANK) = regval;
}

void configure_rgb_led(void)
{
    GPIO_OEN(RGB_BANK) &= ~RGB_MASK;
    GPIO_DIRM(RGB_BANK) |= RGB_MASK;
    rgb_write_raw(0U);
    GPIO_OEN(RGB_BANK) |= RGB_MASK;
}

void rgb_led_on(void)
{
    rgb_write_raw(0x7U);
}

void rgb_led_off(void)
{
    rgb_write_raw(0x0U);
}

/* ========= GPIO button interrupt helpers ========= */
void configure_button_interrupts(void)
{
    uint32_t both = BT4_MASK | BT5_MASK;

    GPIO_INT_DIS(BT4_BANK) = both;

    /* rising edge: TYPE=1, POL=1, ANY=0 */
    GPIO_INT_TYPE(BT4_BANK) |= both;
    GPIO_INT_POL(BT4_BANK)  |= both;
    GPIO_INT_ANY(BT4_BANK)  &= ~both;

    /* clear stale flags */
    GPIO_INT_STAT(BT4_BANK) = both;

    GPIO_INT_EN(BT4_BANK) = both;
}

uint32_t get_gpio_int_status(int bank, uint32_t mask)
{
    return GPIO_INT_STAT(bank) & mask;
}

void clear_gpio_int_status(int bank, uint32_t mask)
{
    GPIO_INT_STAT(bank) = mask;
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

    return (((uint64_t)hi1) << 32) | (uint64_t)lo;
}

void clear_global_timer_interrupt(void)
{
    GTC_ISR = 1U;   /* write 1 to clear EF */
}

void start_blink_timer(void)
{
    uint64_t now;
    uint64_t cmp;

    now = gtc_read_count();
    cmp = now + (uint64_t)GTC_HALFSEC_TICKS;

    GTC_CONTROL = 0U;
    clear_global_timer_interrupt();

    GTC_COMP_LO = (uint32_t)(cmp & 0xFFFFFFFFU);
    GTC_COMP_HI = (uint32_t)(cmp >> 32);
    GTC_AUTO_INC = GTC_HALFSEC_TICKS;

    /* EN=1, CE=1, IE=1, AI=1 */
    GTC_CONTROL = 0x0000000FU;
}

void stop_blink_timer(void)
{
    GTC_CONTROL = 0U;
    clear_global_timer_interrupt();
}