#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "spi_master.h"

extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

uint8_t buf_in[REGISTER_BYTES];
uint8_t buf_curr[REGISTER_BYTES];

void matrix_init_custom(void) {
    // initialize key pins
    spi_init();
    wait_us(1000);
    setPinOutput(REGISTER_CS_PIN);
    writePinHigh(REGISTER_CS_PIN);
    setPinOutput(REGISTER_LD_PIN);
    writePinHigh(REGISTER_LD_PIN);
    memset(buf_curr, 0, REGISTER_BYTES);
    memset(buf_in, 0, REGISTER_BYTES);

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);
}

bool matrix_scan_custom(void) {
    bool changed = false;
    bool ret = true;

    // Set row, read cols
    spi_status_t spi_ret = SPI_STATUS_SUCCESS;

    writePinLow(REGISTER_LD_PIN);
    wait_us(10);
    writePinHigh(REGISTER_LD_PIN);
    // FIXME: 5-10 us latency might be sufficient given the 100 MHz freq of F411
    wait_us(100);
    ret = spi_start(REGISTER_CS_PIN, false, 0, 64);
    if (ret) {
        // spi_receive(buf_in, REGISTER_BYTES);
        spi_ret = spi_receive(buf_in, REGISTER_BYTES);
        if (spi_ret == SPI_STATUS_SUCCESS) {
            printf("SPI read: ");
            for (int i = 0; i< REGISTER_BYTES; i++) {
                printf("0x%x ", buf_in[i]);
            }
            printf("\n");
        } else {
            printf("SPI read error\n");
        }
    } else {
        printf("SPI start error\n");
    }
    spi_stop();

    // If the row has changed, store the row and return the changed flag.
    if (memcmp(buf_curr, buf_in, REGISTER_BYTES) != 0) {
        memcpy(buf_curr, buf_in, REGISTER_BYTES);
        changed = true;
    }
    changed = false;

    printf("%s\n", (changed ? "true" : "false"));
    wait_us(100000);

    raw_matrix[0] = buf_curr[0] & 0x0F;
    raw_matrix[1] = (buf_curr[0] & 0xF0) >> 4;
    raw_matrix[2] = buf_curr[1] & 0x0F;
    raw_matrix[3] = (buf_curr[1] & 0xF0) >> 4;

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    return changed;
}
