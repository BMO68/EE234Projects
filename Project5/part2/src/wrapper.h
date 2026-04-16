#ifndef WRAPPER_H
#define WRAPPER_H

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

/* ========= GPIO registers ========= */
#define GPIO_DATA(n)        (*(((volatile uint32_t *) 0xE000A040) + (n)))
#define GPIO_DATA_RO(n)     (*(((volatile uint32_t *) 0xE000A060) + (n)))
#define GPIO_DIRM(n)        (*(((volatile uint32_t *) 0xE000A204) + 16*(n)))
#define GPIO_OEN(n)         (*(((volatile uint32_t *) 0xE000A208) + 16*(n)))

#define GPIO_INT_MASK(n)    (*(((volatile uint32_t *) 0xE000A20C) + 16*(n)))
#define GPIO_INT_EN(n)      (*(((volatile uint32_t *) 0xE000A210) + 16*(n)))
#define GPIO_INT_DIS(n)     (*(((volatile uint32_t *) 0xE000A214) + 16*(n)))
#define GPIO_INT_STAT(n)    (*(((volatile uint32_t *) 0xE000A218) + 16*(n)))
#define GPIO_INT_TYPE(n)    (*(((volatile uint32_t *) 0xE000A21C) + 16*(n)))
#define GPIO_INT_POL(n)     (*(((volatile uint32_t *) 0xE000A220) + 16*(n)))
#define GPIO_INT_ANY(n)     (*(((volatile uint32_t *) 0xE000A224) + 16*(n)))

/* ========= Project-specific constants ========= */
#define GPIO_INT_ID     52U

/* RGB LED is bank 0, bits 16-18 */
#define RGB_BANK        0
#define RGB_MASK        0x70000U

/* Blackboard pushbuttons used in the references */
#define BT4_BANK        1
#define BT5_BANK        1
#define BT4_MASK        0x40000U   /* bank 1, bit 18 */
#define BT5_MASK        0x80000U   /* bank 1, bit 19 */

/* ========= Function prototypes ========= */
void disable_arm_interrupts(void);
void enable_arm_interrupts(void);

void register_irq_handler(void (*handler)(void *));
void configure_gic_gpio_interrupt(void);

void configure_rgb_led(void);
void rgb_led_on(void);
void rgb_led_off(void);

void configure_button_interrupts(void);
uint32_t get_gpio_int_status(int bank, uint32_t mask);
void clear_gpio_int_status(int bank, uint32_t mask);

#endif