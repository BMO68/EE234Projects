#ifndef BLINK_PROJECT_H
#define BLINK_PROJECT_H

#include <stdint.h>
#include "xil_exception.h"

/* ========= GIC registers ========= */
#define ICCICR      (*((volatile uint32_t *)0xF8F00100))
#define ICCPMR      (*((volatile uint32_t *)0xF8F00104))
#define ICCIAR      (*((volatile uint32_t *)0xF8F0010C))
#define ICCEOIR     (*((volatile uint32_t *)0xF8F00110))

#define ICDDCR      (*((volatile uint32_t *)0xF8F01000))
#define ICDISER(n)  (*(((volatile uint32_t *)0xF8F01100) + (n)))
#define ICDICER(n)  (*(((volatile uint32_t *)0xF8F01180) + (n)))
#define ICDIPR(n)   (*(((volatile uint32_t *)0xF8F01400) + (n)))
#define ICDIPTR(n)  (*(((volatile uint32_t *)0xF8F01800) + (n)))
#define ICDICFR(n)  (*(((volatile uint32_t *)0xF8F01C00) + (n)))

/* ========= UART1 registers ========= */
#define UART1_CR        (*((volatile uint32_t *)0xE0001000))
#define UART1_MR        (*((volatile uint32_t *)0xE0001004))
#define UART1_IER       (*((volatile uint32_t *)0xE0001008))
#define UART1_IDR       (*((volatile uint32_t *)0xE000100C))
#define UART1_IMR       (*((volatile uint32_t *)0xE0001010))
#define UART1_ISR       (*((volatile uint32_t *)0xE0001014))
#define UART1_BAUDGEN   (*((volatile uint32_t *)0xE0001018))
#define UART1_RXTOUT    (*((volatile uint32_t *)0xE000101C))
#define UART1_RXWM      (*((volatile uint32_t *)0xE0001020))
#define UART1_SR        (*((volatile uint32_t *)0xE000102C))
#define UART1_FIFO      (*((volatile uint32_t *)0xE0001030))
#define UART1_BAUDDIV   (*((volatile uint32_t *)0xE0001034))

/* ========= GPIO registers ========= */
#define GPIO_DATA(n)        (*(((volatile uint32_t *)0xE000A040) + (n)))
#define GPIO_DATA_RO(n)     (*(((volatile uint32_t *)0xE000A060) + (n)))
#define GPIO_DIRM(n)        (*(((volatile uint32_t *)0xE000A204) + 16*(n)))
#define GPIO_OEN(n)         (*(((volatile uint32_t *)0xE000A208) + 16*(n)))
#define GPIO_INT_MASK(n)    (*(((volatile uint32_t *)0xE000A20C) + 16*(n)))
#define GPIO_INT_EN(n)      (*(((volatile uint32_t *)0xE000A210) + 16*(n)))
#define GPIO_INT_DIS(n)     (*(((volatile uint32_t *)0xE000A214) + 16*(n)))
#define GPIO_INT_STAT(n)    (*(((volatile uint32_t *)0xE000A218) + 16*(n)))
#define GPIO_INT_TYPE(n)    (*(((volatile uint32_t *)0xE000A21C) + 16*(n)))
#define GPIO_INT_POL(n)     (*(((volatile uint32_t *)0xE000A220) + 16*(n)))
#define GPIO_INT_ANY(n)     (*(((volatile uint32_t *)0xE000A224) + 16*(n)))

/* ========= Global Timer registers ========= */
#define GTC_COUNT_LO    (*((volatile uint32_t *)0xF8F00200))
#define GTC_COUNT_HI    (*((volatile uint32_t *)0xF8F00204))
#define GTC_CONTROL     (*((volatile uint32_t *)0xF8F00208))
#define GTC_ISR         (*((volatile uint32_t *)0xF8F0020C))
#define GTC_COMP_LO     (*((volatile uint32_t *)0xF8F00210))
#define GTC_COMP_HI     (*((volatile uint32_t *)0xF8F00214))
#define GTC_AUTO_INC    (*((volatile uint32_t *)0xF8F00218))

/* ========= interrupt IDs ========= */
#define UART1_INT_ID    82U
#define GPIO_INT_ID     52U
#define GTC_INT_ID      27U

/* ========= UART bits ========= */
#define UART_INT_RTR    (1U << 0)
#define UART_SR_RXEMPTY (1U << 1)
#define UART_SR_TXFULL  (1U << 4)

/* ========= GPIO device masks ========= */
/* Blackboard GPIO buttons are bank 1 bits 18 and 19 */
#define BT4_BANK        1
#define BT5_BANK        1
#define BT4_MASK        0x00040000U
#define BT5_MASK        0x00080000U

/* RGB LED is bank 0 bits 16..18 */
#define RGB_BANK        0
#define RGB_MASK        0x00070000U

/* 333.33 MHz global timer => 0.5 s ≈ 166,666,667 counts */
#define GTC_HALFSEC_TICKS 166666667U

/* ========= ARM interrupt helpers ========= */
void disable_arm_interrupts(void);
void enable_arm_interrupts(void);
void register_irq_handler(void (*handler)(void *));

/* ========= GIC helpers ========= */
void configure_gic_uart1(void);
void configure_gic_gpio(void);
void configure_gic_gtc(void);

/* ========= UART helpers ========= */
void configure_uart1(void);
void configure_uart1_interrupt(void);
int  uart1_rx_empty(void);
char uart1_read_char(void);
void uart1_write_char(char c);
void uart1_puts(const char *s);
void uart1_clear_rx_interrupt_flag(void);

/* ========= GPIO / LED helpers ========= */
void configure_rgb_led(void);
void rgb_led_on(void);
void rgb_led_off(void);
void configure_button_interrupts(void);
uint32_t get_gpio_int_status(int bank, uint32_t mask);
void clear_gpio_int_status(int bank, uint32_t mask);

/* ========= Timer helpers ========= */
uint64_t gtc_read_count(void);
void start_blink_timer(void);
void stop_blink_timer(void);
void clear_global_timer_interrupt(void);

#endif