#include "wrapper.h"

volatile uint32_t count = 0U;

void gtc_isr(void *CallBackRef)
{
    uint32_t id;

    (void)CallBackRef;

    id = ICCIAR;

    if (id == GTC_INT_ID) {
        uart1_puts("Count = ");
        uart1_put_uint(count);
        uart1_puts("\r\n");

        count++;

        clear_global_timer_interrupt();
    }

    ICCEOIR = id;
}

int main(void)
{
    configure_uart1();

    disable_arm_interrupts();

    register_irq_handler(gtc_isr);
    configure_gic_gtc_interrupt();
    configure_global_timer_periodic_1s();

    enable_arm_interrupts();

    for(;;);

    return 1;
}