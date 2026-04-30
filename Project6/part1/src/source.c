
#include "wrapper.h"

/*-------------------------------SPI Stuff---------------------------------*/
void wait_tx_not_full(void) {
    while ((SPI_SR & (1 << 2)) == 0);   // TN bit
}

void wait_rx_not_empty(void) {
    while ((SPI_SR & (1 << 4)) == 0);   // RN bit
}

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
    cfg |= (1 << 2);     // PH/CPHA
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

    SPI_CR = (SPI_CR & ~(0xF << 10)) | (ss << 10);

    uint8_t cmd = 0x80 | (reg & 0x7F);

    wait_tx_not_full();

    SPI_TXD = cmd;

    wait_tx_not_full();
    SPI_TXD = 0x00;

    // Read two bytes
    wait_rx_not_empty();
    volatile uint8_t throwaway = SPI_RXD;

    wait_rx_not_empty();
    uint8_t data = SPI_RXD;

    SPI_CR = (SPI_CR & ~(0xF << 10)) | (SS_NONE << 10);

    return data;
}

uint32_t acc_gyro_read(uint32_t address) {
    return spi_read16(SS_AG, address);
}

uint32_t mag_read(uint32_t address) {
    return spi_read16(SS_MAG, address);
}

/*-------------------------------UART Stuff-----------------------------*/

void configure_uart1(){
    uint32_t *datapath;

    datapath = (uint32_t *)UART1_MR;
    *datapath = 0x00000020;

    datapath = (uint32_t *)UART1_CR;
    *datapath = (1 <<8 ) | (1 << 9);
    *datapath = (1 << 4) | (1 << 2) | (1 <<0);

    datapath = (uint32_t *)UART1_BAUDGEN;
    *datapath = 124;

    datapath = (uint32_t *)UART1_BAUDDIV;
    *datapath = 6;
}

char uart1_getchar(){
    uint32_t *datapath;
    uint32_t temp_data;

    do{
        datapath = (uint32_t *)UART1_SR;
        temp_data = *datapath;
        temp_data &= 2;
    } while(temp_data == 2);

    datapath = (uint32_t *)UART1_FIFO;
    temp_data = *datapath;
    return temp_data;
}

void uart1_sendchar(char data){
    uint32_t *datapath;
    uint32_t temp_data;

    do {
        datapath = (uint32_t *)UART1_SR;
        temp_data = *datapath;
        temp_data &= 16;
    } while(temp_data == 16);

    datapath = (uint32_t *)UART1_FIFO;
    *datapath = data;
}

void uart1_sendstr(char buffer[]){
    int i = 0;
    while(buffer[i] != '\0'){
        uart1_sendchar(buffer[i]);
        i++;
    }
}

int uart1_getln(char buffer[], int max){
    int i = 0;
    char ch;
    while(i < max - 1){
        ch = uart1_getchar();
        if(ch == '\n' || ch == '\r'){
            break;
        }
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
    return i;
}

void uart1_sendint(int value) {
    char buffer[12];
    int i = 0;

    if (value == 0) {
        uart1_sendchar('0');
        return;
    }
    
    if (value < 0) {
        uart1_sendchar('-');
        value = -value;
    }

    while (value > 0 && i < sizeof(buffer)) {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    while (i > 0) {
        uart1_sendchar(buffer[--i]);
    }
}