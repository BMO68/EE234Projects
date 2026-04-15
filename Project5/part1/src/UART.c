#include "wrapper.h"

#define UART1_INT_ID 82

#define UART1_CR       *((uint32_t*)0xE0001000)
#define UART1_MR       *((uint32_t*)0xE0001004)
#define UART1_IER      *((uint32_t*)0xE0001008)
#define UART1_IDR      *((uint32_t*)0xE000100C)
#define UART1_ISR      *((uint32_t*)0xE0001014)
#define UART1_BAUDGEN  *((uint32_t*)0xE0001018)
#define UART1_RXTOUT   *((uint32_t*)0xE000101C)
#define UART1_RXWM     *((uint32_t*)0xE0001020)
#define UART1_FIFO     *((uint32_t*)0xE0001030)
#define UART1_BAUDDIV  *((uint32_t*)0xE0001034)
#define UART1_SR       *((uint32_t*)0xE000102C)

#define LED_CTL        *((uint32_t*)0x41210000)
#define SW_DATA        *((uint32_t*)0x41220000)

/* UART interrupt bits */
#define UART1_IXR_RTR  0x00000001
#define UART1_IXR_RO   0x00000020
#define UART1_IXR_RFR  0x00000040
#define UART1_IXR_RP   0x00000080
#define UART1_IXR_RT   0x00000100

/* UART status bits */
#define UART1_SR_RES   0x00000002   // RX empty
#define UART1_SR_TFS   0x00000010   // TX full

void configure_uart1(void) {
    UART1_CR = 0x03;          // reset RX/TX
    UART1_MR = 0x20;
    UART1_BAUDGEN = 0x7C;
    UART1_BAUDDIV = 0x06;

    UART1_IDR = 0x00003FFF;   // disable all UART interrupts
    UART1_ISR = 0x00003FFF;   // clear any stale UART interrupts

    UART1_RXWM = 1;           // interrupt when 1 byte received
    UART1_RXTOUT = 8;         // timeout for partial data

    UART1_IER = UART1_IXR_RTR | UART1_IXR_RT |
                UART1_IXR_RO  | UART1_IXR_RFR | UART1_IXR_RP;
}

void enable_interrupt82(void) {
    ICDIPTR(20) |= 0x00010000;
    ICDISER(2) = 0x00040000;
}

void disable_interrupt82(void) {
    ICDIPTR(20) &= ~0x00FF0000;
    ICDICER(2) = 0x00040000;
}

void configure_GIC(void) {
    ICDDCR = 0;
    ICCICR = 0x3;
    ICCPMR = 0xFF;

    disable_interrupt82();

    ICDIPR(20) &= ~0x00FF0000;
    ICDIPR(20) |= ((0xA0 & 0xF8) << 16);

    ICDICFR(5) &= ~0x00000030;
    ICDICFR(5) |= ((1 & 0x3) << 4);

    enable_interrupt82();

    ICDDCR = 1;
}

int uart1_rx_has_data(void) {
    return ((UART1_SR & UART1_SR_RES) == 0);
}

int uart1_tx_has_room(void) {
    return ((UART1_SR & UART1_SR_TFS) == 0);
}

uint8_t uart1_recv_char(void) {
    while (!uart1_rx_has_data()) {}
    return (uint8_t)(UART1_FIFO & 0xFF);
}

void uart1_send_char(uint8_t c) {
    while (!uart1_tx_has_room()) {}
    UART1_FIFO = c;
}

void read_and_send_character(void) {
    while (uart1_rx_has_data()) {
        uint8_t c = uart1_recv_char();
        uart1_send_char(c);
    }
}

void my_handler(void) {
    uint32_t id = ICCIAR;

    if (id == UART1_INT_ID) {
        uint32_t pending = UART1_ISR;

        if (pending & (UART1_IXR_RTR | UART1_IXR_RT)) {
            read_and_send_character();
        }

        if (pending & (UART1_IXR_RO | UART1_IXR_RFR | UART1_IXR_RP)) {
            while (uart1_rx_has_data()) {
                (void)(UART1_FIFO & 0xFF);
            }
        }

        UART1_ISR = pending & (UART1_IXR_RTR | UART1_IXR_RT |
                               UART1_IXR_RO  | UART1_IXR_RFR | UART1_IXR_RP);
    }

    ICCEOIR = id;
}