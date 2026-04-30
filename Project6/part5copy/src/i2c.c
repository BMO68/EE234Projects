#include "i2c.h"
#include "uart.h"

void i2c1_init(void)
{
    // Step 1: clear FIFOs and then zero the control register
    I2C_CR = I2C_CR_CLR_FIFO;
    I2C_CR = 0;

    // Step 2: clear any stale interrupt flags
    I2C_ISR = 0xFFFFFFFFu;

    // Step 3: configure for 400 kHz master receive
    //   SCL = 111 MHz / (22 x (DIVB + 1) x 2^DIVA)
    //       = 111 MHz / (22 x 13 x 1)  ~= 388 kHz
    uint32_t cr = 0;
    cr |= (0u  << 14);      // DIVA = 0
    cr |= (12u <<  8);      // DIVB = 12
    cr |= I2C_CR_ACK_EN;    // bit 3: ACK received bytes
    cr |= I2C_CR_NEA;       // bit 2: 7-bit addressing
    cr |= I2C_CR_MS;        // bit 1: master mode
    cr |= I2C_CR_RW;        // bit 0: master receive
    I2C_CR = cr;
}

// Read 2 bytes from LM75B/ Returns 0 on success, -1 on timeout, -2 on NACK
static int lm75b_read_raw(uint8_t buf[2])
{
    // Clear FIFO before every transaction
    I2C_CR |= I2C_CR_CLR_FIFO;

    // Ensure read direction is set
    I2C_CR |= I2C_CR_RW;

    // Write the number of bytes to receive (2)
    I2C_TRANS_SIZE = LM75B_NUM_BYTES;

    // Clear flags
    I2C_ISR = 0xFFFFFFFFu;

    // Writing ADDR starts the transaction: START + 7-bit address + R/W bit
    I2C_ADDR = LM75B_ADDR_7BIT;

    // Wait for COMP with timeout and NACK detection
    uint32_t timeout = 200000u;
    while ((I2C_ISR & I2C_ISR_COMP) == 0u) {
        if (I2C_ISR & I2C_ISR_NACK) {
            I2C_ISR = 0xFFFFFFFFu;
            return -2;
        }
        if (--timeout == 0u) {
            return -1;
        }
    }

    // Pull 2 bytes out of the RX FIFO
    buf[0] = (uint8_t)(I2C_DATA & 0xFFu);
    buf[1] = (uint8_t)(I2C_DATA & 0xFFu);

    I2C_ISR = I2C_ISR_COMP;    // clear for next transaction

    return 0;
}

// read LM75B, return temperature in milli-celsius
// Returns -999999 on any error
int lm75b_read_temp_mC(void)
{
    uint8_t raw[2];
    int rc = lm75b_read_raw(raw);

    if (rc == -1) {
        uart1_sendstr("[I2C] timeout - check SCL/SDA wiring\r\n");
        i2c1_init();
        return -999999;
    }
    if (rc == -2) {
        uart1_sendstr("[I2C] NACK - check LM75B address (A0/A1/A2 pins)\r\n");
        i2c1_init();
        return -999999;
    }

    // LM75B data format: raw[0]=MSB, raw[1]=LSB, bottom 5 bits always 0
    uint16_t v = ((uint16_t)raw[0] << 8) | raw[1];
    v >>= 5;                    // 11-bit value

    if (v & 0x0400u) {          // bit 10 = sign bit
        v |= 0xF800u;           // sign-extend to 16 bits
    }

    int16_t code = (int16_t)v;
    return (int)code * 125;     // 0.125 C per LSB = 125 milli-C per LSB
}

///////////////////////////////////////////////
///////////////////////////////////////////////
//add this for part 5:
///////////////////////////////////////////////

// Shared buffer — written by I2C ISR, read by raw_to_temp_mC()
volatile uint8_t  i2c_rx_buf[2] = {0, 0};
volatile int      i2c_rx_ready   = 0;

// Enable the COMP interrupt inside the I2C controller.
// Call after i2c1_init() and after configure_GIC_interrupt80().
void i2c1_enable_comp_interrupt(void)
{
    I2C_ISR = 0xFFFFFFFFu;      // clear stale flags first
    I2C_IDR = 0xFFFFFFFFu;      // disable all I2C interrupts
    I2C_IER = I2C_ISR_COMP;     // then enable only COMP (bit 0)
}

// Start a 2-byte read from LM75B — called from GTC ISR every second.
// Writing ADDR triggers START + address on the bus.
// COMP interrupt fires when both bytes are in the RX FIFO.
void i2c1_start_read(void)
{
    I2C_CR  |= I2C_CR_CLR_FIFO;
    I2C_ISR  = 0xFFFFFFFFu;
    I2C_CR  |= I2C_CR_RW;
    I2C_TRANS_SIZE = LM75B_NUM_BYTES;
    I2C_IER  = I2C_ISR_COMP;    // re-arm in case it was cleared
    I2C_ADDR = LM75B_ADDR_7BIT; // starts the transaction
}

// Convert i2c_rx_buf to milli-celsius.
int raw_to_temp_mC(void)
{
    uint16_t v = ((uint16_t)i2c_rx_buf[0] << 8) | i2c_rx_buf[1];
    v >>= 5;
    if (v & 0x0400u) {
        v |= 0xF800u;
    }
    int16_t code = (int16_t)v;
    return (int)code * 125;
}