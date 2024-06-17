
#include "MCP23x17.h"
#include "log.h"

#include "i2c_master.h"

#define I2C_TIMEOUT 100

#define I2C_STATUS_CHECK(var) \
    do { \
        switch ((var)) { \
        case I2C_STATUS_TIMEOUT: \
            log_error("I2C op timeout\n"); \
            goto fn_fail; \
            break; \
        case I2C_STATUS_ERROR: \
            log_error("I2C op error\n"); \
            goto fn_fail; \
            break; \
        case I2C_STATUS_SUCCESS: \
            break; \
        default: \
            log_error("I2C op other failure\n"); \
            goto fn_fail; \
            break; \
        } \
    } while(0)

#define HIGH 1
#define LOW 0

#define MCP_SEQ_MODE_ON(dev) ((dev)->reg[MCP_IOCONA] & 0b00001000)

i2c_status_t mcp_status = I2C_STATUS_SUCCESS;

void mcp_init_dev(MCP23017_t *dev, uint8_t addr) {
    dev->addr_s = (addr & 0b0111) << 1;
    dev->state_saved = false;

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

    dev->saved_reg[MCP_IODIRA] = 0x00;
    dev->saved_reg[MCP_IODIRB] = 0x00;
    dev->saved_reg[MCP_IPOLA] = 0x00;
    dev->saved_reg[MCP_IPOLB] = 0x00;
    dev->saved_reg[MCP_GPINTENA] = 0x00;
    dev->saved_reg[MCP_GPINTENB] = 0x00;
    dev->saved_reg[MCP_DEFVALA] = 0x00;
    dev->saved_reg[MCP_DEFVALB] = 0x00;
    dev->saved_reg[MCP_INTCONA] = 0x00;
    dev->saved_reg[MCP_INTCONB] = 0x00;
    dev->saved_reg[MCP_IOCONA] = 0x00;
    dev->saved_reg[MCP_IOCONB] = 0x00;
    dev->saved_reg[MCP_GPPUA] = 0x00;
    dev->saved_reg[MCP_GPPUB] = 0x00;
    dev->saved_reg[MCP_INTFA] = 0x00;
    dev->saved_reg[MCP_INTFB] = 0x00;
    dev->saved_reg[MCP_INTCAPA] = 0x00;
    dev->saved_reg[MCP_INTCAPB] = 0x00;
    dev->saved_reg[MCP_GPIOA] = 0x00;
    dev->saved_reg[MCP_GPIOB] = 0x00;
    dev->saved_reg[MCP_OLATA] = 0x00;
    dev->saved_reg[MCP_OLATB] = 0x00;
}

void mcp_save_mode(MCP23017_t *dev) {
    for (uint8_t i = 0; i < MCP_NUM_REGS; ++i) {
        dev->saved_reg[i] = dev->reg[i];
    }
    dev->saved_reg[MCP_GPIOA] = dev->saved_reg[MCP_OLATA];
    dev->saved_reg[MCP_GPIOB] = dev->saved_reg[MCP_OLATB];
    dev->state_saved = true;
}

void mcp_reset(MCP23017_t *dev) {
    if (!dev->state_saved) {
        return;
    }
    mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), MCP_IOCONA, &dev->saved_reg[MCP_IOCONA], 1, I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);
    mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), MCP_IOCONB, &dev->saved_reg[MCP_IOCONB], 1, I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);
    mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), MCP_IODIRA, dev->saved_reg, MCP_NUM_REGS, I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);

  fn_exit:
    return;
  fn_fail:
    log_debug("failed in mcp reset\n");
    goto fn_exit;
}

void mcp_read_register(MCP23017_t *dev, uint8_t addr) {
    mcp_status = i2c_read_register(MCP_ADDR_READ(dev), addr, &dev->reg[addr], sizeof(uint8_t), I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);

  fn_exit:
    return;
  fn_fail:
    log_debug("mcp_read_register\n");
    mcp_reset(dev);
    goto fn_exit;
}

void mcp_read_register16(MCP23017_t *dev, uint8_t addr) {
    uint8_t data[2] = { 0, 0 };
    if (!MCP_SEQ_MODE_ON(dev)) {
        log_error("Cannot operate 16 bit register without sequential mode enabled.\n");
        return;
    }
    mcp_status = i2c_read_register(MCP_ADDR_READ(dev), addr, data, 2 * sizeof(uint8_t), I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);

    dev->reg[addr] = data[0];
    dev->reg[addr+1] = data[1];

  fn_exit:
    return;
  fn_fail:
    log_debug("mcp_read_register16\n");
    mcp_reset(dev);
    goto fn_exit;
}

