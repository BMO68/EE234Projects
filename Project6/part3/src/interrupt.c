#include "gtc_interrupt.h"
#include "interrupt.h"
#include "uart.h"
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////
//CALLED IN MAIN.C////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void disable_arm_interrupts(void)
{
    uint32_t cpsr_val = 0;
    asm("mrs %0, cpsr" : "=r"(cpsr_val)); //get current cpsr
    cpsr_val |= 0xC0;               // Set bits 6 (FIQ) and 7 (IRQ)
    asm("msr cpsr, %0" : : "r"(cpsr_val)); //writeback modified value

    return;
}

void enable_arm_interrupts(void)
{
    uint32_t cpsr_val = 0;
    asm("mrs %0, cpsr" : "=r"(cpsr_val)); //get current cpsr
    cpsr_val &= ~0xC0;              // Clear bits 6 and 7
    asm("msr cpsr, %0" : : "r"(cpsr_val)); //writeback modified value

    return;
}

void configure_uart1_interrupt(void)
{
    enable_uart1_byte_rx_int();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//TRIGGER FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

//Set trigger to 1 byte so we get an interrupt for every received character, then enable the interrupt at the UART level.
void enable_uart1_byte_rx_int(void)
{
    set_uart1_rx_trigger(1);        // Fire after every single received byte
    unmask_uart1_rxtg_int();        // Enable the RX trigger interrupt in UART1
}

//Set the RX FIFO trigger level.
//The UART fires an interrupt when the number of bytes in the RX FIFO
//reaches or exceeds n bytes.
void set_uart1_rx_trigger(uint32_t n)
{
    UART1_RXTG = n; // RX FIFO Trigger Level
}

//Unmask and enable the RX trigger interrupt in the UART. Bit 0 of IER = RTRIG (receive trigger interrupt enable).
void unmask_uart1_rxtg_int(void)
{
    UART1_IER = 0x01; // Interrupt Enable Register
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
//GIC FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

//GIC sees the signal from UART1 (ID 82), checks that it is enabled and that its priority passes the priority mask, then forwards it to the CPU
void configure_GIC_interrupt82(void)
{
    disable_gic_dist(); //disable gic interrupt generation
    disable_IRQ_passthrough(); //drive irw from gic

    set_gic_pmr(0xFF);              // Accept all priority levels

    disable_interrupt82();          // Disable while configuring

    set_interrupt82_priority(0xA0); // set 82's priority to 160. lower number = higher priority in GIC
    set_interrupt82_sensitivity(1); // Edge-sensitive

    enable_interrupt82();           // Route to CPU0 and reenable

    enable_gic_dist();
    enable_IRQ_passthrough();       // Let interrupts reach the CPU
}

void disable_gic_dist(void)     {
	ICDDCR = 0; }
void enable_gic_dist(void)      {
	ICDDCR = 1; }
void disable_IRQ_passthrough(void) {
	ICCICR = 0; }
void enable_IRQ_passthrough(void)  {
	ICCICR = 1; }
void set_gic_pmr(uint32_t priority) {
    ICCPMR = priority & 0xFF;
}

void disable_interrupt82(void)
{
    ICDIPTR(20) &= ~0x00FF0000;     // Clear CPU target for int 82
    ICDICER(2)   =  0x00040000;     // Disable int 82 in the distributor
}

void enable_interrupt82(void)
{
    ICDIPTR(20) |=  0x00010000;     // set bit 1 of ICDIPTR13 (enable for cpu0)
    ICDISER(2)   =  0x00040000;     // Enable int 82 in the distributor
}

void set_interrupt82_priority(uint8_t priority_val)
{
    ICDIPR(20) &= ~0x00FF0000; //clear priority bits for interrupt 82
    ICDIPR(20) |=  ((uint32_t)(priority_val & 0xF8)) << 16; //set top 5 bits based on passed value
}

void set_interrupt82_sensitivity(uint8_t sens)
{
    ICDICFR(5) &= ~0x00000030;
    ICDICFR(5) |=  ((uint32_t)(sens & 0x3)) << 4;
}

void configure_GIC_interrupt27(void)
{
    disable_gic_dist();
    disable_IRQ_passthrough();

    set_gic_pmr(0xFF);

    disable_interrupt27();
    set_interrupt27_priority(0xA0); //ID 82, 52, and 27 all have the same priority of 0xA0 = 160. there is no preference given to one over the other
    enable_interrupt27();

    enable_gic_dist();
    enable_IRQ_passthrough();
}

void disable_interrupt27(void)
{
    ICDICER(0) = 0x08000000;    // Disable int 27 (bit 27 of word 0)
}

void enable_interrupt27(void)
{
    ICDISER(0) = 0x08000000;    // Enable int 27 (bit 27 of word 0)
}

void set_interrupt27_priority(uint8_t priority_val)
{
    ICDIPR(6) &= ~0xFF000000;                           // Clear bits [31:24]
    ICDIPR(6) |= ((uint32_t)(priority_val & 0xF8)) << 24; // int 27 is byte 3 of word 6
}

void configure_GIC_interrupt58(void)
{
    disable_gic_dist();
    disable_IRQ_passthrough();

    set_gic_pmr(0xFF);

    // disable while configuring
    ICDICER(1) = 0x04000000;

    // ID 58 is byte 2 of ICDIPR(14): bits [23:16]
    ICDIPR(14) &= ~0x00FF0000;
    ICDIPR(14) |=  ((uint32_t)(0xA0 & 0xF8)) << 16;

    // route to CPU0
    ICDIPTR(14) &= ~0x00FF0000;
    ICDIPTR(14) |=  0x00010000;

    // enable in distributor
    ICDISER(1) = 0x04000000;

    enable_gic_dist();
    enable_IRQ_passthrough();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//ISR FUNCTIONS////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////


//Called from my_handler when interrupt ID == 82.
//Checks the UART ISR to confirm it is an RX trigger interrupt (bit 0),
//reads the character, echoes it back, then clears the flags.
void service_uart1_int(void)
{
    uint32_t status = UART1_ISR;    // Read interrupt status register

    if (status & 0x01) {            // confirm an rx trigger interrupt: Bit 0 = RTRIG (RX trigger)
        char ch = uart1_getchar();  // pull from RX FIFO
        uart1_sendchar(ch);         // push back to TX FIFO
    }

    clear_uart1_int_flags();        // Clear flags so UART doesn't think the interrupt is still pending
    								//and either re-fire or block future interrupts from firing
}

//Clear all UART1 interrupt status flags.
//The ISR is a write-1-to-clear register, so writing all 1s clears everything.
void clear_uart1_int_flags(void)
{
    UART1_ISR = 0xFFFFFFFF;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

void service_spi_int(void)
{
    uart1_sendstr("SPI fired\r\n");

    while (SPI_SR & (1 << 4)) {        // while RX not empty
        uint8_t b = (uint8_t)SPI_RXD;

        if (accel_rx_count == 0) {
            accel_rx_count++;           // byte 0 = cmd echo, discard it
            continue;
        }

        // bytes 1-6 = X_L, X_H, Y_L, Y_H, Z_L, Z_H
        if (accel_rx_count <= 6) {
            accel_buf[accel_rx_count - 1] = b;  // store at 0-5
            accel_rx_count++;
        }
    }

    SPI_SR = (1 << 4); //write 1 to clear RX_NOT_EMPTy interrupt flag

    if (accel_rx_count > 6) {           // got all 6 data bytes
        int16_t ax = (int16_t)((accel_buf[1] << 8) | accel_buf[0]);
        int16_t ay = (int16_t)((accel_buf[3] << 8) | accel_buf[2]);
        int16_t az = (int16_t)((accel_buf[5] << 8) | accel_buf[4]);

        uart1_sendstr("Accel: X = ");
        uart1_sendint(ax);
        uart1_sendstr(", Y = ");
        uart1_sendint(ay);
        uart1_sendstr(", Z = ");
        uart1_sendint(az);
        uart1_sendstr("\r\n");

        uart1_sendstr("Deassert SS\r\n");

        SPI_CR = (SPI_CR & ~(0xF << 10)) | (SS_NONE << 10);
        accel_rx_count = 0;
    }
    // Empty FIFO = interrupt naturally clears at the SPI level
}