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

// clang-format off
#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, \
	K300, K301,       K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, \
	K400, K401,       K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, \
	K500,       K502, K503, K504, K505, K506, K507, K508, K509, K510, K511, K512,       K514, K515, \
	K600, K601,       K603, K604, K605, K606, K607, K608, K609,       K611, K612, K613, K614, K615  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  K215 }, \
	{ K300,  K301,  KC_NO, K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315 }, \
	{ K400,  K401,  KC_NO, K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415 }, \
	{ K500,  KC_NO, K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  K512,  KC_NO, K514,  K515 }, \
	{ K600,  K601,  KC_NO, K603,  K604,  K605,  K606,  K607,  K608,  K609,  KC_NO, K611,  K612,  K613,  K614,  K615 }  \
}
// clang-format on

#endif
