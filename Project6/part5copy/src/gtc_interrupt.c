#include "gtc_interrupt.h"
#include "interrupt.h"
#include "i2c.h"
#include "uart.h"
#include <stdint.h>

// Configure the Global Timer to fire an interrupt once per second
void configure_gtc_interrupt(void)
{
    // Step 1: stop timer and clear all control bits
    GTCTRL = 0;

    // Step 2: read current 64-bit counter value
    uint32_t lo = GTCR0;
    uint32_t hi = GTCR1;

    // Step 3: set comparator to current time + 1 second
    uint64_t current = ((uint64_t)hi << 32) | lo;
    uint64_t compare = current + GTC_TICKS_PER_SECOND;

    GTCVR0 = (uint32_t)(compare & 0xFFFFFFFF);
    GTCVR1 = (uint32_t)(compare >> 32);

    // Step 4: auto-increment by 1 second
    GTAIR = GTC_TICKS_PER_SECOND;

    // Step 5: enable timer, comparator, IRQ, and auto-increment
    GTCTRL = GTC_ENABLE | GTC_COMP_ENABLE | GTC_IRQ_ENABLE | GTC_AUTOINC;
}

// GTC ISR called every second by irq_handler
// Kicks off a 2-byte I2C read from the LM75B.
// Data handling is in service_i2c_int when the I2C COMP interrupt fires.
void service_gtc_int(void)
{
    uart1_sendstr("GTC fired - starting I2C read\r\n");

    i2c1_start_read();

    // Clear the GTC interrupt flag so it can fire again
    GTIS = 0x1;
}