#ifndef WRAPPER_H
#define WRAPPER_H

#include <stdint.h>

/* ---------------- UART1 ---------------- */
#define UART1_BASE      0xE0001000U
#define UART1_CR        (*(volatile uint32_t *)(UART1_BASE + 0x00))
#define UART1_MR        (*(volatile uint32_t *)(UART1_BASE + 0x04))
#define UART1_BAUDGEN   (*(volatile uint32_t *)(UART1_BASE + 0x18))
#define UART1_SR        (*(volatile uint32_t *)(UART1_BASE + 0x2C))
#define UART1_FIFO      (*(volatile uint32_t *)(UART1_BASE + 0x30))
#define UART1_BAUDDIV   (*(volatile uint32_t *)(UART1_BASE + 0x34))

#define BGEN_115200     0x7C
#define BDIV_115200     6

/* ---------------- SLCR / SPI0 ---------------- */
#define SLCR_LOCK       (*(volatile uint32_t *)0xF8000004)
#define SLCR_UNLOCK     (*(volatile uint32_t *)0xF8000008)
#define SLCR_SPI_RST    (*(volatile uint32_t *)0xF800021C)

#define UNLOCK_KEY      0x0000DF0D
#define LOCK_KEY        0x0000767B

#define SPI0_BASE       0xE0006000U
#define SPI0_CR         (*(volatile uint32_t *)(SPI0_BASE + 0x00))
#define SPI0_SR         (*(volatile uint32_t *)(SPI0_BASE + 0x04))
#define SPI0_ER         (*(volatile uint32_t *)(SPI0_BASE + 0x14))
#define SPI0_TXD        (*(volatile uint32_t *)(SPI0_BASE + 0x1C))
#define SPI0_RXD        (*(volatile uint32_t *)(SPI0_BASE + 0x20))

/* SPI status bits */
#define SPI_SR_RN           (1U << 4)   /* RX FIFO not empty */
#define SPI_SR_TN           (1U << 2)   /* TX FIFO not full  */

/* SPI control bits */
#define SPI_CR_MSTREN       (1U << 0)
#define SPI_CR_CPOL         (1U << 1)
#define SPI_CR_CPHA         (1U << 2)
#define SPI_CR_BAUDDIV_4    (4U << 3)
#define SPI_CR_SS_MASK      (0xFU << 10)
#define SPI_CR_SS_NONE      (0xFU << 10)
#define SPI_CR_SS0          (0xEU << 10)   /* 1110 selects slave 0 */
#define SPI_CR_SS1          (0xDU << 10)   /* 1101 selects slave 1 */
#define SPI_CR_MANSTRTEN    (1U << 15)
#define SPI_CR_MANSTRT      (1U << 16)

/* LSM9DS1 register addresses */
#define WHO_AM_I_ADDR       0x0F

void conf_uart1_115200(void);
void putc_uart1(char c);
void putst_uart1(const char *s);
void byte_to_hex_str(uint8_t val, char *str);

void reset_SPI0(void);
void init_SPI0(void);
uint8_t acc_gyro_read(uint8_t address);
uint8_t mag_read(uint8_t address);

#endif