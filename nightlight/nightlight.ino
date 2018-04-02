#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

enum Pattern {
  WIPE,
  DIAGONAL_WIPE,
  RADIAL,
  RAINBOW_STRIPE
};

const int cols = 8;
const int rows = 5;
const int pin = 6;
const int contrast = 10;
const float theta = 0.025; // Rate of colour change
const int brightness = 64;

Pattern pattern = DIAGONAL_WIPE;
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(rows, cols, pin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);

bool power = true;
long ticks = 0;
long timeout = 3600000; // 1 hour
float delta = 0;

void setup() {
  Serial.begin(115200);
  neomatrix_setup();
}

void loop() {
  neomatrix_loop();
}

/**
 * @name neomatrix_setup
 * @description Called from main setup()
 * @return {void}
**/
void neomatrix_setup() {
  matrix.begin();
  matrix.fillScreen(0);
  matrix.show();
}


/**
 * @name hue_to_rgb
 * @description Helper function for hsl_to_rgb. Converts hue degrees to RGB.
 * @param {float} p - Combination of lightness/brightness (0.0 - 1.0)
 * @param {float} q - Combination of lightness/brightness (0.0 - 1.0)
 * @param {float} t - Hue (0.0 - 1.0)
 * @return {float}
**/
float hue_to_rgb( float p, float q, float t ) {
  if ( t < 0 ) t += 1.0;
  if ( t > 1 ) t -= 1.0;
  if ( t < 1/6.0 ) return p + ( q - p ) * 6 * t;
  if ( t < 1/2.0 ) return q;
  if ( t < 2/3.0 ) return p + ( q - p ) * ( 2/3.0 - t ) * 6;
  return p;
}

/**
 * @name hsl_to_rgb
 * @description Converts HSL to RGB.
 * @param {float} h - Hue (0.0 - 1.0)
 * @param {float} s - Saturation (0.0 - 1.0)
 * @param {float} l - Lightness (0.0 - 1.0)
 * @return {Color}
**/
uint16_t hsl_to_rgb( float h, float s, float l ) {
    float r, g, b;

    if ( s == 0.0 ) {
      // No saturation, so it's grey
      r = g = b = l;
    } else {
        // If the lightness is less than 0.5, then multiply by 1+saturation, otherwise add the saturation and subtract lightness multipled by saturation.
        float q = l < 0.5 ? l * (1.0 + s) : l + s - l * s;
        float p = 2.0 * l - q;
        r = hue_to_rgb(p, q, h + 1/3.0);
        g = hue_to_rgb(p, q, h);
        b = hue_to_rgb(p, q, h - 1/3.0);
    }

    // Return a neomatrix colour
    return matrix.Color( round(r * 255), round(g * 255), round(b * 255) );
}

/**
 * @name dist
 * @description Gets the distance between two vectors. This is used for the radial pattern.
 * @param {float} x1 - The x coordinate of the first vector.
 * @param {float} y2 - The y coordinate of the first vector.
 * @param {float} x2 - The x coordinate of the second vector.
 * @param {float} y2 - The y coordinate of the second vector.
 * @return {float}
**/
float dist( float x1, float y1, float x2, float y2 ) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return (float) sqrt(dx*dx + dy*dy);
}


/**
 * @name neomatrix_loop
 * @description This function is called from main loop() and sets the LED values if the lamp is on.
 * @return {void}
**/
void neomatrix_loop() {
  if (ticks > timeout) {
    power = false;
  } else {
    ticks = millis();
  }

  uint8_t x, y, z;
  float hue = 0.0;

  if ( power ) {
    matrix.setBrightness( brightness );

    delta += theta;

    if (delta >= 360) {
      delta = 0;
    }

    for ( x = 0 ; x < rows ; x++ ) {
      for ( y = 0 ; y < cols ; y++ ) {
        z = x + y;
        float distance = dist( (float)rows/2, (float)cols/2, (float)x, (float)y );
        switch ( pattern ) {
          case RADIAL:
            hue = (float)(int((delta - distance) * contrast) % 360) / 360;
            matrix.drawPixel( x, y, hsl_to_rgb( hue, 1.0, 0.5 ) );
            break;
          case WIPE:
            hue = (float)(int((delta + y) * contrast) % 360) / 360;
            matrix.drawPixel( x, y, hsl_to_rgb( hue, 1.0, 0.5 ));
            break;
          case DIAGONAL_WIPE:
            hue = (float)(int((delta + z) * contrast) % 360) / 360;
            matrix.drawPixel( x, y, hsl_to_rgb( hue, 1.0, 0.5 ));
            break;
          case RAINBOW_STRIPE:
            hue = (float)(int(((360 / rows) * x) + delta * contrast) % 360) / 360;
            matrix.drawPixel( x, y, hsl_to_rgb( hue, 1.0, 0.5 ) );
            break;
          default:
            break;
        }
      }
    }
  }
  else {
    matrix.fillScreen(0);
  }
  
  matrix.show();
}
