# MCU name
MCU = STM32F411
BOARD = BLACKPILL_STM32_F411
BOOTLOADER = stm32-dfu

OLED_ENABLE = yes
OLED_DRIVER = ssd1306
CUSTOM_MATRIX = lite
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
# THUMBSTICK_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
PROGRAMMABLE_BUTTON_ENABLE = yes

OS_DETECTION_ENABLE = yes
OS_DETECTION_DEBUG_ENABLE = yes

KEYBOARD_SHARED_EP = yes
# F411 only have 3 endpoints, disable this for now. Will need to merge with console
EEPROM_DRIVER = i2c
# TAP_DANCE_ENABLE = yes
# need to define it here to avoid qmk build problem
# JOYSTICK_ENABLE = analog

SRC += matrix.c \
       analog.c \
       MCP23x17.c \
	   rpt_macro.c

QUANTUM_LIB_SRC = i2c_master.c

ifeq ($(strip $(CONSOLE_ENABLE)), yes)
    SRC += log.c
endif

ifeq ($(strip $(THUMBSTICK_ENABLE)), yes)
    POINTING_DEVICE_ENABLE = yes
    OPT_DEFS += -DTHUMBSTICK_ENABLE
    SRC += analog.c
    SRC += thumbstick.c
endif
