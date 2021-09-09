#include "raw.h"
#include "log.h"

static uint8_t d[4] = "UGO";

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 0) {
        log_debug("poll %d byte(s)\n", length);
    } else {
        log_debug("Host raw hid poll with no data\n");
    }
    raw_hid_send(d, 4);
}
