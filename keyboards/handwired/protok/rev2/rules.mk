# MCU name
MCU = STM32F303
BOARD = QMK_PROTON_C

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
# BOOTLOADER = qmk-dfu

# Build Options
#   comment out to disable the options.
#
BOOTMAGIC_ENABLE = yes		# Virtual DIP switch configuration
MOUSEKEY_ENABLE = yes		# Mouse keys
EXTRAKEY_ENABLE = yes		# Audio control and System control
CONSOLE_ENABLE = yes		# Console for debug
COMMAND_ENABLE = yes		# Commands for debug and configuration, diable because of
                                # conflicting with space cadet key
# KEYBOARD_LOCK_ENABLE = yes	# Allow locking of keyboard via magic key
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes	# Breathing sleep LED during USB suspend
NKRO_ENABLE = yes			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes	# Enable keyboard backlight functionality
# MIDI_ENABLE = YES			# MIDI controls
# UNICODE_ENABLE = YES		# Unicode
# BLUETOOTH_ENABLE = yes	# Enable Bluetooth with the Adafruit EZ-Key HID
# TERMINAL_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
AUDIO_ENABLE = yes
AUDIO_DRIVER = dac_basic
CUSTOM_MATRIX = lite
ENCODER_ENABLE = yes
THUMBSTICK_ENABLE = yes
RAW_ENABLE = yes

SRC += matrix.c \
       MCP23x17.c

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

ifeq ($(strip $(RAW_ENABLE)), yes)
    OPT_DEFS += -DRAW_ENABLE
    SRC += raw.c
endif

