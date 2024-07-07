#include <stdint.h>
#include "raw.h"
#include "common/log.h"
#include "eeconfig.h"

enum {
    MSG_HEARTBEAT = 0,
    MSG_MODE = 1
};

uint8_t protok_os_type = OS_TYPE_NULL;

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t msg_id = *data;
    /* uint8_t payload_sz = *(data + 1); */
    uint8_t *payload = data + 2;

    switch (msg_id) {
        case MSG_HEARTBEAT:
            break;
        case MSG_MODE: {
            uint8_t os_type = *payload;
            uint16_t eeconfig_keymap = eeconfig_read_keymap();

            switch (os_type) {
                case OS_TYPE_WIN:
                    protok_os_type = os_type;
                case OS_TYPE_LINUX:
                    protok_os_type = os_type;
                    eeconfig_keymap &= ~EECONFIG_KEYMAP_SWAP_LALT_LGUI;
                    eeconfig_keymap &= ~EECONFIG_KEYMAP_SWAP_RALT_RGUI;
                    eeconfig_update_keymap(eeconfig_keymap);
                    break;
                case OS_TYPE_MAC:
                    protok_os_type = os_type;
                    eeconfig_keymap |= EECONFIG_KEYMAP_SWAP_LALT_LGUI;
                    eeconfig_keymap &= ~EECONFIG_KEYMAP_SWAP_RALT_RGUI;
                    eeconfig_update_keymap(eeconfig_keymap);
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}
