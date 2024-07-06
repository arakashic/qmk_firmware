// Copyright 2023 Yanfei Guo (@UGO)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16

// SPI Configuration (needed for FRAM and FLASH)
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4

// 74HC165 configuration
// #define REGISTER_CS_PIN A8
// #define REGISTER_LD_PIN B0
#define REGISTER_CS_PIN C14
#define REGISTER_LD_PIN C15
#define REGISTER_BYTES 13

#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100000
#define EXTERNAL_EEPROM_BYTE_COUNT 32768
#define EXTERNAL_EEPROM_PAGE_SIZE 64

#define ONESHOT_TIMEOUT 5000

/* configurations for mod-tap keys */
/* #define TAPPING_TERM 200 */
#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD_PER_KEY
// #define TAPPING_FORCE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM_PER_KEY

