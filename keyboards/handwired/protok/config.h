#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#ifdef REV1
/* USB Device descriptor parameter */
#define VENDOR_ID       0x0FAC
#define PRODUCT_ID      0x0010
#define DEVICE_VER      0x0001
#define MANUFACTURER    UGO
#define PRODUCT         ProtoK Keyboard Model II
#define DESCRIPTION     ProtoK Macro Keyboard Model II

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, B7, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, E6, D6, D7, B4, B5, B6, D4, D5, C7, C6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW
#endif

#ifdef REV2
/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x88BD
#define DEVICE_VER      0x0003
#define MANUFACTURER    UGO
#define PRODUCT         ProtoK Keyboard Model II Rev2 Dev

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

/* choose matrix mode */
/* #define MATRIX_USE_COL_MUX */
#define MATRIX_USE_COL_23017
#define MATRIX_ROW_PINS { A8, A15, B10, B11, B12, A14, A13 }

#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE

#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }
#define ENCODER_RESOLUTION 2

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

#ifdef I2C_EEPROM
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_BYTE_COUNT 32768
#define EXTERNAL_EEPROM_PAGE_SIZE 64
#endif

#endif

#ifdef REV3
#undef STM32_BOOTLOADER_ADDRESS
#define STM32_BOOTLOADER_ADDRESS 0x08000000

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1209
#define PRODUCT_ID      0x88BD
#define DEVICE_VER      0x0004
#define MANUFACTURER    UGO
#define PRODUCT         ProtoK Keyboard Model II Rev3 Dev

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

/* choose matrix mode */
/* #define MATRIX_USE_COL_MUX */
#define MATRIX_USE_COL_23017
#define MATRIX_ROW_PINS { B8, B9, A10, A15, B3, B4, B5 }

#define ENCODERS_PAD_A { B15, B13, A9 }
#define ENCODERS_PAD_B { B14, B12, A8 }
#define ENCODER_RESOLUTION 1

#define UNUSED_PINS { B10, B2, B1, B0, A7, A6, A5, A4, A0 }

#ifdef THUMBSTICK_ENABLE

#define THUMBSTICK_RAW_RES 12
#define THUMBSTICK_VEC_RES 8
#define THUMBSTICK_VCC A3
#define THUMBSTICK_PIN_X A2
#define THUMBSTICK_PIN_Y A1
#define JOYSTICK_X A1
#define JOYSTICK_Y A2
#define THUMBSTICK_FLIP_X
#define THUMBSTICK_FLIP_Y
/* #define THUMBSTICK_DEBUG 1 */

#endif

#ifdef I2C_EEPROM
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_BYTE_COUNT 32768
#define EXTERNAL_EEPROM_PAGE_SIZE 64
#endif

#ifdef SPI_EEPROM
#define SPI_DRIVER SPID1
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
#define EXTERNAL_EEPROM_BYTE_COUNT 16777216
#define EXTERNAL_EEPROM_PAGE_SIZE 256
#endif

#endif


/* /1* Diode direction is COL2ROW *1/ */
/* #define MATRIX_COL_ADDR_BITS 4 */
/* /1* compensate extra wait due to col read, 30us - 1us per col * 16 cols *1/ */
/* #define MATRIX_IO_DELAY 14 */

/* /1* key matrix pins, using mux/demux on columns *1/ */
/* #define MATRIX_ROW_PINS { B15, B9, B10, B11, B12, A14, A13 } */
/* #define MATRIX_COL_SIG_PIN B0 */
/* #define MATRIX_COL_ADDR_PINS { A15, A8, A7, A6 } */


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

#define OLED_DISPLAY_128X64

/* configurations for mod-tap keys */
/* #define TAPPING_TERM 200 */
#define TAPPING_TERM_PER_KEY
/* #define PERMISSIVE_HOLD */
#define PERMISSIVE_HOLD_PER_KEY
/* #define IGNORE_MOD_TAP_INTERRUPT */
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY
/* #define TAPPING_FORCE_HOLD */

#ifdef CONSOLE_ENABLE
#define __ENABLE_LOG 1
/* #define DEBUG_MATRIX_SCAN_RATE */
#endif

#endif
