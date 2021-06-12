
#include "MCP23S17.h"
#include "spi_master.h"

#define SPI_STATUS_CHECK(var, val) \
    do { \
        if ((var) != (val)) goto fn_fail; \
    } while(0)

#define HIGH 1
#define LOW 0

static inline bool mcp_spi_start(MCP23S17_t *dev);

static inline bool mcp_spi_start(MCP23S17_t *dev)
{
    bool rc = true;
    rc = spi_start(dev->cs, false /* msbFirst */, 0, 90 /* 0.8 MHz */);
    if (!rc) {
        uprintf("Cannot start device\n");
    /* } else { */
    /*     wait_us(150); */
    }
    return rc;
}

void mcp_init_dev(MCP23S17_t *dev, pin_t cs, uint8_t addr)
{
    dev->cs = cs;
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

/*! The begin function performs the initial configuration of the IO expander chip.
 *  Not only does it set up the SPI communications, but it also configures the chip
 *  for address-based communication and sets the default parameters and registers
 *  to sensible values.
 *
 *  Example:
 *
 *      myExpander.begin();
 *
 */
void mcp_begin(MCP23S17_t *dev) {
    spi_status_t rc = SPI_STATUS_SUCCESS;
    uint8_t stage = 0;
    if (mcp_spi_start(dev)) {
        uint8_t cmd = 0b01000000 | dev->addr_s;
        stage = 1;
        rc = spi_write(cmd);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        stage = 2;
        rc = spi_write(MCP_IOCONA);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        stage = 3;
        rc = spi_write(0x18);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        spi_stop();
    }
  fn_fail:
    uprintf("spi_write failed, stage %u\n", stage);
    spi_stop();
}

/*! This private function reads a value from the specified register on the chip and
 *  stores it in the _reg array for later usage.
 */
void mcp_read_register(MCP23S17_t *dev, uint8_t addr) {
    spi_status_t rc = SPI_STATUS_SUCCESS;
    uint8_t stage = 0;
    if (addr > 21) {
        return;
    }
    uint8_t cmd = 0b01000001 | dev->addr_s;
    if (mcp_spi_start(dev)) {
        stage = 1;
        rc = spi_write(cmd);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        stage = 2;
        rc = spi_write(addr);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        stage = 3;
        dev->reg[addr] = spi_read();
        spi_stop();
    }
  fn_fail:
    uprintf("spi_write failed, stage %u\n", stage);
    spi_stop();
}

/*! This private function writes the current value of a register (as stored in the
 *  _reg array) out to the register in the chip.
 */
void mcp_write_register(MCP23S17_t *dev, uint8_t addr) {
    spi_status_t rc = SPI_STATUS_SUCCESS;
    uint8_t stage = 0;
    if (addr > 21) {
        return;
    }
    uint8_t cmd = 0b01000000 | dev->addr_s;
    if (mcp_spi_start(dev)) {
        stage = 1;
        rc = spi_write(cmd);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        stage = 2;
        rc = spi_write(addr);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        stage = 3;
        rc = spi_write(dev->reg[addr]);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        spi_stop();
    }
  fn_fail:
    uprintf("spi_write failed, stage %u\n", stage);
    spi_stop();
}

/*! This private function performs a bulk read on all the registers in the chip to
 *  ensure the _reg array contains all the correct current values.
 */
void mcp_read_all(MCP23S17_t *dev) {
    spi_status_t rc = SPI_STATUS_SUCCESS;
    uint8_t cmd = 0b01000001 | dev->addr_s;
    if (mcp_spi_start(dev)) {
        rc = spi_write(cmd);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        rc = spi_write(0);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        for (uint8_t i = 0; i < MCP_NUM_REGS; i++) {
            dev->reg[i] = spi_read();
        }
        spi_stop();
    }
  fn_fail:
    uprintf("spi_write failed\n");
    spi_stop();
}

/*! This private function performs a bulk write of all the data in the _reg array
 *  out to all the registers on the chip.  It is mainly used during the initialisation
 *  of the chip.
 */
void mcp_write_all(MCP23S17_t *dev) {
    spi_status_t rc = SPI_STATUS_SUCCESS;
    uint8_t cmd = 0b01000000 | dev->addr_s;
    if (mcp_spi_start(dev)) {
        rc = spi_write(cmd);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        rc = spi_write(0);
        SPI_STATUS_CHECK(rc, SPI_STATUS_SUCCESS);
        for (uint8_t i = 0; i < MCP_NUM_REGS; i++) {
            spi_write(dev->reg[i]);
        }
        spi_stop();
    }
  fn_fail:
    uprintf("spi_write failed\n");
    spi_stop();
}

/*! Just like the pinMode() function of the Arduino API, this function sets the
 *  direction of the pin.  The first parameter is the pin nimber (0-15) to use,
 *  and the second parameter is the direction of the pin.  There are standard
 *  Arduino macros for different modes which should be used.  The supported macros are:
 *
 *  * OUTPUT
 *  * INPUT
 *  * INPUT_PULLUP
 *
 *  The INPUT_PULLUP mode enables the weak pullup that is available on any pin.
 *
 *  Example:
 *
 *      myExpander.pinMode(5, INPUT_PULLUP);
 */
void mcp_pin_mode(MCP23S17_t *dev, uint8_t pin, uint8_t mode) {
    if (pin >= MCP_NUM_PINS) {
        return;
    }
    uint8_t dirReg = MCP_IODIRA;
    uint8_t puReg = MCP_GPPUA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = MCP_IODIRB;
        puReg = MCP_GPPUB;
    }

    switch (mode) {
        case MCP_PIN_OUTPUT:
            dev->reg[dirReg] &= ~(1<<pin);
            mcp_write_register(dev, dirReg);
            break;

        case MCP_PIN_INPUT:
        case MCP_PIN_INPUT_PULLUP:
            dev->reg[dirReg] |= (1<<pin);
            mcp_write_register(dev, dirReg);
            if (mode == MCP_PIN_INPUT_PULLUP) {
                dev->reg[puReg] |= (1<<pin);
            } else {
                dev->reg[puReg] &= ~(1<<pin);
            }
            mcp_write_register(dev, puReg);
            break;
    }
}

