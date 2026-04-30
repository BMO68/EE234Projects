#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdint.h>

/*----------------------------SPI Stuff---------------------------*/
#define SPI0_BASE       0xE0006000
#define SPI_CR          (*(volatile uint32_t *)(SPI0_BASE + 0x00))//configuration register
#define SPI_SR          (*(volatile uint32_t *)(SPI0_BASE + 0x04))//interrupt status register (FIFO)
#define SPI_IER         (*(volatile uint32_t *)(SPI0_BASE + 0x08))//enable interrupt sources
#define SPI_IDR         (*(volatile uint32_t *)(SPI0_BASE + 0x0C))//disable interrupt sources
#define SPI_IMR         (*(volatile uint32_t *)(SPI0_BASE + 0x10))//mask bits for interrupt sources
#define SPI_ER          (*(volatile uint32_t *)(SPI0_BASE + 0x14))//spi controller eable
#define SPI_DR          (*(volatile uint32_t *)(SPI0_BASE + 0x18))//set various intra-frame delays
#define SPI_TXD         (*(volatile uint32_t *)(SPI0_BASE + 0x1C))//spi write data (fifo)
#define SPI_RXD         (*(volatile uint32_t *)(SPI0_BASE + 0x20))//spi read data (fifo)

// reset the spi module by writing to zynq's system level control registers block
//SLCRs are protected registers that can only be accessed after they are "unlocked"
#define SLCR_LOCK       (*(volatile uint32_t *)0xF8000004)
#define SLCR_UNLOCK     (*(volatile uint32_t *)0xF8000008)
#define SLCR_SPI_RST    (*(volatile uint32_t *)0xF800021C)
#define UNLOCK_KEY      0xDF0D
#define LOCK_KEY        0x767B

// LSM9DS1 register
#define WHO_AM_I_REG    0x0F //ID register returns 0x68

// Slave select encodings for SPI_CR[13:10]
#define SS_NONE  0xF
#define SS_AG    0xE   // accelerometer/gyro (SS0)
#define SS_MAG   0xD   // magnetometer (SS1)

/*----------------------------UART Stuff---------------------------*/
#include <stdio.h>
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