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

/* key matrix pins */
#define MATRIX_ROW_PINS { B2, B1, B0, A6, A7, A8, A15 }
#define MATRIX_COL_PINS { A14, B12, B11, B10,  B9, B15, \
                           A2,  A1,  A0,  B8, B13, B14, \
                           A9, A10,  B4,  B3 }
#define UNUSED_PINS

#define LED_CAPS_LOCK_PIN A13

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

// #define OLED_SCROLL_TIMEOUT 5000
/* #define I2C_DRIVER I2CD2 */

/* #define I2C2_BANK GPIOB */
/* #define I2C2_SCL 9 */
/* #define I2C2_SDA 10 */

/* configurations for mod-tap keys */
/* #define TAPPING_TERM 200 */
#define TAPPING_TERM_PER_KEY
/* #define PERMISSIVE_HOLD */
#define PERMISSIVE_HOLD_PER_KEY
/* #define IGNORE_MOD_TAP_INTERRUPT */
/* #define IGNORE_MOD_TAP_INTERRUPT_PER_KEY */
/* #define TAPPING_FORCE_HOLD */

#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

// DEBUG
#define DEBUG_MATRIX_SCAN_RATE

#endif
