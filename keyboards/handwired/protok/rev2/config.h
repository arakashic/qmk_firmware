#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x0FAC
#define PRODUCT_ID      0x0010
#define DEVICE_VER      0x0002
#define MANUFACTURER    UGO
#define PRODUCT         ProtoK Keyboard Model II Rev2 Dev

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

/* choose matrix mode */
/* #define MATRIX_USE_COL_MUX */
#define MATRIX_USE_COL_23017

#if defined(MATRIX_USE_COL_MUX)

/* Diode direction is COL2ROW */
#define MATRIX_COL_ADDR_BITS 4
/* compensate extra wait due to col read, 30us - 1us per col * 16 cols */
#define MATRIX_IO_DELAY 14

/* key matrix pins, using mux/demux on columns */
#define MATRIX_ROW_PINS { B15, B9, B10, B11, B12, A14, A13 }
#define MATRIX_COL_SIG_PIN B0
#define MATRIX_COL_ADDR_PINS { A15, A8, A7, A6 }

#elif defined(MATRIX_USE_COL_23017)

#define MATRIX_ROW_PINS { A8, A15, B10, B11, B12, A14, A13 }
/* Diode direction is COL2ROW */

#else

#define MATRIX_ROW_PINS { B15, B9, B10, B11, B12, A14, A13 }
#define MATRIX_COL_PINS { A14, B12, B11, B10,  B9, B15, \
                           A2,  A1,  A0,  B8, B13, B14, \
                           A9, A10,  B4,  B3 }
/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#endif

#define UNUSED_PINS

/* #define LED_CAPS_LOCK_PIN A13 */


/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
/* #define DEBOUNCING_DELAY 5 */

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */

/* Locking resynchronize hack */
/* #define LOCKING_RESYNC_ENABLE */


/* Tapping this number of times holds the key until tapped once again. */
// #define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define TERMINAL_HELP

#define OLED_DISPLAY_128X64

/* configurations for mod-tap keys */
/* #define TAPPING_TERM 200 */
#define TAPPING_TERM_PER_KEY
/* #define PERMISSIVE_HOLD */
#define PERMISSIVE_HOLD_PER_KEY
/* #define IGNORE_MOD_TAP_INTERRUPT */
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
/* #define TAPPING_FORCE_HOLD */

#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }
#define ENCODER_RESOLUTION 2

#define __ENABLE_LOG 1
/* #define DEBUG_MATRIX_SCAN_RATE */

#ifdef THUMBSTICK_ENABLE

#define ADC_RESOLUTION ADC_CFGR_RES_12BITS

#define THUMBSTICK_RAW_RES 12
#define THUMBSTICK_VEC_RES 8
#define THUMBSTICK_VCC B9
#define THUMBSTICK_PIN_X A6
#define THUMBSTICK_PIN_Y A7
#define THUMBSTICK_FLIP_X
#define THUMBSTICK_FLIP_Y
/* #define THUMBSTICK_DEBUG 1 */

#endif


#endif
