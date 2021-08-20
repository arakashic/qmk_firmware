#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

/* matrix state(1:on, 0:off) */

extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputHigh(pin); }
}

static inline void setPinInputLow_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { setPinInputLow(pin); }
}

#ifdef MATRIX_USE_COL_MUL
/* only for COL2ROW diode direction */
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_addr_pins[MATRIX_COL_ADDR_BITS] = MATRIX_COL_ADDR_PINS;

// matrix code

static void select_row(uint8_t row) { setPinOutput_writeLow(row_pins[row]); }

static void unselect_row(uint8_t row) { setPinInputHigh_atomic(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

static inline void setColPinAddr(uint8_t addr) {
    ATOMIC_BLOCK_FORCEON {
        uint8_t mask = 0x1;
        for (uint8_t pin_bit = 0; pin_bit < MATRIX_COL_ADDR_BITS; pin_bit++) {
            writePin(col_addr_pins[pin_bit], addr & mask);
            mask = (mask << 1);
        }
    }
}

static void init_pins(void) {
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COL_ADDR_BITS; x++) {
        setPinOutput(col_addr_pins[x]);
    }
    setPinInputHigh_atomic(MATRIX_COL_SIG_PIN);
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
        setColPinAddr(col_index);
        // Wait for propagation
        wait_us(1);
        uint8_t pin_state = readPin(MATRIX_COL_SIG_PIN);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay();  // wait for all Col signals to go HIGH

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan_custom(void) {
    bool changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return (uint8_t)changed;
}

#endif /* MATRIX_USE_COL_MUL */

#ifdef MATRIX_USE_COL_23017

#define MCP23017

#include "MCP23x17.h"
#include "i2c_master.h"
/* only for COL2ROW diode direction, cols as input accept active low */
MCP23017_t matrix_col_dev;

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

// matrix code

static void select_row(uint8_t row) { setPinOutput_writeLow(row_pins[row]); }

static void unselect_row(uint8_t row) { setPinInputHigh_atomic(row_pins[row]); }

static void init_pins(void) {
    i2c_init();
    wait_us(1000);
    /* force reset */
    mcp_init_dev(&matrix_col_dev, 0U);
    /* PORT A/B output, PORT A as row select, PORT B as col read */
    mcp_write_register(&matrix_col_dev, MCP_IOCONA, 0b00001000);
    mcp_write_register(&matrix_col_dev, MCP_IOCONB, 0b00001000);
    mcp_write_register16(&matrix_col_dev, MCP_IODIRA, 0xFFFFu);
    mcp_write_register16(&matrix_col_dev, MCP_GPPUA, 0xFFFFu);
    wait_us(10);
    mcp_read_all(&matrix_col_dev);
    mcp_save_mode(&matrix_col_dev);
    wait_us(10);
    /* setup rows */
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;
    uint16_t data = 0;

    /* mcp_write_port16(&matrix_col_dev, 0xffffu); */
    /* wait_us(10); */

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    /* wait_us(10); */
    data = mcp_read_port16(&matrix_col_dev);
    /* if (data != 0xFFFFu) { */
    /*     uprintf("row %d value %x\n", current_row, ~data); */
    /* } */
    current_row_value = ~data;

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay();  // wait for all Col signals to go HIGH

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

void matrix_init_custom(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan_custom(void) {
    bool changed = false;

    /* static uint16_t time_elapsed; */
    /* time_elapsed = timer_read(); */

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();

    /* time_elapsed = timer_read() - time_elapsed; */
    /* uprintf("time elapsed %d ms\n", time_elapsed); */

    return (uint8_t)changed;
}

#endif
