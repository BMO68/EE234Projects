#include "uart.h"
#include "interrupt.h"       // GIC functions, accel_buf/accel_rx_count externs, pulls in spi.h
#include "gtc_interrupt.h"   // configure_gtc_interrupt, GTC register macros
#include "xil_exception.h"
#include <stdint.h>

#define SLCR_LOCK       (*(volatile uint32_t *)0xF8000004)
#define SLCR_UNLOCK     (*(volatile uint32_t *)0xF8000008)
#define SLCR_SPI_RST    (*(volatile uint32_t *)0xF800021C)
#define UNLOCK_KEY      0xDF0D
#define LOCK_KEY        0x767B
#define WHO_AM_I_REG    0x0F
volatile uint8_t accel_buf[6];
volatile int accel_rx_count = 0;

void my_handler(void);

void reset_SPI() {
    SLCR_UNLOCK = UNLOCK_KEY; //unlock SLCRs
    SLCR_SPI_RST = 0xF;//assert SPI reset
    for (volatile int i = 0; i < 1000; i++);//write 1s to reset, then let some time pass, then write 0s
    SLCR_SPI_RST = 0; //deassert
    SLCR_LOCK = LOCK_KEY; //relock SLCRs
}

void init_SPI0() {
    reset_SPI();

    SPI_ER = 0;// Disable SPI before configuring to prevent undefined behavior while changing stuff

    uint32_t cfg = 0; //local variable to assign bits to rather than writing straight to the register
    cfg |= (1 << 0);     // M = 1, master mode
    cfg |= (1 << 1);     // PL/CPOL = 1, clock polarity = quiescent high / clock idles high
    cfg |= (1 << 2);     // PH/CPHA = 1, clock phase = data is captured on next edge
    cfg |= (4 << 3);     // BAUDDIV = 4,  Clock divided by 2^(N+1), ~5.2MHz
    cfg |= (0 << 8);     // CK = 0, use SPI reference clock (166MHz)
    cfg |= (0 << 9);     // ED = 0  no external decoder
    cfg |= (SS_NONE << 10); // SS = 1111, slave selects, no slave selected, deasserts all slave chip-selects
    cfg |= (1 << 14);    // CS = 1  enable manual chip select
    cfg |= (0 << 15);    // EN = 0  manual start enable, auto-send data placed in fifo
    cfg |= (0 << 16);    // MS = 0  manual start command, no manual start pulse/bit
    cfg |= (1 << 17);    // MF = 1  enable mode-fail detection (in slave mode, indicates if SS was deasserted mid-transfer)

    SPI_CR = cfg; //assign cfg bits to the SPI_CR register

    SPI_ER = 1; //enable the SPI controller

    // Flush RX FIFO before enabling interrupt
    while (SPI_SR & (1 << 4)) {
        volatile uint32_t discard = SPI_RXD;
    }

    SPI_IER = (1 << 4);   // enable RX NOT EMPTY
}

// takes a slave select value, a register address, and perfomrs a 16-bit SPI read (as required by the LSM9DS1) and returns 1 byte
uint16_t spi_read16(uint32_t ss, uint8_t reg) {

	// Assert SS. writing 1110 selects SS0: accelerometer/gyro signal, writing 1101 selects SS1: magnetometer
    SPI_CR = (SPI_CR & ~(0xF << 10)) | (ss << 10);

    // move data through the SPI registers by writing the read/write bit, register addrtess
    uint8_t cmd = 0x80 | (reg & 0x7F);

    // the spi fifo must not be full before writing
    wait_tx_not_full();
    //writing to txd pushes the byte into the transmit fifo
    SPI_TXD = cmd;

    wait_tx_not_full();
    SPI_TXD = 0x00;   // write 0x00 as a blank 16th bit

    // Read two bytes
    wait_rx_not_empty();
    volatile uint8_t throwaway = SPI_RXD;  // during the first 8 clicks, the slave is receiving. it cannot output data yet. this byte is garbage

    wait_rx_not_empty();
    uint8_t data = SPI_RXD; //read the register data we want

    // Deassert SS (write 1111)
    SPI_CR = (SPI_CR & ~(0xF << 10)) | (SS_NONE << 10);

    return data;
}

uint32_t acc_gyro_read(uint32_t address) {
    return spi_read16(SS_AG, address); //call spi_read16() with SS0
}

uint32_t mag_read(uint32_t address) {
    return spi_read16(SS_MAG, address); //call spi_read16() with SS1
}

//write R/W = 0, send register address, send data
void spi_write16(uint32_t ss, uint8_t reg, uint8_t data) {

    // Assert SS
    SPI_CR = (SPI_CR & ~(0xF << 10)) | (ss << 10);

    // First byte: R/W = 0 + register address
    uint8_t cmd = reg & 0x7F;

    wait_tx_not_full();
    SPI_TXD = cmd;

    wait_tx_not_full();
    SPI_TXD = data;

    // Read and discard two RX bytes
    wait_rx_not_empty();
    volatile uint8_t throwaway1 = SPI_RXD;

    wait_rx_not_empty();
    volatile uint8_t throwaway2 = SPI_RXD;

    // Deassert SS
    SPI_CR = (SPI_CR & ~(0xF << 10)) | (SS_NONE << 10);
}

int main(void)
{
    disable_arm_interrupts();

    configure_uart1();
    init_SPI0();

    spi_write16(SS_AG, 0x10, 0x60);   // enable gyro
    spi_write16(SS_AG, 0x20, 0x60);   // enable accel
    spi_write16(SS_MAG, 0x22, 0x00);  // enable magnetometer

    configure_GIC_interrupt58();   // SPI RX
    configure_GIC_interrupt27();   // GTC

    configure_gtc_interrupt();     // 1 Hz timer

    // Register my_handler as the IRQ exception handler so my_handler is called
    Xil_ExceptionRegisterHandler(5, my_handler,NULL);
    enable_arm_interrupts();

    while (1) {
    }
}

void my_handler(void)
{
    uint32_t int_id = ICCIAR & 0x3FF;

    if (int_id == 27) {
        service_gtc_int();
    } else if (int_id == 58) {
        service_spi_int();
    } else if (int_id == 82) {
        service_uart1_int();
    }

    ICCEOIR = int_id;
}
