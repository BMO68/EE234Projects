#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C1_BASE          0xE0005000U
#define I2C_CR             (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C_SR             (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C_ADDR           (*(volatile uint32_t *)(I2C1_BASE + 0x08))
#define I2C_DATA           (*(volatile uint32_t *)(I2C1_BASE + 0x0C))
#define I2C_ISR            (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C_TRANS_SIZE     (*(volatile uint32_t *)(I2C1_BASE + 0x14))

/*add these for part 5*/
#define I2C_IER            (*(volatile uint32_t *)(I2C1_BASE + 0x24))
#define I2C_IDR            (*(volatile uint32_t *)(I2C1_BASE + 0x28))
#define I2C_ISR_DATA       (1u << 1)
/**/

// Control register bits
//   bit 0: RW       1 = master receive,  0 = master transmit
//   bit 1: MS       1 = master mode,     0 = slave mode
//   bit 2: NEA      1 = 7-bit addressing (normal)
//   bit 3: ACK_EN   1 = ACK received bytes
//   bit 4: HOLD     holds SCL low after each byte
//   bit 5: SLVMON   slave monitor mode (not used)
//   bit 6: CLR_FIFO clear TX/RX FIFO
//   bits [13:8]: DIVB
//   bits [15:14]: DIVA

#define I2C_CR_RW           (1u << 0)
#define I2C_CR_MS           (1u << 1)
#define I2C_CR_NEA          (1u << 2)
#define I2C_CR_ACK_EN       (1u << 3)
#define I2C_CR_CLR_FIFO     (1u << 6)

// ISR bits � Zynq TRM:
//   bit 0: COMP     � transfer complete
//   bit 1: DATA     � FIFO data available
//   bit 2: NACK     � slave sent NACK (wrong address / device missing)
//   bit 3: TO       � bus timeout
//   bit 4: SLVRDY   � slave ready
//   bit 8: ARB_LOST � arbitration lost

#define I2C_ISR_COMP        (1u << 0)
#define I2C_ISR_NACK        (1u << 2)

// LM75B � A2=A1=A0=GND -> 0b1001000 = 0x48
#define LM75B_ADDR_7BIT     0x48
#define LM75B_NUM_BYTES     2

void i2c1_init(void);
int  lm75b_read_temp_mC(void);   // returns milli-celsius, or -999999 on error

//////////////////////////////////////////////////////////
//add these for part 5 (remove for part 4)///////////////
//////////////////////////////////////////////////////////

// Shared RX buffer � written by I2C ISR, read by temperature converter
extern volatile uint8_t  i2c_rx_buf[2];
extern volatile int      i2c_rx_ready;   // set to 1 by ISR when 2 bytes are in buf

void i2c1_enable_comp_interrupt(void);   // enable COMP interrupt in I2C IER
void i2c1_start_read(void);              // start a 2-byte read (called from GTC ISR)
int  raw_to_temp_mC(void);

#endif