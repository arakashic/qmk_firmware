// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "debug.h"
#include "rev4.h"

enum custom_keycodes {
    SPI_READ = SAFE_RANGE,
    XAP_K1,
};

enum layer_names {
    L_DEF = 0,
    L_GAME,
    L_FUN,
    L_SYM,
    L_NAV,
    L_SET,
    L_CMD
};

#define EXT_KEY XXXXXXX
#define PK_BSPC LT(L_SYM, KC_BSPC)
#define PK_SPC  RSFT_T(KC_SPC)
#define PK_LCTL LCTL_T(KC_ESC)
#define PK_TAB  LT(L_NAV, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* base layer PC */
    [L_DEF] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPS, KC_INS ,
           KC_DEL   , KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_HOME, KC_END ,
           KC_HOME  , PK_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , EXT_KEY, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_DEL ,
           KC_END   , PK_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , EXT_KEY, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_BSLS, MO(L_FUN),
           XXXXXXX  , SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , EXT_KEY, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SC_RSPC, KC_PGUP, EXT_KEY,
           MO(L_CMD),  XAP_K1, XXXXXXX, KC_HYPR, KC_LGUI, KC_LALT, PK_BSPC, EXT_KEY, PK_SPC , KC_ENT , KC_RALT, KC_RGUI, KC_LCTL, XXXXXXX, KC_UP  , KC_PGDN,
                                                                                                                                  KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* Game layer PC */
    [L_GAME] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_CAPS, KC_INS ,
           KC_DEL   , KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_HOME, KC_END ,
           KC_HOME  , KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , EXT_KEY, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSPC,
           KC_END   , PK_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , EXT_KEY, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_BSLS, MO(L_FUN),
           XXXXXXX  , SC_LSPO, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , EXT_KEY, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, SC_RSPC, KC_PGUP, EXT_KEY,
           MO(L_CMD), XXXXXXX, XXXXXXX, KC_HYPR, KC_LGUI, KC_LALT, KC_SPC , EXT_KEY, KC_SPC , KC_ENT , KC_RALT, KC_RGUI, KC_LCTL, KC_DEL , KC_UP  , KC_PGDN,
                                                                                                                                  KC_LEFT, KC_DOWN, KC_RGHT
    ),
    /* additional func */
    [L_FUN] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, KC_PWR , KC_SLEP, KC_WAKE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MPLY  , KC_MSTP, KC_MPRV, KC_MNXT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_MUTE  , _______, _______, _______, _______, _______, _______, EXT_KEY, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLU  , _______, _______, _______, _______, _______, _______, EXT_KEY, _______, _______, _______, _______, _______, _______, _______, _______,
           KC_VOLD  , KC_LSFT, _______, _______, _______, _______, _______, EXT_KEY, _______, _______, _______, _______, _______, KC_RSFT, _______, EXT_KEY,
           _______  , _______, _______, _______, _______, _______, KC_SPC , EXT_KEY, _______, _______, _______, _______, _______, _______, _______, _______,
                                                                                                                                  _______, _______, _______
    ),
    /* symbol layer */
    [L_SYM] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EXLM, XXXXXXX, EXT_KEY, XXXXXXX, KC_UNDS, KC_CIRC, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, KC_AT  , KC_DLR , KC_PERC, KC_ASTR, KC_AMPR, EXT_KEY, KC_HASH, KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                  XXXXXXX, XXXXXXX, XXXXXXX
    ),
    /* nav layer */
    [L_NAV] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, KC_UP  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, EXT_KEY, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                  XXXXXXX, XXXXXXX, XXXXXXX
    ),
    /* bootmagic key layer */
    [L_SET] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           NK_TOGG  , NK_ON  , NK_OFF , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           AG_NORM  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, LAG_NRM, LAG_SWP, XXXXXXX, EXT_KEY, XXXXXXX, RAG_SWP, RAG_NRM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                  XXXXXXX, XXXXXXX, XXXXXXX
    ),
    /* command jump layer */
    [L_CMD] = LAYOUT_split(
           EXT_KEY  , EXT_KEY, DT_PRNT,   DT_UP, DT_DOWN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, DB_TOGG,  EE_CLR,  QK_RBT, OSL(L_SET),
           KC_ACL2  , XXXXXXX,TO(L_DEF),TO(L_GAME),XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL1  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           KC_ACL0  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
           XXXXXXX  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY,
           XXXXXXX  , QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EXT_KEY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                                                                                  XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case XAP_K1:
            xap_broadcast_user(&keycode, 2);
            return false;
        default:
            return true;
    }
}

void keyboard_post_init_user(void) {
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse    = true;
}

// void housekeeping_task_user(void) {
//     static uint32_t timer = 0;
//     static uint8_t count = 0;
//     if (timer_elapsed32(timer) > 1000) {
//         timer = timer_read32();
//         count++;
//
//         xap_broadcast(0x03, &count, 1);
//     }
// }
