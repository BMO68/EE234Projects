#include "wrapper.h"

/* =========================
   ARM IRQ enable/disable
   ========================= */
void disable_arm_interrupts(void)
{
    uint32_t cpsr_val;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val |= 0x80;                 /* set I bit */
    asm volatile("msr cpsr, %0" : : "r"(cpsr_val));
}

void enable_arm_interrupts(void)
{
    uint32_t cpsr_val;
    asm volatile("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val &= ~0x80U;               /* clear I bit */
    asm volatile("msr cpsr, %0" : : "r"(cpsr_val));
}

/* =========================
   UART helpers
   ========================= */
void reset_uart1(void)
{
    UART1_CR = 0x00000003;            /* SRR + SRT */
    while (UART1_CR & 0x00000003) {
        /* wait for reset bits to self-clear */
    }
}

void configure_uart1(void)
{
    reset_uart1();

    /* Normal mode, 8-bit, no parity, 1 stop bit, reference clock */
    UART1_MR = 0x00000020;

    /* Common 115200 settings shown in RealDigital UART page */
    UART1_BAUDGEN = 0x7C;
    UART1_BAUDDIV = 6;

    /* Optional timeout can be zero for this lab */
    UART1_RXTOUT = 0;

    /* Enable TX and RX */
    UART1_CR = 0x00000014;
}

int uart1_rx_empty(void)
{
    return (UART1_SR & UART_SR_RXEMPTY) != 0U;
}

int uart1_tx_full(void)
{
    return (UART1_SR & UART_SR_TXFULL) != 0U;
}

char uart1_read_char(void)
{
    return (char)(UART1_FIFO & 0xFFU);
}

void uart1_write_char(char c)
{
    while (uart1_tx_full()) {
        /* wait for room in TX FIFO */
    }
    UART1_FIFO = (uint32_t)(uint8_t)c;
}

void clear_uart1_int_flags(void)
{
    /* write-back current flags to clear sticky ISR bits */
    UART1_ISR = UART1_ISR;
}

void configure_uart1_interrupt(void)
{
    /* mask everything first, clear stale flags */
    UART1_IDR = 0x1FFFU;
    clear_uart1_int_flags();

    /* interrupt when >= 1 byte is in RX FIFO */
    UART1_RXWM = 1U;

    /* unmask receiver FIFO trigger interrupt */
    UART1_IER = UART_INT_RTR;
}

/* =========================
   GIC helpers for interrupt 82
   ========================= */
void configure_gic_uart1(void)
{
    /* interrupt 82 bookkeeping */
    const uint32_t iser_index  = 82U / 32U;          /* 2 */
    const uint32_t iser_bit    = 82U % 32U;          /* 18 */
    const uint32_t ipr_index   = 82U / 4U;           /* 20 */
    const uint32_t ipr_shift   = (82U % 4U) * 8U;    /* 16 */
    const uint32_t icfr_index  = 82U / 16U;          /* 5 */
    const uint32_t icfr_shift  = (82U % 16U) * 2U;   /* 4 */

    /* 1) disable distributor */
    ICDDCR = 0U;

    /* 2) drive IRQ from GIC */
    ICCICR = 0x3U;

    /* 3) allow all priorities */
    ICCPMR = 0xFFU;

    /* disable interrupt 82 before reconfiguring */
    ICDICER(iser_index) = (1U << iser_bit);

    /* target CPU0 */
    ICDIPTR(ipr_index) &= ~(0xFFU << ipr_shift);
    ICDIPTR(ipr_index) |=  (0x01U << ipr_shift);

    /* set priority, e.g. 0xA0 like the RealDigital examples */
    ICDIPR(ipr_index) &= ~(0xFFU << ipr_shift);
    ICDIPR(ipr_index) |=  (0xA0U << ipr_shift);

    /* set to level-sensitive (same style used in RealDigital examples) */
    ICDICFR(icfr_index) &= ~(0x3U << icfr_shift);
    ICDICFR(icfr_index) |=  (0x1U << icfr_shift);

    /* re-enable interrupt 82 */
    ICDISER(iser_index) = (1U << iser_bit);

    /* 5) enable distributor */
    ICDDCR = 1U;
}

/* =========================
   IRQ handler
   ========================= */
void my_handler(void *CallBackRef)
{
    (void)CallBackRef;

    uint32_t id = ICCIAR;

    if (id == UART1_INT_ID) {
        while (!uart1_rx_empty()) {
            char c = uart1_read_char();
            uart1_write_char(c);      /* echo */
        }

        clear_uart1_int_flags();
    }

    ICCEOIR = id;
}