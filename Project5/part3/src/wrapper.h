#ifndef TIMER_PROJECT_H
#define TIMER_PROJECT_H

#include <stdint.h>
#include "xil_exception.h"

/* ========= GIC registers ========= */
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

/* ========= UART1 registers ========= */
#define UART1_CR        (*((volatile uint32_t *) 0xE0001000))
#define UART1_MR        (*((volatile uint32_t *) 0xE0001004))
#define UART1_BAUDGEN   (*((volatile uint32_t *) 0xE0001018))
#define UART1_BAUDDIV   (*((volatile uint32_t *) 0xE0001034))
#define UART1_SR        (*((volatile uint32_t *) 0xE000102C))
#define UART1_FIFO      (*((volatile uint32_t *) 0xE0001030))

#define UART_SR_TXFULL  (1U << 4)

/* ========= Global Timer registers ========= */
#define GTC_COUNT_LO    (*((volatile uint32_t *) 0xF8F00200))
#define GTC_COUNT_HI    (*((volatile uint32_t *) 0xF8F00204))
#define GTC_CONTROL     (*((volatile uint32_t *) 0xF8F00208))
#define GTC_ISR         (*((volatile uint32_t *) 0xF8F0020C))
#define GTC_COMP_LO     (*((volatile uint32_t *) 0xF8F00210))
#define GTC_COMP_HI     (*((volatile uint32_t *) 0xF8F00214))
#define GTC_AUTO_INC    (*((volatile uint32_t *) 0xF8F00218))

#define GTC_INT_ID      27U

/* 1 second at 333.333 MHz */
#define GTC_TICKS_1S    333333333U

void disable_arm_interrupts(void);
void enable_arm_interrupts(void);
void register_irq_handler(void (*handler)(void *));

void configure_gic_gtc_interrupt(void);

void configure_uart1(void);
void uart1_write_char(char c);
void uart1_puts(const char *s);
void uart1_put_uint(uint32_t value);

uint64_t gtc_read_count(void);
void configure_global_timer_periodic_1s(void);
void clear_global_timer_interrupt(void);

#endif