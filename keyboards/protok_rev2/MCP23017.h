#ifndef _MCP23017_H
#define _MCP23017_H

#include <stdint.h>
#include <stdbool.h>
#include "util.h"
#include "quantum.h"

#define MCP_PORTA 0
#define MCP_PORTB 1

enum {
    MCP_PIN_OUTPUT = 0,
    MCP_PIN_INPUT,
    MCP_PIN_INPUT_PULLUP
};

enum {
    MCP_PIN_A0 = 0,
    MCP_PIN_A1,
    MCP_PIN_A2,
    MCP_PIN_A3,
    MCP_PIN_A4,
    MCP_PIN_A5,
    MCP_PIN_A6,
    MCP_PIN_A7,
    MCP_PIN_B0,
    MCP_PIN_B1,
    MCP_PIN_B2,
    MCP_PIN_B3,
    MCP_PIN_B4,
    MCP_PIN_B5,
    MCP_PIN_B6,
    MCP_PIN_B7,
    MCP_NUM_PINS
};

enum MCP23017_regs {
    MCP_IODIRA,     MCP_IODIRB,
    MCP_IPOLA,      MCP_IPOLB,
    MCP_GPINTENA,   MCP_GPINTENB,
    MCP_DEFVALA,    MCP_DEFVALB,
    MCP_INTCONA,    MCP_INTCONB,
    MCP_IOCONA,     MCP_IOCONB,
    MCP_GPPUA,      MCP_GPPUB,
    MCP_INTFA,      MCP_INTFB,
    MCP_INTCAPA,    MCP_INTCAPB,
    MCP_GPIOA,      MCP_GPIOB,
    MCP_OLATA,      MCP_OLATB,
    MCP_NUM_REGS
};

typedef struct MCP23017 {
    uint8_t addr;  /* 3-bit chip address */
    uint8_t addr_s;  /* shifted ready to use address */

    uint8_t reg[MCP_NUM_REGS];   /* copy of the 22 internal registers of MCP23017 */
} MCP23017_t;

void mcp_init_dev(MCP23017_t *dev, uint8_t addr);

void mcp_read_register(MCP23017_t *dev, uint8_t addr);
void mcp_write_register(MCP23017_t *dev, uint8_t addr, uint8_t value);
void mcp_read_all(MCP23017_t *dev);
/* void mcp_write_all(MCP23017_t *dev); */
uint8_t mcp_read_port(MCP23017_t *dev, uint8_t port);

/* void mcp_begin(MCP23017_t *dev); */
/* void mcp_pin_mode(MCP23017_t *dev, uint8_t pin, uint8_t mode); */
/* void mcp_write_pin(MCP23017_t *dev, uint8_t pin, uint8_t value); */
/* uint8_t mcp_read_pin(MCP23017_t *dev, uint8_t pin); */

/* uint8_t mcp_read_port(MCP23017_t *dev, uint8_t port); */
/* uint16_t mcp_read_allport(MCP23017_t *dev); */
/* void mcp_write_port(MCP23017_t *dev, uint8_t port, uint8_t val); */
/* void mcp_write_allport(MCP23017_t *dev, uint16_t val); */

void mcp_print_all(MCP23017_t *dev);

#endif
