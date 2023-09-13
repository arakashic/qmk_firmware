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
// #define REGISTER_BYTES 13
// TODO: testing left
#define REGISTER_BYTES 13

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN B12
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR 8
#define EXTERNAL_FLASH_PAGE_SIZE 256
#define EXTERNAL_FLASH_SECTOR_SIZE (4 * 1024)
#define EXTERNAL_FLASH_BLOCK_SIZE (64 * 1024)
#define EXTERNAL_FLASH_SIZE (16 * 1024 * 1024)
#define EXTERNAL_FLASH_ADDRESS_SIZE 3
//
// #define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_COUNT 1
// #define WEAR_LEVELING_EXTERNAL_FLASH_BLOCK_OFFSET 0
// #define WEAR_LEVELING_BACKING_SIZE	(2 * EXTERNAL_FLASH_BLOCK_SIZE)
// #define WEAR_LEVELING_LOGICAL_SIZE	(WEAR_LEVELING_BACKING_SIZE / 2)
