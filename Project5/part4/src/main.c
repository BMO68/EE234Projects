#include "wrapper.h"

/* ========= global state for Part 5 ========= */
volatile uint32_t blink_target = 0U;   /* requested cycles from UART: 1..9 */
volatile uint32_t blink_count  = 0U;   /* completed blink cycles */
volatile uint32_t led_on       = 0U;   /* 0 = off, 1 = on */
volatile uint32_t blinking     = 0U;   /* 1 while active */

static void start_blink_sequence(void)
{
    if ((blink_target == 0U) || (blinking != 0U)) {
        return;
    }

    blink_count = 0U;
    led_on = 0U;
    blinking = 1U;

    rgb_led_off();
    start_blink_timer();

    uart1_puts("Blinking started\r\n");
}

static void stop_blink_sequence(void)
{
    stop_blink_timer();
    rgb_led_off();

    blinking = 0U;
    blink_count = 0U;
    led_on = 0U;

    uart1_puts("Blinking stopped\r\n");
}

void my_handler(void *CallBackRef)
{
    uint32_t id;

    (void)CallBackRef;

    id = ICCIAR;

    if (id == UART1_INT_ID)
    {
        while (!uart1_rx_empty())
        {
            char c = uart1_read_char();

            /* project says accept 1..9 over UART, convert char -> int */
            if ((blinking == 0U) && (c >= '1') && (c <= '9'))
            {
                blink_target = (uint32_t)(c - '0');
                uart1_puts("Blink count updated\r\n");
            }
        }

        uart1_clear_rx_interrupt_flag();
    }
    else if (id == GPIO_INT_ID)
    {
        uint32_t flags = get_gpio_int_status(BT4_BANK, BT4_MASK | BT5_MASK);

        if ((flags & BT4_MASK) != 0U) {
            start_blink_sequence();
        }

        if ((flags & BT5_MASK) != 0U) {
            stop_blink_sequence();
        }

        clear_gpio_int_status(BT4_BANK, BT4_MASK | BT5_MASK);
    }
    else if (id == GTC_INT_ID)
    {
        if (blinking != 0U)
        {
            if (led_on == 0U)
            {
                rgb_led_on();
                led_on = 1U;
            }
            else
            {
                rgb_led_off();
                led_on = 0U;

                /* one full blink cycle completes when LED goes off */
                blink_count++;

                if (blink_count >= blink_target)
                {
                    stop_blink_sequence();
                }
            }
        }

        clear_global_timer_interrupt();
    }

    ICCEOIR = id;
}

int main(void)
{
    configure_uart1();
    configure_rgb_led();

    /* optional startup text for debugging */
    uart1_puts("UART alive\r\n");

    disable_arm_interrupts();

    register_irq_handler(my_handler);

    configure_gic_uart1();
    configure_gic_gpio();
    configure_gic_gtc();

    configure_uart1_interrupt();
    configure_button_interrupts();

    stop_blink_timer();
    rgb_led_off();

    enable_arm_interrupts();

    while (1) {
        /* all work is interrupt-driven for Part 5 */
    }

    return 0;
}