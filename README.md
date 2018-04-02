# Nightlight

A simple Arduino-powered nightlight.

## Parts List
Part | Price/Source
-----|-------------
Arduino Uno R3 | [AU$54.89](https://www.littlebirdelectronics.com.au/arduino-uno-r3) |
Neopixel Shield | [US$27.95](https://www.adafruit.com/product/1430) |

### Configuration

Change these variables to alter how the light works.

**const int contrast** (Default: 10)

Increases the contrast between 1 pixel and the next when transitioning. The lower the number, the lower the contrast.

**const float theta** (Default: 0.025)

The lower the number, the slower the transition through the colour spectrum.

**const int brightness** (Default: 64)

Sets the brightness of the LEDS. Use an integer between 1 and 255. WARNING: Setting the brightness to high could result in the board freezing as it drains a lot of power.

**long timeout** (Default: 3,600,000ms or 1 hour)

This determines how long the shield will animate. Once this timeout has passed, it will turn off all the LEDs.

**Pattern pattern** (Default: DIAGONAL_WIPE)

An enumerator that determines how the LEDs animate. There are 4 options.
+ WIPE (left to right)
+ DIAGONAL_WIPE (top left to bottom right)
+ RADIAL (center to outside)
+ and RAINBOW_STRIPE (each row cycles through, starting at a different fifth of the spectrum giving a rainbow effect)

![Photo](https://github.com/struct78/nightlight/raw/develop/images/nightlight.jpg)
