#include "wrapper.h"
#include "ttc.h"

/* BTN0 = load random
   BTN1 = start
   BTN2 = stop */
#define BTN0_MASK 0x1U
#define BTN1_MASK 0x2U
#define BTN2_MASK 0x4U

static void wait_release(uint32_t mask)
{
    while (BTN_DATA & mask) {
    }
}

int main(void)
{
    uint32_t ms = 0;
    int32_t countdown_cs = 0;
    int32_t score_cs = 0;

    enum {
        LOAD_STATE,
        RUN_STATE,
        SCORE_STATE
    } state = LOAD_STATE;

    ttc_init(108, 9);

    display_4digits(0, 0, 0, 0);

    while (1) {
        if (state == LOAD_STATE) {
            if (BTN_DATA & BTN0_MASK) {
                countdown_cs = (int32_t)random_start_cs();
                ms = 0;

                display_4digits(
                    (countdown_cs / 1000) % 10,
                    (countdown_cs / 100) % 10,
                    (countdown_cs / 10) % 10,
                    countdown_cs % 10
                );

                wait_release(BTN0_MASK);
            }

            if (BTN_DATA & BTN1_MASK) {
                ms = 0;
                state = RUN_STATE;
                wait_release(BTN1_MASK);
            }
        }

        else if (state == RUN_STATE) {
            if (BTN_DATA & BTN2_MASK) {
                score_cs = countdown_cs;
                state = SCORE_STATE;
                wait_release(BTN2_MASK);
            }

            ttc_wait_for_tick();
            ms++;

            if (ms >= 10) {
                ms = 0;
                countdown_cs--;
            }

            if (countdown_cs >= 0) {
                display_4digits(
                    (countdown_cs / 1000) % 10,
                    (countdown_cs / 100) % 10,
                    (countdown_cs / 10) % 10,
                    countdown_cs % 10
                );
            } else {
                /* after zero crossing, show absolute amount late while running */
                int32_t late = -countdown_cs;
                display_signed_score(-late);
            }
        }

        else if (state == SCORE_STATE) {
            display_signed_score(score_cs);

            if (BTN_DATA & BTN0_MASK) {
                countdown_cs = (int32_t)random_start_cs();
                ms = 0;
                state = LOAD_STATE;

                display_4digits(
                    (countdown_cs / 1000) % 10,
                    (countdown_cs / 100) % 10,
                    (countdown_cs / 10) % 10,
                    countdown_cs % 10
                );

                wait_release(BTN0_MASK);
            }
        }
    }

    return 0;
}