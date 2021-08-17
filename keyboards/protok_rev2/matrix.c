#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "MCP23017.h"
#include "i2c_master.c"

/* matrix state(1:on, 0:off) */

extern MCP23017_t matrix_col_dev;

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

#ifdef MATRIX_USE_COL_IOEXT
#include "MCP23S17.h"
/* only for COL2ROW diode direction */
MCP23S17_t matrix_col_dev;      // debounced values

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

// matrix code

static void select_row(uint8_t row) { setPinOutput_writeLow(row_pins[row]); }

static void unselect_row(uint8_t row) { setPinInputHigh_atomic(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

static void init_pins(void) {
    /* force reset */
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(MATRIX_COL_RST_PIN);
        writePinHigh(MATRIX_COL_RST_PIN);
        wait_us(30);
        writePinLow(MATRIX_COL_RST_PIN);
        wait_us(30);
        writePinHigh(MATRIX_COL_RST_PIN);
        wait_us(32);
    }
    mcp_init_dev(&matrix_col_dev, MATRIX_COL_CS_PIN, 0U);
    mcp_begin(&matrix_col_dev);
    for (uint8_t i = 0; i < MCP_NUM_PINS; i++) {
        mcp_pin_mode(&matrix_col_dev, i, MCP_PIN_INPUT);
    }
    unselect_rows();
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    current_row_value = mcp_read_allport(&matrix_col_dev);
    uprintf("read_col: %b\n", current_row_value);

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

#endif /* MATRIX_USE_COL_IOEXT */

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

#include "MCP23017.h"
/* only for COL2ROW diode direction */
MCP23017_t matrix_col_dev;      // debounced values

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

// matrix code

static void select_row(uint8_t row) { setPinOutput_writeLow(row_pins[row]); }

static void unselect_row(uint8_t row) { setPinInputHigh_atomic(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

static void init_pins(void) {
    /* i2c_init(); */
    /* wait_ms(1000); */
    /* force reset */
    mcp_init_dev(&matrix_col_dev, 0U);
    /* mcp_begin(&matrix_col_dev); */
    /* for (uint8_t i = 0; i < MCP_NUM_PINS; i++) { */
    /*     mcp_pin_mode(&matrix_col_dev, i, MCP_PIN_INPUT); */
    /* } */
    unselect_rows();
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    /* uprintf("read\n"); */
    /* mcp_read_register(&matrix_col_dev, MCP_IOCONA); */
    /* mcp_print_all(&matrix_col_dev); */
    /* uprintf("read gpio\n"); */
    /* mcp_read_register(&matrix_col_dev, MCP_GPIOA); */
    /* mcp_print_all(&matrix_col_dev); */
    /* uprintf("write\n"); */
    /* mcp_write_register(&matrix_col_dev, MCP_IOCONA, 0x18); */
    /* mcp_print_all(&matrix_col_dev); */
    /* wait_ms(1000); */
    uint8_t data = mcp_read_port(&matrix_col_dev, MCP_PORTA);
    uprintf("port A=%d\n", data);

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

