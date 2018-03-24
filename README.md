# Nightlight

A simple Arduino-powered nightlight.

## Parts List
Part | Price/Source
-----|-------------
Arduino Uno R3 | [AU$54.89](https://www.littlebirdelectronics.com.au/arduino-uno-r3) |
Neopixel Shield | [US$27.95](https://www.adafruit.com/product/1430) |

### Configuration

Change these variables to alter how the light works.

**const int contrast**

Increases the contrast between 1 pixel and the next when transitioning.
Default: 1

**const float theta**

The lower the number, the slower the transition through the colour spectrum.
Default: 0.025

**int brightness**

Sets the brightness of the LEDS. Use an integer between 1 and 255. WARNING: Setting the brightness to high could result in the board freezing as it drains a lot of power.
Default: 128;

**int powerSavingBrightness**

Sets the brightness of the shield when the timeout has passed and the board has gone into power saving mode.
Default: 5

**long timeout**

This determines how long the shield will animate at full power. Once this timeout has passed, it will transition to power saving mode.
Default: 1 hour (3600000 milliseconds)

**Pattern pattern**

An enumerator that determines how the LEDs animate. There are 3 options. Wipe (left to right), Radial (center to outside), and Pulse (like Radial but with rising/falling brightness)
Default: RADIAL
