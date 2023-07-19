#ifndef CONFIG_H
#define CONFIG_H

#undef STM32_BOOTLOADER_ADDRESS
#define STM32_BOOTLOADER_ADDRESS 0x08000000

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

/* choose matrix mode */
/* #define MATRIX_USE_COL_MUX */
#define MATRIX_USE_COL_23017
#define MATRIX_ROW_PINS { B8, B9, A10, A15, B3, B4, B5 }

#define ENCODERS_PAD_A { B15, B13, A9 }
#define ENCODERS_PAD_B { B14, B12, A8 }
#define ENCODER_RESOLUTIONS { 2, 2, 1 }

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

#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_BYTE_COUNT 32768
#define EXTERNAL_EEPROM_PAGE_SIZE 64

/* Tapping this number of times holds the key until tapped once again. */
// #define ONESHOT_TAP_TOGGLE 5
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define OLED_DISPLAY_128X64
#define OLED_FONT_H "keyboards/handwired/ugo/protok/keymaps/rev3/glcdfont.c"

/* configurations for mod-tap keys */
/* #define TAPPING_TERM 200 */
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
// #define TAPPING_FORCE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM_PER_KEY

#ifdef CONSOLE_ENABLE
#define __ENABLE_LOG 1
/* #define DEBUG_MATRIX_SCAN_RATE */
#endif

#endif
