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
#define MATRIX_ROWS 1
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { B10 }
#define MATRIX_COL_PINS { A13, A14, B12, B0, B1, B2, B3 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 0
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
/* #define LOCKING_SUPPORT_ENABLE */

/* Locking resynchronize hack */
/* #define LOCKING_RESYNC_ENABLE */

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)) \
)

/* prevent stuck modifiers */
/*
#define PREVENT_STUCK_MODIFIERS


#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
*/

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define TERMINAL_HELP

#define OLED_DISPLAY_128X64
// #define OLED_DISPLAY_WIDTH  128
// #define OLED_DISPLAY_HEIGHT 64
// #define OLED_MATRIX_SIZE    1024
// #define OLED_BLOCK_COUNT    16
// #define OLED_BLOCK_SIZE     64

#define OLED_SCROLL_TIMEOUT 5000

#endif
