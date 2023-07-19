// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "debug.h"

enum custom_keycodes {
    SPI_READ = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_P0,   KC_PDOT, KC_PENT, KC_PPLS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // uint8_t buf[REGISTER_BYTES] = { 0, 0 };
    // bool ret = true;
    // spi_status_t spi_ret = SPI_STATUS_SUCCESS;
    // switch (keycode) {
    //     case SPI_READ:
    //         if (record->event.pressed) {
    //             printf("Hello world! ");
    //             memset(buf, 0, REGISTER_BYTES);
    //             writePinLow(REGISTER_LD_PIN);
    //             wait_us(10);
    //             writePinHigh(REGISTER_LD_PIN);
    //             wait_us(100);
    //             ret = spi_start(REGISTER_CS_PIN, false, 0, 64);
    //             if (ret) {
    //                 // spi_ret = spi_receive(&buf, REGISTER_BYTES);
    //                 spi_ret = spi_receive(buf, REGISTER_BYTES);
    //                 if (spi_ret == SPI_STATUS_SUCCESS) {
    //                     printf("SPI read: ");
    //                     for (int i = 0; i< REGISTER_BYTES; i++) {
    //                         printf("0x%x ", buf[i]);
    //                     }
    //                     printf("\n");
    //                 } else {
    //                     printf("SPI read error\n");
    //                 }
    //                 spi_stop();
    //             } else {
    //                 printf("SPI start error\n");
    //             }
    //             wait_us(100);
    //             writePinLow(REGISTER_LD_PIN);
    //             wait_us(10);
    //             writePinHigh(REGISTER_LD_PIN);
    //         }
    //         break;
    // }
    return false;
};

void keyboard_post_init_user(void) {
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;
}
