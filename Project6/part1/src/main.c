#include "wrapper.h"

int main(void)
{
    char hexstr[3];
    uint8_t ag_id, mag_id;

    putst_uart1("before ag read\r\n");
    ag_id = acc_gyro_read(WHO_AM_I_ADDR);
    putst_uart1("after ag read\r\n");

    byte_to_hex_str(ag_id, hexstr);
    putst_uart1("AG WHO_AM_I = 0x");
    putst_uart1(hexstr);
    putst_uart1("\r\n");

    putst_uart1("before mag read\r\n");
    mag_id = mag_read(WHO_AM_I_ADDR);
    putst_uart1("after mag read\r\n");

    byte_to_hex_str(mag_id, hexstr);
    putst_uart1("MAG WHO_AM_I = 0x");
    putst_uart1(hexstr);
    putst_uart1("\r\n");
    while (1) {;}
    return 0;
}