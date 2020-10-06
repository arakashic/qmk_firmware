#include "protok.h"
#include "print.h"
#include "song_list.h"

enum layer_names {
    _QWERTY = 0,
    _FUNCTION,
    _COMMAND,
    _SETUP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* base layer PC */
    LAYOUT(KC_A , KC_S , KC_D , KC_F , KC_CLCK , KC_NLCK , DEBUG)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    /* keyevent_t event = record->event; */

    switch (id) {

    }
    return MACRO_NONE;
}

void matrix_init_user(void) {
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    //debug_mouse=true;
}
void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    float my_song[][2] = SONG(QWERTY_SOUND);
    if (keycode == DEBUG && record->event.pressed) {
        PLAY_SONG(my_song);
        print("debug pressed.\n");
    }
    return true;
}

void led_set_user(uint8_t usb_led) {

    /* if (usb_led & (1 << USB_LED_NUM_LOCK)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_CAPS_LOCK)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_SCROLL_LOCK)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_COMPOSE)) { */
    /* } else { */
    /* } */

    /* if (usb_led & (1 << USB_LED_KANA)) { */
    /* } else { */
    /* } */

}

#ifdef OLED_DRIVER_ENABLE

void render_status(void);
/* void render_logo(void); */

void render_status(void) {

    // Render to mode icon
    /* static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}}; */

    oled_clear();

    oled_write_P(PSTR("A\n"), false);
    oled_write_P(PSTR("BC\n"), false);
    oled_write_P(PSTR("0123456789ABCDEFGHIJKL\n"), false);
    oled_write_char(0x7f, false);
    oled_write_char(0x0, false);
    oled_write_pixel(64, 32, true);
    /* if (is_mac_mode()) { */
    /* oled_write_P(os_logo[0][0], false); */
    /* oled_write_P(PSTR("\n"), false); */
    /* oled_write_P(os_logo[0][1], false); */
    /* }else{ */
    /* oled_write_P(os_logo[1][0], false); */
    /* oled_write_P(PSTR("\n"), false); */
    /* oled_write_P(os_logo[1][1], false); */
    /* } */

    /* oled_write_P(PSTR(" "), false); */

    /* oled_write_P(eeconfig_read_debug() ? PSTR("DBG ") : PSTR("NDBG "), false); */

    // Host Keyboard Layer Status
    /* oled_write_P(PSTR("Layer: "), false); */

    /* switch (get_highest_layer(layer_state)) { */
    /* case _QWERTY: */
    /*     oled_write_P(PSTR("Default\n"), false); */
    /*     break; */
    /* case _FUNCTION: */
    /*     oled_write_P(PSTR("Function\n"), false); */
    /*     break; */
    /* case _COMMAND: */
    /*     oled_write_P(PSTR("Command\n"), false); */
    /*     break; */
    /* case _SETUP: */
    /*     oled_write_P(PSTR("Setup\n"), false); */
    /*     break; */
    /* default: */
    /*     // Or use the write_ln shortcut over adding '\n' to the end of your string */
    /*     oled_write_ln_P(PSTR("Undefined"), false); */
    /* } */

    /* oled_write_P(PSTR("\n"), false); */

    /* // Host Keyboard LED Status */
    /* led_t led_state = host_keyboard_led_state(); */
    /* oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("NAH"), false); */
    oled_write_P(host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK) ? PSTR("CAP ") : PSTR("NAH"), false);
    /* oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("NAH"), false); */
    /* static const char PROGMEM qmk_logo[] = { */
    /*     0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, */
    /*     0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, */
    /*     0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00 */
    /* }; */

    /* oled_write_P(qmk_logo, false); */
}

/* void render_logo(void) { */
/*     static const char PROGMEM qmk_logo[] = { */
/*         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, */
/*         0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, */
/*         0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00 */
/*     }; */

/*     oled_write_P(qmk_logo, false); */
/* } */

void oled_task_user(void) {
    /* if(is_keyboard_master()){ */
    render_status();
    /* }else{ */
    /* render_logo(); */
    /*   /1* render_rgbled_status(true); *1/ */
    /* } */
}
#endif

