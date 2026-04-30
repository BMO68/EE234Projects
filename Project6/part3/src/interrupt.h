#ifndef SRC_INTERRUPTS_H_
#define SRC_INTERRUPTS_H_

#include <stdint.h>
#include "spi.h"   // provides SPI_CR, SPI_SR, SPI_RXD, SS_NONE, etc.

#define ICCPMR      *((volatile uint32_t *) 0xF8F00104)
#define ICCICR      *((volatile uint32_t *) 0xF8F00100)
#define ICCIAR      *((volatile uint32_t *) 0xF8F0010C)
#define ICCEOIR     *((volatile uint32_t *) 0xF8F00110)

#define ICDDCR      *((volatile uint32_t *) 0xF8F01000)
#define ICDISER(n)  *(((volatile uint32_t *) 0xF8F01100) + (n))
#define ICDICER(n)  *(((volatile uint32_t *) 0xF8F01180) + (n))
#define ICDIPR(n)   *(((volatile uint32_t *) 0xF8F01400) + (n))
#define ICDIPTR(n)  *(((volatile uint32_t *) 0xF8F01800) + (n))
#define ICDICFR(n)  *(((volatile uint32_t *) 0xF8F01C00) + (n))

// These are defined in part3.c and shared here via extern
extern volatile uint8_t accel_buf[6];
extern volatile int accel_rx_count;

#define UART1_ISR   *((volatile uint32_t *) 0xE0001014)
#define UART1_RXTG  *((volatile uint32_t *) 0xE0001020)

// Forward declarations for helper functions
void disable_gic_dist(void);
void enable_gic_dist(void);
void disable_IRQ_passthrough(void);
void enable_IRQ_passthrough(void);
void set_gic_pmr(uint32_t priority);
void disable_interrupt27(void);
void enable_interrupt27(void);
void set_interrupt27_priority(uint8_t priority_val);
void disable_interrupt52(void);
void enable_interrupt52(void);
void set_interrupt52_priority(uint8_t priority_val);
void set_interrupt52_sensitivity(uint8_t sens);
void disable_interrupt82(void);
void enable_interrupt82(void);
void set_interrupt82_priority(uint8_t priority_val);
void set_interrupt82_sensitivity(uint8_t sens);
void clear_uart1_int_flags(void);

void enable_uart1_byte_rx_int(void);
void set_uart1_rx_trigger(uint32_t n);
void unmask_uart1_rxtg_int(void);

void disable_arm_interrupts(void);
void enable_arm_interrupts(void);

void configure_GIC_interrupt82(void);
void configure_GIC_interrupt58(void);
void configure_GIC_interrupt27(void);

void configure_uart1_interrupt(void);
void service_uart1_int(void);
void service_spi_int(void);

#endif