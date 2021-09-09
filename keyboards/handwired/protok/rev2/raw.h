#pragma once

#include <stdint.h>
#include "raw_hid.h"

void raw_hid_receive(uint8_t *data, uint8_t length);
