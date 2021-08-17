
#include "MCP23017.h"
#include "i2c_master.h"

#define I2C_STATUS_CHECK(var) \
    do { \
        switch ((var)) { \
        case I2C_STATUS_TIMEOUT: \
            uprintf("I2C op timeout\n"); \
            goto fn_fail; \
            break; \
        case I2C_STATUS_ERROR: \
            uprintf("I2C op error\n"); \
            goto fn_fail; \
            break; \
        case I2C_STATUS_SUCCESS: \
            break; \
        default: \
            uprintf("I2C op other failure\n"); \
            goto fn_fail; \
            break; \
        } \
    } while(0)

#define HIGH 1
#define LOW 0

#define MCP_WRITE 0x00
#define MCP_READ 0x01
#define MCP_CMD 0b01000000
#define MCP_ADDR_WRITE(dev) (MCP_CMD | (dev)->addr_s | MCP_WRITE)
#define MCP_ADDR_READ(dev) (MCP_CMD | (dev)->addr_s | MCP_READ)

i2c_status_t mcp_status = I2C_STATUS_SUCCESS;

void mcp_init_dev(MCP23017_t *dev, uint8_t addr)
{
    dev->addr = addr;
    dev->addr_s = (addr & 0b0111) << 1;

    dev->reg[MCP_IODIRA] = 0xFF;
    dev->reg[MCP_IODIRB] = 0xFF;
    dev->reg[MCP_IPOLA] = 0x00;
    dev->reg[MCP_IPOLB] = 0x00;
    dev->reg[MCP_GPINTENA] = 0x00;
    dev->reg[MCP_GPINTENB] = 0x00;
    dev->reg[MCP_DEFVALA] = 0x00;
    dev->reg[MCP_DEFVALB] = 0x00;
    dev->reg[MCP_INTCONA] = 0x00;
    dev->reg[MCP_INTCONB] = 0x00;
    dev->reg[MCP_IOCONA] = 0x18;
    dev->reg[MCP_IOCONB] = 0x18;
    dev->reg[MCP_GPPUA] = 0x00;
    dev->reg[MCP_GPPUB] = 0x00;
    dev->reg[MCP_INTFA] = 0x00;
    dev->reg[MCP_INTFB] = 0x00;
    dev->reg[MCP_INTCAPA] = 0x00;
    dev->reg[MCP_INTCAPB] = 0x00;
    dev->reg[MCP_GPIOA] = 0x00;
    dev->reg[MCP_GPIOB] = 0x00;
    dev->reg[MCP_OLATA] = 0x00;
    dev->reg[MCP_OLATB] = 0x00;
}

void mcp_read_register(MCP23017_t *dev, uint8_t addr) {
    mcp_status = i2c_readReg(MCP_ADDR_READ(dev), addr, &dev->reg[addr], sizeof(uint8_t), 1000);
    I2C_STATUS_CHECK(mcp_status);

  fn_exit:
    return;
  fn_fail:
    i2c_stop();
    goto fn_exit;
}

void mcp_write_register(MCP23017_t *dev, uint8_t addr, uint8_t value) {
    mcp_status = i2c_writeReg(MCP_ADDR_WRITE(dev), addr, &value, sizeof(uint8_t), 1000);
    I2C_STATUS_CHECK(mcp_status);

    dev->reg[addr] = value;

  fn_exit:
    return;
  fn_fail:
    i2c_stop();
    goto fn_exit;
}

void mcp_read_all(MCP23017_t *dev)
{
    mcp_status = i2c_readReg(MCP_ADDR_READ(dev), 0x0, dev->reg, MCP_NUM_REGS * sizeof(uint8_t), 1000);
    I2C_STATUS_CHECK(mcp_status);

  fn_exit:
    return;
  fn_fail:
    i2c_stop();
    goto fn_exit;
}

void mcp_print_all(MCP23017_t *dev)
{
    if (mcp_status != I2C_STATUS_SUCCESS) {
        uprintf("mcp_print_all: MCP_STATUS == ERROR\n");
        return;
    }
    uprintf("MCP reg: ");
    for (uint8_t i = 0; i < MCP_NUM_REGS; ++i) {
        uprintf("[%u]=%u ", i, dev->reg[i]);
    }
    uprintf("\n");
}

uint8_t mcp_read_port(MCP23017_t *dev, uint8_t port)
{
    if (port == MCP_PORTA) {
        mcp_read_register(dev, MCP_GPIOA);
        return dev->reg[MCP_GPIOA];
    } else {
        mcp_read_register(dev, MCP_GPIOB);
        return dev->reg[MCP_GPIOB];
    }
}
