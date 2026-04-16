#include "wrapper.h"

void gpio_isr(void *CallBackRef)
{
    uint32_t id;
    uint32_t flags;

    (void)CallBackRef;

    id = ICCIAR;

    if (id == GPIO_INT_ID)
    {
        flags = get_gpio_int_status(BT4_BANK, BT4_MASK | BT5_MASK);

        if ((flags & BT4_MASK) != 0U)
        {
            rgb_led_on();    /* one button turns LED on */
        }

        if ((flags & BT5_MASK) != 0U)
        {
            rgb_led_off();   /* other button turns LED off */
        }

        clear_gpio_int_status(BT4_BANK, BT4_MASK | BT5_MASK);
    }

    ICCEOIR = id;
}

int main(void)
{
    configure_rgb_led();

    disable_arm_interrupts();

    register_irq_handler(gpio_isr);
    configure_gic_gpio_interrupt();
    configure_button_interrupts();

    enable_arm_interrupts();

    for(;;);

    return 0;
}