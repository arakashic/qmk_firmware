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
#define MATRIX_ROWS 4
#define MATRIX_COLS 4

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
#define REGISTER_BYTES 2
