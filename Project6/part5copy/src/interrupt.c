#include "interrupt.h"
#include "i2c.h"
#include "uart.h"
#include <stdint.h>

void disable_arm_interrupts(void)
{
    uint32_t cpsr_val = 0;
    asm("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val |= 0xC0;               // set bits 6 (FIQ) and 7 (IRQ)
    asm("msr cpsr, %0" : : "r"(cpsr_val));
}

void enable_arm_interrupts(void)
{
    uint32_t cpsr_val = 0;
    asm("mrs %0, cpsr" : "=r"(cpsr_val));
    cpsr_val &= ~0xC0;              // clear bits 6 and 7
    asm("msr cpsr, %0" : : "r"(cpsr_val));
}

static void disable_gic_dist(void)      { ICDDCR = 0; }
static void enable_gic_dist(void)       { ICDDCR = 1; }
static void disable_IRQ_passthrough(void) { ICCICR = 0; }
static void enable_IRQ_passthrough(void)  { ICCICR = 1; }

void configure_GIC_interrupt27(void)
{
    disable_gic_dist();
    disable_IRQ_passthrough();

    ICCPMR = 0xFF;                  // accept all priority levels

    ICDICER(0)  =  0x08000000;      // disable ID 27 while configuring

    ICDIPR(6)  &= ~0xFF000000;      // clear priority bits [31:24]
    ICDIPR(6)  |=  0xA0000000;      // priority 0xA0, top 5 bits only

    ICDISER(0)  =  0x08000000;      // enable ID 27

    enable_gic_dist();
    enable_IRQ_passthrough();
}

void configure_GIC_interrupt80(void)
{
    disable_gic_dist();
    disable_IRQ_passthrough();

    ICCPMR = 0xFF;

    // Disable ID 80 while configuring
    ICDIPTR(20) &= ~0x000000FF;     // clear CPU target for ID 80
    ICDICER(2)   =  0x00010000;     // disable ID 80 in distributor

    // Set priority to 0xA0 (same as GTC, no preference between them)
    ICDIPR(20)  &= ~0x000000FF;
    ICDIPR(20)  |=  0x000000A0;     // bits [7:0] for ID 80

    // Route to CPU0
    ICDIPTR(20) |=  0x00000001;     // bits [7:0] -> CPU0

    // Level-sensitive (I2C interrupt is a level signal, not an edge)
    ICDICFR(5)  &= ~0x00000003;     // bits [1:0] for ID 80 = 0b00 (level)

    // Enable ID 80
    ICDISER(2)   =  0x00010000;

    enable_gic_dist();
    enable_IRQ_passthrough();
}

// I2C ISR is called when COMP fires (2 bytes received)
// Reads both bytes from the RX FIFO, converts, sends over UART
void service_i2c_int(void)
{
    // Read both bytes out of the RX FIFO
	//i2c_rx_buf is a 2-byte array that acts as a buffer between the 11-bit reading and the celsius output
    i2c_rx_buf[0] = (uint8_t)(I2C_DATA & 0xFFu);
    i2c_rx_buf[1] = (uint8_t)(I2C_DATA & 0xFFu);
    i2c_rx_ready  = 1;

    // Convert temperature
    int temp_mC = raw_to_temp_mC();

    //Print
    uart1_sendstr("Temp = ");

    if (temp_mC < 0) {
        uart1_sendchar('-');
        temp_mC = -temp_mC;
    }

    int whole = temp_mC / 1000;
    int frac  = temp_mC % 1000;

    uart1_sendint(whole);
    uart1_sendchar('.');
    uart1_sendchar('0' + (frac / 100));
    uart1_sendchar('0' + ((frac / 10) % 10));
    uart1_sendchar('0' + (frac % 10));
    uart1_sendstr(" C\r\n");

    // Clear I2C interrupt flags
    I2C_ISR = 0xFFFFFFFFu;
}