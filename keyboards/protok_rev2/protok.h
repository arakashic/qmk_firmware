#ifndef PROTOK_H
#define PROTOK_H

#include "quantum.h"

/* ProtoK LEDs
 *   D6 Capslock LED
 */

/*
inline void protok_caps_led_on(void)  { setPinOutput(D6); writePinLow(D6); }
inline void protok_caps_led_off(void) { setPinInput(D6); }
*/

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006 \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006 } \
}

#endif
