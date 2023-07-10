# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = halfkay

# KEYBOARD_LOCK_ENABLE = yes	# Allow locking of keyboard via magic key
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
# SLEEP_LED_ENABLE = yes	# Breathing sleep LED during USB suspend
NKRO_ENABLE = yes			# USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = yes	# Enable keyboard backlight functionality
# MIDI_ENABLE = YES			# MIDI controls
# UNICODE_ENABLE = YES		# Unicode
# BLUETOOTH_ENABLE = yes	# Enable Bluetooth with the Adafruit EZ-Key HID
# TERMINAL_ENABLE = yes
# OLED_ENABLE = yes

OPT_DEFS += -DREV1