void mcp_write_register(MCP23017_t *dev, uint8_t addr, uint8_t value) {
    mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), addr, &value, sizeof(uint8_t), I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);

    dev->reg[addr] = value;

  fn_exit:
    return;
  fn_fail:
    log_debug("mcp_write_register\n");
    mcp_reset(dev);
    goto fn_exit;
}

void mcp_write_register16(MCP23017_t *dev, uint8_t addr, uint16_t value) {
    uint8_t data[2] = { value & 0x00ff, (value & 0xff00) >> 8 };
    if (!MCP_SEQ_MODE_ON(dev)) {
        log_error("Cannot operate 16 bit register without sequential mode enabled.\n");
        return;
    }
    mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), addr, data, 2 * sizeof(uint8_t), I2C_TIMEOUT);
    I2C_STATUS_CHECK(mcp_status);

    dev->reg[addr] = data[0];
    dev->reg[addr+1] = data[1];

  fn_exit:
    return;
  fn_fail:
    log_debug("mcp_write_register16\n");
    mcp_reset(dev);
    goto fn_exit;
}

void mcp_read_all(MCP23017_t *dev) {
    int i = 0;
    if (MCP_SEQ_MODE_ON(dev)) {
        mcp_status = i2c_read_register(MCP_ADDR_READ(dev), MCP_IODIRA, dev->reg,
                                 MCP_NUM_REGS * sizeof(uint8_t), I2C_TIMEOUT);
        I2C_STATUS_CHECK(mcp_status);
    } else {
        for (i = 0; i < MCP_NUM_REGS; i++) {
            mcp_status = i2c_read_register(MCP_ADDR_READ(dev), i, &dev->reg[i], sizeof(uint8_t), I2C_TIMEOUT);
            I2C_STATUS_CHECK(mcp_status);
        }
    }

  fn_exit:
    return;
  fn_fail:
    mcp_reset(dev);
    goto fn_exit;
}

void mcp_write_all(MCP23017_t *dev) {
    int i = 0;
    if (MCP_SEQ_MODE_ON(dev)) {
        mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), MCP_IODIRA, dev->reg,
                                  MCP_NUM_REGS * sizeof(uint8_t), I2C_TIMEOUT);
        I2C_STATUS_CHECK(mcp_status);
    } else {
        for (i = 0; i < MCP_NUM_REGS; i++) {
            mcp_status = i2c_write_register(MCP_ADDR_WRITE(dev), i, &dev->reg[i], sizeof(uint8_t), I2C_TIMEOUT);
            I2C_STATUS_CHECK(mcp_status);
        }
    }

  fn_exit:
    return;
  fn_fail:
    mcp_reset(dev);
    goto fn_exit;
}

void mcp_print_all(MCP23017_t *dev) {
    if (mcp_status != I2C_STATUS_SUCCESS) {
        log_debug("mcp_print_all: MCP_STATUS == ERROR\n");
        return;
    }
    log_debug("MCP reg: ");
    for (uint8_t i = 0; i < MCP_NUM_REGS; ++i) {
        log_debug("[%u]=%u ", i, dev->reg[i]);
    }
    log_debug("\n");
}

uint8_t mcp_read_port(MCP23017_t *dev, uint8_t port) {
    if (port == MCP_PORTA) {
        mcp_read_register(dev, MCP_GPIOA);
        return dev->reg[MCP_GPIOA];
    } else {
        mcp_read_register(dev, MCP_GPIOB);
        return dev->reg[MCP_GPIOB];
    }
}

void mcp_write_port(MCP23017_t *dev, uint8_t port, uint8_t value) {
    if (port == MCP_PORTA) {
        mcp_write_register(dev, MCP_GPIOA, value);
    } else {
        mcp_write_register(dev, MCP_GPIOB, value);
    }
}

uint16_t mcp_read_port16(MCP23017_t *dev) {
    uint16_t ret = 0;
    mcp_read_register16(dev, MCP_GPIOA);
    ret = dev->reg[MCP_GPIOA] | (dev->reg[MCP_GPIOB] << 8);
    return ret;
}

void mcp_write_port16(MCP23017_t *dev, uint16_t value) {
    mcp_write_register16(dev, MCP_GPIOA, value);
}