/*! Like the Arduino API's namesake, this function will set an output pin to a specific
 *  value, either HIGH (1) or LOW (0).  If the pin is currently set to an INPUT instead of
 *  an OUTPUT, then this function acts like the old way of enabling / disabling the pullup
 *  resistor, which pre-1.0.0 versions of the Arduino API used - i.e., set HIGH to enable the
 *  pullup, or LOW to disable it.
 *
 *  Example:
 *
 *      myExpander.digitalWrite(3, HIGH);
 */
void mcp_write_pin(MCP23S17_t *dev, uint8_t pin, uint8_t value) {
    if (pin >= MCP_NUM_PINS) {
        return;
    }
    uint8_t dirReg = MCP_IODIRA;
    uint8_t puReg = MCP_GPPUA;
    uint8_t latReg = MCP_OLATA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = MCP_IODIRB;
        puReg = MCP_GPPUB;
        latReg = MCP_OLATB;
    }

    uint8_t mode = (dev->reg[dirReg] & (1<<pin)) == 0 ? MCP_PIN_OUTPUT : MCP_PIN_INPUT;

    switch (mode) {
        case MCP_PIN_OUTPUT:
            if (value == 0) {
                dev->reg[latReg] &= ~(1<<pin);
            } else {
                dev->reg[latReg] |= (1<<pin);
            }
            mcp_write_register(dev, latReg);
            break;

        case MCP_PIN_INPUT:
            if (value == 0) {
                dev->reg[puReg] &= ~(1<<pin);
            } else {
                dev->reg[puReg] |= (1<<pin);
            }
            mcp_write_register(dev, puReg);
            break;
    }
}

/*! This will return the current state of a pin set to INPUT, or the last
 *  value written to a pin set to OUTPUT.
 *
 *  Example:
 *
 *      byte value = myExpander.digitalRead(4);
 */
