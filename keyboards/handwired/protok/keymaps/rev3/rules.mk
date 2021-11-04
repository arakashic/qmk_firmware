# MCU name
MCU = STM32F411
BOARD = BLACKPILL_STM32_F411
BOOTLOADER = stm32-dfu

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
CUSTOM_MATRIX = lite
ENCODER_ENABLE = yes
THUMBSTICK_ENABLE = yes

KEYBOARD_SHARED_EP = yes
# F411 only have 3 endpoints, disable this for now. Will need to merge with console
RAW_ENABLE = yes
EEPROM_DRIVER = i2c
# TAP_DANCE_ENABLE = yes
# need to define it here to avoid qmk build problem
# JOYSTICK_ENABLE = analog

SRC += matrix.c \
       MCP23x17.c

QUANTUM_LIB_SRC = i2c_master.c

# OPT_DEFS += -DREV3
OPT_DEFS += -DREV3 -DI2C_EEPROM
# OPT_DEFS += -DREV3 -DSPI_EEPROM

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    SRC += log.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DTHUMBSTICK_ENABLE
    SRC += analog.c
    SRC += thumbstick.c
endif

ifeq ($(strip $(RAW_ENABLE)), yes)
    OPT_DEFS += -DRAW_ENABLE
    SRC += raw.c
endif

