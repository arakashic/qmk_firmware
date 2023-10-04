/* Copyright 2022
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

#include "multiaxis.h"

#include "wait.h"

multiaxis_t multiaxis_state = {
    .axes =
        {
#if MULTIAXIS_AXIS_COUNT > 0
            0
#endif
        },
    .dirty = false,
};

// array defining the reading of analog values for each axis
__attribute__((weak)) multiaxis_config_t multiaxis_axes[MULTIAXIS_AXIS_COUNT] = {};

__attribute__((weak)) void multiaxis_task(void) {
    multiaxis_read_axes();
}

void multiaxis_flush(void) {
    if (multiaxis_state.dirty) {
        host_multiaxis_send(&multiaxis_state);
        multiaxis_state.dirty = false;
    }
}

int16_t multiaxis_read_axis(uint8_t axis) {
    if (axis >= MULTIAXIS_AXIS_COUNT) return 0;

    // disable pull-up resistor
    writePinLow(multiaxis_axes[axis].input_pin);

    // if pin was a pull-up input, we need to uncharge it by turning it low
    // before making it a low input
    setPinOutput(multiaxis_axes[axis].input_pin);

    wait_us(10);

    if (multiaxis_axes[axis].output_pin != MS_VIRTUAL_AXIS) {
        setPinOutput(multiaxis_axes[axis].output_pin);
        writePinHigh(multiaxis_axes[axis].output_pin);
    }

    if (multiaxis_axes[axis].ground_pin != MS_VIRTUAL_AXIS) {
        setPinOutput(multiaxis_axes[axis].ground_pin);
        writePinLow(multiaxis_axes[axis].ground_pin);
    }

    wait_us(10);

    setPinInput(multiaxis_axes[axis].input_pin);

    wait_us(10);

    int16_t axis_val = multiaxis_axes[axis].mid_digit;

    // test the converted value against the lower range
    int32_t ref        = multiaxis_axes[axis].mid_digit;
    int32_t range      = multiaxis_axes[axis].min_digit;
    int32_t ranged_val = ((axis_val - ref) * -MULTIAXIS_MAX_VALUE) / (range - ref);

    if (ranged_val > 0) {
        // the value is in the higher range
        range      = multiaxis_axes[axis].max_digit;
        ranged_val = ((axis_val - ref) * MULTIAXIS_MAX_VALUE) / (range - ref);
    }

    // clamp the result in the valid range
    ranged_val = ranged_val < -MULTIAXIS_MAX_VALUE ? -MULTIAXIS_MAX_VALUE : ranged_val;
    ranged_val = ranged_val > MULTIAXIS_MAX_VALUE ? MULTIAXIS_MAX_VALUE : ranged_val;

    return ranged_val;
}

void multiaxis_read_axes(void) {
#if MULTIAXIS_AXIS_COUNT > 0
    for (int i = 0; i < MULTIAXIS_AXIS_COUNT; ++i) {
        if (multiaxis_axes[i].input_pin == MS_VIRTUAL_AXIS) {
            continue;
        }

        multiaxis_set_axis(i, multiaxis_read_axis(i));
    }

    multiaxis_flush();
#endif
}

void multiaxis_set_axis(uint8_t axis, int16_t value) {
    if (axis >= MULTIAXIS_AXIS_COUNT) return;

    if (value != multiaxis_state.axes[axis]) {
        multiaxis_state.axes[axis] = value;
        multiaxis_state.dirty      = true;
    }
}
