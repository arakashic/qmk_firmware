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
    gpio_set_pin_output(REGISTER_CS_PIN);
    gpio_write_pin_high(REGISTER_CS_PIN);
    gpio_set_pin_output(REGISTER_LD_PIN);
    gpio_write_pin_high(REGISTER_LD_PIN);
    memset(buf_curr, 0, REGISTER_BYTES);
    memset(buf_in, 0, REGISTER_BYTES);

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;
    bool ret = true;

    // Set row, read cols
    spi_status_t spi_ret = SPI_STATUS_SUCCESS;

    gpio_write_pin_low(REGISTER_LD_PIN);
    matrix_output_select_delay();
    gpio_write_pin_high(REGISTER_LD_PIN);
    matrix_io_delay();

    ret = spi_start(REGISTER_CS_PIN, false, 0, 64);
    if (ret) {
        // spi_receive(buf_in, REGISTER_BYTES);
        spi_ret = spi_receive(buf_in, REGISTER_BYTES);
        if (spi_ret != SPI_STATUS_SUCCESS) {
            printf("SPI read error\n");
        }
    } else {
        printf("SPI start error\n");
    }
    spi_stop();

    for (int i =  0; i < REGISTER_BYTES; i++) {
        buf_in[i] = ~buf_in[i];
    }

    // If the row has changed, store the row and return the changed flag.
    if (memcmp(buf_curr, buf_in, REGISTER_BYTES) != 0) {
        memcpy(buf_curr, buf_in, REGISTER_BYTES);
        changed = true;
    }

    raw_matrix[0] = ((uint16_t) buf_curr[0]) | (((uint16_t) buf_curr[6]) << 8);
    raw_matrix[1] = ((uint16_t) buf_curr[1]) | (((uint16_t) buf_curr[7]) << 8);
    raw_matrix[2] = ((uint16_t) buf_curr[2]) | (((uint16_t) buf_curr[8]) << 8);
    raw_matrix[3] = ((uint16_t) buf_curr[3]) | (((uint16_t) buf_curr[9]) << 8);
    raw_matrix[4] = ((uint16_t) buf_curr[4]) | (((uint16_t) buf_curr[10]) << 8);
    raw_matrix[5] = ((uint16_t) buf_curr[5]) | (((uint16_t) buf_curr[11]) << 8);
    raw_matrix[6] =                      0x0 | (((uint16_t) buf_curr[12]) << 8);
    //
    // printf("%s\n", (changed ? "true" : "false"));
    //
    // changed = false;

    // wait_us(1000000);
    // for (int i = 0; i < REGISTER_BYTES; i++) {
    //     printf("0x%x ", buf_in[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < MATRIX_ROWS; i++) {
    //     printf("0x%x\n", raw_matrix[i]);
    // }
    // if (changed) {
    //     printf("changed\n");
    // }
    // changed = false;

    memcpy(current_matrix, raw_matrix, MATRIX_ROWS * sizeof(uint64_t));

    // debounce(raw_matrix, current_matrix, MATRIX_ROWS, changed);

    return changed;
}
