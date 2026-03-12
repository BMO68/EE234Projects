#include "wrapper.h"
#include "ttc.h"

#define BTN_START_MASK   0x1U   /* BTN0 */
#define BTN_REACT_MASK   0x2U   /* BTN1 */
#define REACT_LED_MASK   0x1U   /* LED0 */

static void wait_release(uint32_t mask)
{
    while (BTN_DATA & mask) {
    }
}

int main(void)
{
    uint32_t wait_ms = 0U;
    uint32_t timer_ms = 0U;

    enum {
        IDLE_STATE,
        WAIT_STATE,
        REACT_STATE,
        RESULT_STATE
    } state = IDLE_STATE;

    /* ~1 ms TTC tick */
    ttc_init(108, 9);

    LED = 0U;
    display_ms(0U);

    while (1) {

        if (state == IDLE_STATE) {
            LED = 0U;
            display_ms(0U);

            if (BTN_DATA & BTN_START_MASK) {
                wait_ms = random_delay_ms();
                timer_ms = 0U;
                LED = 0U;
                display_ms(0U);
                wait_release(BTN_START_MASK);
                state = WAIT_STATE;
            }
        }

        else if (state == WAIT_STATE) {
            ttc_wait_for_tick();

            if (wait_ms > 0U) {
                wait_ms--;
            }

            if (wait_ms == 0U) {
                LED = REACT_LED_MASK;
                timer_ms = 0U;
                display_ms(0U);
                state = REACT_STATE;
            }
        }

        else if (state == REACT_STATE) {
            ttc_wait_for_tick();
            timer_ms++;
            display_ms(timer_ms);

            if (BTN_DATA & BTN_REACT_MASK) {
                LED = 0U;
                wait_release(BTN_REACT_MASK);
                state = RESULT_STATE;
            }
        }

        else if (state == RESULT_STATE) {
            LED = 0U;
            display_ms(timer_ms);

            if (BTN_DATA & BTN_START_MASK) {
                wait_ms = random_delay_ms();
                timer_ms = 0U;
                LED = 0U;
                display_ms(0U);
                wait_release(BTN_START_MASK);
                state = WAIT_STATE;
            }
        }
    }

    return 0;
}