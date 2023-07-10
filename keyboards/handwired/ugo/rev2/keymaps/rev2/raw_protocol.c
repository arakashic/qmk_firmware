#include "raw_protocol.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);
}
