#include "gtc_interrupt.h"
#include "uart.h"
#include "interrupt.h"
#include <stdio.h>
#include <stdint.h>

// configure the Global Timer to fire an interrupt once per second
void configure_gtc_interrupt(void)
{
    // Step 1: Stop the timer and clear all control bits
    GTCTRL = 0;

    // Step 2: Read the current GTC 64-bit counter value and but them in a ZYNQ 32-bit register
    uint32_t lo = GTCR0;
    uint32_t hi = GTCR1;

    // Step 3: Read the current time, add one second, write that time back
    uint64_t current  = ((uint64_t)hi << 32) | lo; //put hi and lo together as a single 64-nit number
    uint64_t compare  = current + GTC_TICKS_PER_SECOND; //calculate when the next interrupt should fire

    //split back to 32-bit chunks
    GTCVR0 = (uint32_t)(compare & 0xFFFFFFFF);
    GTCVR1 = (uint32_t)(compare >> 32);

    // Step 4: Set auto-increment so the comparator advances by one second without needing to go inside the ISR
    GTAIR = GTC_TICKS_PER_SECOND;

    // Step 5: Enable timer, comparator, IRQ, auto-increment
    GTCTRL = GTC_ENABLE | GTC_COMP_ENABLE | GTC_IRQ_ENABLE | GTC_AUTOINC; //OR-ing these together combines them into one value (assigning seperately would cause overwritting)
}

void service_gtc_int(void) //completely replaced for proj6
{
    uart1_sendstr("GTC fired\r\n");

    // discard any stale bytes left in the RX FIFO from the previous transaction
   while (SPI_SR & (1 << 4)) {
        volatile uint32_t discard = SPI_RXD;
        }
    // Start a multi-byte accel read: OUT_X_XL_L, auto-increment
    uint8_t cmd = 0x80 | 0x40 | 0x28;   // READ + AUTO-INCR + OUT_X_XL_L

    accel_rx_count = 0;                 // reset RX counter

    // Assert SS for A/G
    SPI_CR = (SPI_CR & ~(0xF << 10)) | (SS_AG << 10);

    // Send command byte
    wait_tx_not_full();
    SPI_TXD = cmd;

    // Queue 6 dummy bytes to clock out X_L, X_H, Y_L, Y_H, Z_L, Z_H
    for (int i = 0; i < 6; i++) {
        wait_tx_not_full();
        SPI_TXD = 0x00;
    }

    // Clear GTC interrupt flag
    GTIS = 0x1;
}

void gtc_start(void)
{
    // read the current counter value
    uint32_t lo = GTCR0;
    uint32_t hi = GTCR1;
    uint64_t current = ((uint64_t)hi << 32) | lo;

    //calculate when the first interrupt should fire
    uint64_t compare = current + (GTC_TICKS_PER_SECOND / 2); // the /2 makes it so the interrupt fires every 500ms rather than 1s

    GTCVR0 = (uint32_t)(compare & 0xFFFFFFFF);
    GTCVR1 = (uint32_t)(compare >> 32);
    GTAIR  = GTC_TICKS_PER_SECOND / 2;     // auto-increment by 500ms

    GTCTRL = GTC_ENABLE | GTC_COMP_ENABLE | GTC_IRQ_ENABLE | GTC_AUTOINC;
}

void gtc_stop(void)
{
    GTCTRL &= ~GTC_IRQ_ENABLE;  // clear the IRQ enable bit, leave timer running
}