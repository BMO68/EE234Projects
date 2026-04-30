#include "uart.h"
#include "spi.h"

void reset_SPI() {
    SLCR_UNLOCK = UNLOCK_KEY;
    SLCR_SPI_RST = 0xF;
    for (volatile int i = 0; i < 1000; i++);
    SLCR_SPI_RST = 0;
    SLCR_LOCK = LOCK_KEY;
}

void init_SPI0() {
    reset_SPI();

    SPI_ER = 0;

    uint32_t cfg = 0;
    cfg |= (1 << 0);     // M = 1
    cfg |= (1 << 1);     // PL/CPOL = 1
    cfg |= (1 << 2);     // PH/CPHA = 1
    cfg |= (4 << 3);     // BAUDDIV = 4
    cfg |= (0 << 8);     // CK = 0
    cfg |= (0 << 9);     // ED = 0
    cfg |= (SS_NONE << 10); // SS = 1111
    cfg |= (1 << 14);    // CS = 1
    cfg |= (0 << 15);    // EN = 0
    cfg |= (0 << 16);    // MS = 0
    cfg |= (1 << 17);    // MF = 1

    SPI_CR = cfg;

    SPI_ER = 1;
}

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

int16_t read_axis(uint32_t ss, uint8_t low_addr) {
    uint8_t lo = spi_read16(ss, low_addr);
    uint8_t hi = spi_read16(ss, low_addr + 1);
    return (int16_t)((hi << 8) | lo);
}

int main() {
    configure_uart1();
    init_SPI0();

    // Enable gyro, accel, and magnetometer
    spi_write16(SS_AG, 0x10, 0x60);   // CTRL_REG1_G, gyro data rate, full-scale, and bandwidth selection
    spi_write16(SS_AG, 0x20, 0x60);   // CTRL_REG6_XL, data rate, full-scale, bandwidth, and filter selection
    spi_write16(SS_MAG, 0x22, 0x00);  // CTRL_REG3_M, gyro data rate, full-scale, and bandwidth selection

    while (1) {
        int16_t gx = read_axis(SS_AG, 0x18); //OUT_X_G, angular rate sensor pitch axis, 16-bit 2's compliment
        int16_t gy = read_axis(SS_AG, 0x1A); //OUT_Y_G, angular rate sensor roll axis, 16-bit 2's compliment
        int16_t gz = read_axis(SS_AG, 0x1C); //OUT_Z_G, angular rate sensor yaw axis, 16-bit 2's compliment

        int16_t ax = read_axis(SS_AG, 0x28); //OUT_X_G, linear acceleration x axis, 16-bit 2's compliment
        int16_t ay = read_axis(SS_AG, 0x2A); //OUT_Y_G, linear acceleration y axis, 16-bit 2's compliment
        int16_t az = read_axis(SS_AG, 0x2C); //OUT_Z_G, linear acceleration z axis, 16-bit 2's compliment

        int16_t mx = read_axis(SS_MAG, 0x28); //OUT_X_M, magnetometer x axis, 16-bit 2's compliment
        int16_t my = read_axis(SS_MAG, 0x2A);
        int16_t mz = read_axis(SS_MAG, 0x2C);

        uart1_sendstr("G: ");
        uart1_sendint(gx); uart1_sendstr(" ");
        uart1_sendint(gy); uart1_sendstr(" ");
        uart1_sendint(gz); uart1_sendstr("\r\n");

        uart1_sendstr("A: ");
        uart1_sendint(ax); uart1_sendstr(" ");
        uart1_sendint(ay); uart1_sendstr(" ");
        uart1_sendint(az); uart1_sendstr("\r\n");

        uart1_sendstr("M: ");
        uart1_sendint(mx); uart1_sendstr(" ");
        uart1_sendint(my); uart1_sendstr(" ");
        uart1_sendint(mz); uart1_sendstr("\r\n\r\n");

        for (volatile int i = 0; i < 5000000; i++); // small delay
    }
}