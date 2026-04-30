//part 4: poll for btn4 to be pressed, then return temp in celsius to the terminal. needs uart.c, uart.h, i2c.h, and i2c.c
#include <stdint.h>
#include "uart.h"
#include "i2c.h"

#define GPIO_BASE           0xE000A000U

//output data register
#define GPIO_DATA(n)		*(((uint32_t*) 0xE000A040)+n)

//input data register
#define GPIO_DATA_RO(n) 	*(((uint32_t*) 0xE000A060)+n)

//direction register
#define GPIO_DIRM(n) 		*(((uint32_t*) 0xE000A204) + 16*n)

//output enable register
#define GPIO_OEN(n) 		*(((uint32_t*) 0xE000A208) + 16*n)

#define BTN4_MIO    50
#define BTN4_BANK   (BTN4_MIO / 32)
#define BTN4_BIT    (BTN4_MIO % 32)
#define BTN4_MASK   (1u << BTN4_BIT)

static void gpio_init_btn4(void)
{
    GPIO_DIRM(BTN4_BANK) &= ~BTN4_MASK;   // input direction
    GPIO_OEN(BTN4_BANK)  &= ~BTN4_MASK;   // output-enable off
}

static int read_btn4(void)
{
    return (GPIO_DATA_RO(BTN4_BANK) & BTN4_MASK) ? 1 : 0;
}

static void print_temp_mC(int temp_mC)
{
    uart1_sendstr("Temp = ");

    if (temp_mC < 0) {
        uart1_sendchar('-');
        temp_mC = -temp_mC;
    }

    int whole =  temp_mC / 1000;
    int frac  =  temp_mC % 1000;

    uart1_sendint(whole);
    uart1_sendchar('.');
    uart1_sendchar('0' + (frac / 100));
    uart1_sendchar('0' + ((frac / 10) % 10));
    uart1_sendchar('0' + (frac % 10));

    uart1_sendstr(" C\r\n");
}

int main(void)
{
    configure_uart1();
    uart1_sendstr("Part 4 - I2C Temperature Sensor\r\n");
    uart1_sendstr("Press BTN4 to read temperature\r\n");

    gpio_init_btn4();
    i2c1_init();

    int prev = 0;

    while (1) {
        int cur = read_btn4();

        if (cur && !prev) {                        // rising edge only
            uart1_sendstr("BTN4 detected\r\n");    // confirm button is working

            int temp_mC = lm75b_read_temp_mC();

            if (temp_mC == -999999) {
                uart1_sendstr("Temperature read failed\r\n");
            } else {
                print_temp_mC(temp_mC);
            }
        }
        prev = cur;
    }

    return 0;
}