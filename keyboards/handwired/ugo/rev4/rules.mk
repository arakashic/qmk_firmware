# This file intentionally left blank
CUSTOM_MATRIX=lite

KEYBOARD_SHARED_EP=yes

JOYSTICK_ENABLE=yes
JOYSTICK_DRIVER=digital

MULTIAXIS_ENABLE=yes
MULTIAXIS_DRIVER=digital

# EEPROM_DRIVER=wear_leveling
# WEAR_LEVELING_DRIVER=spi_flash
FLASH_DRIVER = spi

XAP_ENABLE=yes

QUANTUM_LIB_SRC += spi_master.c

SRC += matrix.c
