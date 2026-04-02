#include "wrapper.h"

//uart1 control register
#define UART1_CR *((uint32_t*)0xE0001000)

//uart1 mode register
#define UART1_MR *((uint32_t*)0xE0001004)

#define UART1_BAUDGEN *((uint32_t*)0xE0001018)
#define UART1_BAUDDIV *((uint32_t*)0xE0001034)
#define UART1_FIFO *((uint32_t*)0xE0001030)

//Switches and LEDs
#define LED_CTL *((uint32_t*)0x41210000)
#define SW_DATA *((uint32_t*)0x41220000)


#define XADC_BASE      0xF8007100U
#define VCCAUX_OFFSET  0x208U

#define REG32(addr) (*(volatile uint32_t *)(addr))

#include <stdint.h>


uint32_t read_xadc_voltage(void)
{
    uint32_t raw;

    raw = REG32(XADC_BASE + VCCAUX_OFFSET);

    raw = (raw >> 4) & 0x0FFF;

    return raw;
}

float convert_to_voltage(uint32_t adc_value)
{
    return (adc_value / 4096.0f) * 3.0f;
}

void send_to_pc(float voltage) {
        UART1_FIFO = voltage;
}