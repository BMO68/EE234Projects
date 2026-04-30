#include <stdint.h>
#include "uart.h"
#include "i2c.h"
#include "interrupt.h"
#include "gtc_interrupt.h"
#include "xil_exception.h"

void my_handler(void);

int main(void)
{
    // Step 1: disable ARM interrupts while configuring everything
    disable_arm_interrupts();

    // Step 2: configure UART for terminal output
    configure_uart1();
    uart1_sendstr("Part 5 - Interrupt-driven I2C Temperature Sensor\r\n");

    // Step 3: configure I2C1 controller
    i2c1_init();

    // Step 4: configure GIC for ID 27 (Global Timer) and ID 80 (I2C1)
    configure_GIC_interrupt27();
    configure_GIC_interrupt80();

    // Step 5: enable the COMP interrupt inside the I2C controller (ISR bit 0 for transfer complete)
    i2c1_enable_comp_interrupt();

    // Step 6: configure the Global Timer to fire every second
    configure_gtc_interrupt();

    // Step 7: enable ARM interrupts
    Xil_ExceptionRegisterHandler(5, my_handler,NULL);
    enable_arm_interrupts();
    uart1_sendstr("Interrupts enabled - temperature prints every second\r\n");

    while (1) {
    }

    return 0;
}

// Reads the interrupt ID from ICCIAR, calls the correct service routine,
// then writes ICCEOIR to signal end-of-interrupt
void my_handler(void)
{
    uint32_t int_id = ICCIAR & 0x3FF;   // bits [9:0] = interrupt ID

    switch (int_id) {
        case 27:
            service_gtc_int();           // GTC fires -> initiate I2C read
            break;
        case 80:
            service_i2c_int();           // I2C COMP fires (FIFO is ready) -> send temp over UART
            break;
        default:
            break;
    }

    ICCEOIR = int_id;
}