# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
AUDIO_ENABLE = yes
AUDIO_DRIVER = dac_basic
CUSTOM_MATRIX = lite
ENCODER_ENABLE = yes
THUMBSTICK_ENABLE = yes
RAW_ENABLE = yes
EEPROM_DRIVER = i2c
# TAP_DANCE_ENABLE = yes
# need to define it here to avoid qmk build problem
# JOYSTICK_ENABLE = analog

SRC += matrix.c \
       MCP23x17.c

QUANTUM_LIB_SRC = i2c_master.c

OPT_DEFS += -DREV2 -DI2C_EEPROM

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

