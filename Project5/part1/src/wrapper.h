#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Disable ARM interrupts (by writing to the CPSR);
Register your interrupt handler;
Configure the GIC for interrupts from the UART module, interrupt ID 82;
Configure the UART module for interrupt generation;
Enable ARM interrupts (again through the CPSR). */

void configure_uart1(void);

void send_string(char str[]);

void receive_string(char str[]);

void disable_ARM_interrupts();

void register_irq_handler();

void configure_GIC();

void configure_uart1_interrupt();

void enable_arm_interrupts();