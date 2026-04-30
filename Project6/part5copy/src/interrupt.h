#ifndef INTERRUPTS
#define INTERRUPTS

#include <stdint.h>

// General Interrupt Controller (GIC) CPU interface registers
#define ICCPMR      *((volatile uint32_t *) 0xF8F00104)   // Priority mask
#define ICCICR      *((volatile uint32_t *) 0xF8F00100)   // CPU interface control
#define ICCIAR      *((volatile uint32_t *) 0xF8F0010C)   // Interrupt acknowledge
#define ICCEOIR     *((volatile uint32_t *) 0xF8F00110)   // End of interrupt

#define ICDDCR      *((volatile uint32_t *) 0xF8F01000) //   GIC distributor registers
#define ICDISER(n)  *(((volatile uint32_t *) 0xF8F01100) + (n))   // Set-enable
#define ICDICER(n)  *(((volatile uint32_t *) 0xF8F01180) + (n))   // Clear-enable
#define ICDIPR(n)   *(((volatile uint32_t *) 0xF8F01400) + (n))   // Priority
#define ICDIPTR(n)  *(((volatile uint32_t *) 0xF8F01800) + (n))   // Target CPU
#define ICDICFR(n)  *(((volatile uint32_t *) 0xF8F01C00) + (n))   // Configuration

#define UART1_ISR   *((volatile uint32_t *) 0xE0001014)

void disable_arm_interrupts(void);
void enable_arm_interrupts(void);

void configure_GIC_interrupt27(void);    // ID 27 = Global Timer
void configure_GIC_interrupt80(void);    // ID 80 = I2C1

// ISR service routines are called from my_handler in main
void service_gtc_int(void);              // defined in gtc_interrupt.c
void service_i2c_int(void);              // defined in interrupt.c

#endif