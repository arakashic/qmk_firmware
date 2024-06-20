#ifndef RPT_MACRO_H_INCLUDED

#define RPT_MACRO_H_INCLUDED

#include <stdbool.h>

extern bool rpt_enabled;

void rpt_init(void);
void rpt_enable(void);
void rpt_disable(void);
void rpt_toggle(void);
void rpt_runner(void);

#endif /* end of include guard: RPT_MACRO_H_INCLUDED */
