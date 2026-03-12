#include "wrapper.h"
#include "TTC.h"

int main(void)
{
    uint32_t ms = 0;
    uint32_t sec = 0;
    uint32_t cs = 0;   
    uint8_t running = 0;  /* 0 = stopped, 1 = running */

    ttc_init(108, 9);

    for (;;) {
        /* handle start/stop toggle and clear */
        stopwatch_update_buttons(&running, &sec, &cs);

        /* wait 1 ms (ish) */
        ttc_wait_for_tick();

        if (running) {
            ms++;

            if (ms >= 10) {
                ms = 0;
                cs++;
            }

            if (cs >= 100) {
                cs = 0;
                sec++;
            }

            if (sec >= 100) {
                sec = 0;
            }
        }

        display_4digits(
            (sec / 10) % 10,
            sec % 10,
            (cs / 10) % 10,
            cs % 10
        );
    }

    return 0;
}