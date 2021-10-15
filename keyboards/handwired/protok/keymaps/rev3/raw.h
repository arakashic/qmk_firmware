#pragma once

#include <stdint.h>
#include "raw_hid.h"

extern uint8_t protok_os_type;

enum {
    OS_TYPE_WIN = 0,
    OS_TYPE_LINUX,
    OS_TYPE_MAC,
    OS_TYPE_NULL
};

void raw_hid_receive(uint8_t *data, uint8_t length);
