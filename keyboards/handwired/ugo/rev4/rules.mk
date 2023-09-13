# This file intentionally left blank
CUSTOM_MATRIX=lite

EEPROM_DRIVER=wear_leveling
WEAR_LEVELING_DRIVER=spi_flash
FLASH_DRIVER = spi

QUANTUM_LIB_SRC += spi_master.c

SRC += matrix.c
