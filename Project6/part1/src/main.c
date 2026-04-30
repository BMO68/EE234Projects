#include "wrapper.h"

int main() {
    configure_uart1();
    init_SPI0();

    uint32_t who_ag  = acc_gyro_read(WHO_AM_I_REG); //read from SS0
    uint32_t who_mag = mag_read(WHO_AM_I_REG); //read from SS1

    uart1_sendstr("A/G WHO_AM_I = 0x");
    uart1_sendchar("0123456789ABCDEF"[(who_ag >> 4) & 0xF]);
    uart1_sendchar("0123456789ABCDEF"[who_ag & 0xF]);
    uart1_sendstr("\r\n");

    uart1_sendstr("MAG WHO_AM_I = 0x");
    uart1_sendchar("0123456789ABCDEF"[(who_mag >> 4) & 0xF]);
    uart1_sendchar("0123456789ABCDEF"[who_mag & 0xF]);
    uart1_sendstr("\r\n");

    while (1);
}