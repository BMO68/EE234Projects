#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "xil_exception.h"


/* Disable ARM interrupts (by writing to the CPSR);
Register your interrupt handler;
Configure the GIC for interrupts from the UART module, interrupt ID 82;
Configure the UART module for interrupt generation;
Enable ARM interrupts (again through the CPSR). */

//definitions for GIC configuration regisjters
#define ICCPMR	*((uint32_t *) 0xF8F00104)	//Priority mask reg
#define ICCICR	*((uint32_t *) 0xF8F00100)	//CPU interface control reg
#define ICDDCR	*((uint32_t *) 0xF8F01000)	//Distributor Control reg
#define ICDISER(n)	*(((uint32_t *) 0xF8F01100) + n )	//Int. set enable reg
#define ICDICER(n)	*(((uint32_t *) 0xF8F01180) + n )	//Int. Clear Enable reg
#define ICDIPR(n)	*(((uint32_t *) 0xF8F01400) + n )	//Int. Priority reg
#define ICDIPTR(n)	*(((uint32_t *) 0xF8F01800) + n )	//Int. Processor Targets reg
#define ICDICFR(n)	*(((uint32_t *) 0xF8F01C00) + n )	//Int. Configuration reg
#define ICCIAR *((uint32_t *) 0xF8F0010C)
#define ICCEOIR *((uint32_t *) 0xF8F00110)

//uart1 control register
#define UART1_CR *((uint32_t*)0xE0001000)

//uart1 mode register
#define UART1_MR *((uint32_t*)0xE0001004)
#define UART1_BAUDGEN *((uint32_t*)0xE0001018)
#define UART1_BAUDDIV *((uint32_t*)0xE0001034)
//pointer to UART FIFO
#define UART1_FIFO *((uint32_t*)0xE0001030)


void configure_uart1(void);

void send_string(char str[]);

void receive_string(char str[]);

void disable_ARM_interrupts();

void register_irq_handler();

void configure_GIC();

void configure_uart1_interrupt();

void enable_arm_interrupts();

void read_and_send_character();