uint8_t mcp_read_pin(MCP23S17_t *dev, uint8_t pin) {
    if (pin >= MCP_NUM_PINS) {
        return 0;
    }
    uint8_t dirReg = MCP_IODIRA;
    uint8_t portReg = MCP_GPIOA;
    uint8_t latReg = MCP_OLATA;
    if (pin >= 8) {
        pin -= 8;
        dirReg = MCP_IODIRB;
        portReg = MCP_GPIOB;
        latReg = MCP_OLATB;
    }

    uint8_t mode = (dev->reg[dirReg] & (1<<pin)) == 0 ? MCP_PIN_OUTPUT : MCP_PIN_INPUT;

    switch (mode) {
        case MCP_PIN_OUTPUT:
            return dev->reg[latReg] & (1<<pin) ? HIGH : LOW;
        case MCP_PIN_INPUT:
            mcp_read_register(dev, portReg);
            return dev->reg[portReg] & (1<<pin) ? HIGH : LOW;
    }
    return 0;
}

/*! This function returns the entire 8-bit value of a GPIO port.  Note that
 *  only the bits which correspond to a GPIO pin set to INPUT are valid.
 *  Other pins should be ignored.  The only parameter defines which port (A/B)
 *  to retrieve: 0 is port A and 1 (or anything other than 0) is port B.
 *
 *  Example:
 *
 *      byte portA = myExpander.readPort(0);
 */
uint8_t mcp_read_port(MCP23S17_t *dev, uint8_t port) {
    if (port == MCP_PORTA) {
        mcp_read_register(dev, MCP_GPIOA);
        return dev->reg[MCP_GPIOA];
    } else {
        mcp_read_register(dev, MCP_GPIOB);
        return dev->reg[MCP_GPIOB];
    }
}

/*! This is a full 16-bit version of the parameterised readPort function.  This
 *  version reads the value of both ports and combines them into a single 16-bit
 *  value.
 *
 *  Example:
 *
 *      unsigned int value = myExpander.readPort();
 */
uint16_t mcp_read_allport(MCP23S17_t *dev) {
    mcp_read_register(dev, MCP_GPIOA);
    mcp_read_register(dev, MCP_GPIOB);
    return (dev->reg[MCP_GPIOB] << 8) | dev->reg[MCP_GPIOA];
}

/*! This writes an 8-bit value to one of the two IO port banks (A/B) on the chip.
 *  The value is output direct to any pins on that bank that are set as OUTPUT. Any
 *  bits that correspond to pins set to INPUT are ignored.  As with the readPort
 *  function the first parameter defines which bank to use (0 = A, 1+ = B).
 *
 *  Example:
 *
 *      myExpander.writePort(0, 0x55);
 */
void mcp_write_port(MCP23S17_t *dev, uint8_t port, uint8_t val) {
    if (port == MCP_PORTA) {
        dev->reg[MCP_OLATA] = val;
        mcp_write_register(dev, MCP_OLATA);
    } else {
        dev->reg[MCP_OLATB] = val;
        mcp_write_register(dev, MCP_OLATB);
    }
}

/*! This is the 16-bit version of the writePort function.  This takes a single
 *  16-bit value and splits it between the two IO ports, the upper half going to
 *  port B and the lower to port A.
 *
 *  Example:
 *
 *      myExpander.writePort(0x55AA);
 */
void mcp_write_allport(MCP23S17_t *dev, uint16_t val) {
    dev->reg[MCP_OLATB] = val >> 8;
    dev->reg[MCP_OLATA] = val & 0xFF;
    mcp_write_register(dev, MCP_OLATA);
    mcp_write_register(dev, MCP_OLATB);
}

void mcp_print_all(MCP23S17_t *dev)
{
    uprintf("MCP reg: ");
    for (uint8_t i = 0; i < MCP_NUM_REGS; ++i) {
        uprintf("[%u]=%u ", i, dev->reg[i]);
    }
    uprintf("\n");
}
