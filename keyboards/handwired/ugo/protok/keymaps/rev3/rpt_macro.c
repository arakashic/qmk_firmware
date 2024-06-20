#include "rpt_macro.h"
#include "quantum.h"

#define INTERVAL_MASTER 20
#define INTERVAL_EV1 50
#define INTERVAL_EV2 200

bool rpt_enabled = false;

uint32_t t_master = 0;
uint32_t t_ev1 = 0;
uint32_t t_ev2 = 0;

void rpt_init(void)
{
    rpt_enabled = false;
    t_master = timer_read32();
    t_ev1 = timer_read32();
    t_ev2 = timer_read32();
}

void rpt_enable(void)
{
    rpt_enabled = true;
    t_master = timer_read32();
    t_ev1 = timer_read32();
    t_ev2 = timer_read32();
}

void rpt_disable(void)
{
    rpt_enabled = false;
}

void rpt_toggle(void)
{
    rpt_enabled = !rpt_enabled;
}

void rpt_runner(void)
{
    uint32_t t_curr = timer_read32();

    if (!rpt_enabled) {
        return;
    }

    if (t_curr - t_master < INTERVAL_MASTER) {
        return;
    }

    if (t_curr - t_ev1 > INTERVAL_EV1) {
        tap_code(KC_F);
        t_ev1 = timer_read32();
    }

    if (t_curr - t_ev2 > INTERVAL_EV2) {
        tap_code(KC_A);
        tap_code(KC_S);
        tap_code(KC_D);
        t_ev2 = timer_read32();
    }
    t_master = timer_read32();
}
