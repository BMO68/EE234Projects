#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define LED_CTL			0x4BB00000
#define UART1_CR		0xE0001000
#define UART1_MR		0xE0001004
#define UART1_BAUDGEN	0xE0001018
#define UART1_BAUDDIV	0xE0001034
#define UART1_SR 		0xE000102C
#define UART1_FIFO		0xE0001030
#define UART1_IER *((volatile uint32_t *) 0xE0001008)  // Interrupt Enable Register
#define UART1_RXTG *((volatile uint32_t *) 0xE0001020)  // RX Trigger Register

#define UART1_INT_ID 82

extern void reset_uart1();

void configure_uart1();

char uart1_getchar();

void uart1_sendchar(char data);

void uart1_sendstr(char buffer[]);

int uart1_getln(char buffer[], int max);

void uart1_sendint(int value);

#endif