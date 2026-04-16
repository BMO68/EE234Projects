/* Disable ARM interrupts (by writing to the CPSR);
Register your interrupt handler;
Configure the GIC for interrupts from the UART module, interrupt ID 82;
Configure the UART module for interrupt generation;
Enable ARM interrupts (again through the CPSR). */

//definitions for GIC configuration regisjters

#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdint.h>
#include "xil_exception.h"

/* =========================
   GIC registers
   ========================= */
#define ICCPMR      (*((volatile uint32_t *) 0xF8F00104))
#define ICCICR      (*((volatile uint32_t *) 0xF8F00100))
#define ICDDCR      (*((volatile uint32_t *) 0xF8F01000))
#define ICDISER(n)  (*(((volatile uint32_t *) 0xF8F01100) + (n)))
#define ICDICER(n)  (*(((volatile uint32_t *) 0xF8F01180) + (n)))
#define ICDIPR(n)   (*(((volatile uint32_t *) 0xF8F01400) + (n)))
#define ICDIPTR(n)  (*(((volatile uint32_t *) 0xF8F01800) + (n)))
#define ICDICFR(n)  (*(((volatile uint32_t *) 0xF8F01C00) + (n)))
#define ICCIAR      (*((volatile uint32_t *) 0xF8F0010C))
#define ICCEOIR     (*((volatile uint32_t *) 0xF8F00110))

/* =========================
   UART1 registers
   UART1 base = 0xE0001000
   ========================= */
#define UART1_CR        (*((volatile uint32_t *) 0xE0001000))
#define UART1_MR        (*((volatile uint32_t *) 0xE0001004))
#define UART1_IER       (*((volatile uint32_t *) 0xE0001008))
#define UART1_IDR       (*((volatile uint32_t *) 0xE000100C))
#define UART1_IMR       (*((volatile uint32_t *) 0xE0001010))
#define UART1_ISR       (*((volatile uint32_t *) 0xE0001014))
#define UART1_BAUDGEN   (*((volatile uint32_t *) 0xE0001018))
#define UART1_RXTOUT    (*((volatile uint32_t *) 0xE000101C))
#define UART1_RXWM      (*((volatile uint32_t *) 0xE0001020))
#define UART1_SR        (*((volatile uint32_t *) 0xE000102C))
#define UART1_FIFO      (*((volatile uint32_t *) 0xE0001030))
#define UART1_BAUDDIV   (*((volatile uint32_t *) 0xE0001034))

#define UART1_INT_ID    82U

/* UART status bits */
#define UART_SR_RXEMPTY   (1U << 1)
#define UART_SR_TXFULL    (1U << 4)

/* UART interrupt bits */
#define UART_INT_RTR      (1U << 0)   /* receiver FIFO trigger */

void disable_arm_interrupts(void);
void enable_arm_interrupts(void);
void reset_uart1(void);
void configure_uart1(void);
int uart1_rx_empty(void);
int uart1_tx_full(void);
char uart1_read_char(void);
void uart1_write_char(char c);
void clear_uart1_int_flags(void);
void configure_uart1_interrupt(void);
void configure_gic_uart1(void);
void my_handler(void *CallBackRef);

#endif