/* Copyright 2023
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "gpio.h"

/**
 * \file
 *
 * \defgroup multiaxis HID Multi-axis
 * \{
 */

#ifndef MULTIAXIS_AXIS_COUNT
#    define MULTIAXIS_AXIS_COUNT 2
#elif MULTIAXIS_AXIS_COUNT > 6
#    error Multi-axis feature only supports up to 6 axes
#endif

#ifndef MULTIAXIS_AXIS_RESOLUTION
#    define MULTIAXIS_AXIS_RESOLUTION 8
#elif MULTIAXIS_AXIS_RESOLUTION < 8 || MULTIAXIS_AXIS_RESOLUTION > 16
#    error MULTIAXIS_AXIS_RESOLUTION must be between 8 and 16
#endif

#define MULTIAXIS_MAX_VALUE ((1L << (MULTIAXIS_AXIS_RESOLUTION - 1)) - 1)

// configure on input_pin of the multiaxis_axes array entry to JS_VIRTUAL_AXIS
// to prevent it from being read from the ADC. This allows outputing forged axis value.
//
#define MS_VIRTUAL_AXIS 0xFF

#define MULTIAXIS_AXIS_VIRTUAL \
    { MS_VIRTUAL_AXIS, MS_VIRTUAL_AXIS, MS_VIRTUAL_AXIS, 0, 1023 }

typedef struct {
    pin_t output_pin;
    pin_t input_pin;
    pin_t ground_pin;

    // the AVR ADC offers 10 bit precision, with significant bits on the higher part
    uint16_t min_digit;
    uint16_t mid_digit;
    uint16_t max_digit;
} multiaxis_config_t;

extern multiaxis_config_t multiaxis_axes[MULTIAXIS_AXIS_COUNT];

typedef struct {
    int16_t axes[MULTIAXIS_AXIS_COUNT];
    bool    dirty;
} multiaxis_t;

extern multiaxis_t multiaxis_state;

void multiaxis_task(void);

/**
 * \brief Send the multiaxis report to the host, if it has been marked as dirty.
 */
void multiaxis_flush(void);

/**
 * \brief Sample and process the analog value of the given axis.
 *
 * \param axis The axis to read.
 *
 * \return A signed 16-bit integer, where 0 is the resting or mid point.
 */
int16_t multiaxis_read_axis(uint8_t axis);

void multiaxis_read_axes(void);

/**
 * \brief Set the value of the given axis.
 *
 * \param axis The axis to set the value of.
 * \param value The value to set.
 */
void multiaxis_set_axis(uint8_t axis, int16_t value);

void host_multiaxis_send(multiaxis_t *multiaxis);

/** \} */
