#include "wrapper.h"

static void delay_cycles(volatile uint32_t count);

static void delay_cycles(volatile uint32_t count)
{
    while (count--) {;}
}

/* ---------------- UART1 ---------------- */

void conf_uart1_115200(void)
{
    UART1_CR = 0x03;              /* reset TX/RX */
    while (UART1_CR & 0x03) {;}

    UART1_MR = 0x20;              /* 8-bit, no parity, 1 stop */
    UART1_BAUDGEN = BGEN_115200;
    UART1_BAUDDIV = BDIV_115200;
    UART1_CR = 0x14;              /* enable TX and RX */
}

void putc_uart1(char c)
{
    while (UART1_SR & 0x10U) {;}  /* wait while TX FIFO full */
    UART1_FIFO = (uint32_t)c;
}

void putst_uart1(const char *s)
{
    while (*s != '\0')
    {
        putc_uart1(*s++);
    }
}

static char nibble_to_hex(uint8_t val)
{
    val &= 0xF;
    return (val > 9) ? (char)(val + ('A' - 10)) : (char)(val + '0');
}

void byte_to_hex_str(uint8_t val, char *str)
{
    str[0] = nibble_to_hex((val >> 4) & 0xF);
    str[1] = nibble_to_hex(val & 0xF);
    str[2] = '\0';
}

/* ---------------- SPI0 ---------------- */

void reset_SPI0(void)
{
    SLCR_UNLOCK = UNLOCK_KEY;
    SLCR_SPI_RST = 0x0000000F;
    delay_cycles(2000);
    SLCR_SPI_RST = 0x00000000;
    SLCR_LOCK = LOCK_KEY;
}

static void spi_flush_rx(void)
{
    while (SPI0_SR & SPI_SR_RN)
    {
        (void)SPI0_RXD;
    }
}

void init_SPI0(void)
{
    SPI0_ER = 0x00;

    SPI0_CR =
        SPI_CR_MSTREN |
        SPI_CR_CPOL |
        SPI_CR_CPHA |
        SPI_CR_BAUDDIV_4 |
        SPI_CR_SS_NONE;

    SPI0_ER = 0x01;
    spi_flush_rx();
}

static uint8_t spi_read_two_byte_transaction(uint8_t cmd, uint32_t ss_bits)
{
    uint8_t junk, data;
    volatile int timeout;

    spi_flush_rx();

    SPI0_CR = (SPI0_CR & ~SPI_CR_SS_MASK) | ss_bits;

    timeout = 1000000;
    while (!(SPI0_SR & SPI_SR_TN) && --timeout) {;}
    if (timeout == 0) return 0xFF;
    SPI0_TXD = cmd;

    timeout = 1000000;
    while (!(SPI0_SR & SPI_SR_TN) && --timeout) {;}
    if (timeout == 0) return 0xFF;
    SPI0_TXD = 0x00;

    timeout = 1000000;
    while (!(SPI0_SR & SPI_SR_RN) && --timeout) {;}
    if (timeout == 0) return 0xFF;
    junk = (uint8_t)SPI0_RXD;

    timeout = 1000000;
    while (!(SPI0_SR & SPI_SR_RN) && --timeout) {;}
    if (timeout == 0) return 0xFF;
    data = (uint8_t)SPI0_RXD;

    SPI0_CR = (SPI0_CR & ~SPI_CR_SS_MASK) | SPI_CR_SS_NONE;

    (void)junk;
    return data;
}

uint8_t acc_gyro_read(uint8_t address)
{
    /* bit7 = read, bits6:0 = address */
    uint8_t cmd = (uint8_t)(0x80U | (address & 0x7FU));
    return spi_read_two_byte_transaction(cmd, SPI_CR_SS0);
}

uint8_t mag_read(uint8_t address)
{
    /* bit7 = read, bit6 = auto-increment (0 here), bits5:0 = address */
    uint8_t cmd = (uint8_t)(0x80U | (address & 0x3FU));
    return spi_read_two_byte_transaction(cmd, SPI_CR_SS1);
}