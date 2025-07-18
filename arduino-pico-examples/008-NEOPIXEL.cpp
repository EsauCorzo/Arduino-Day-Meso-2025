#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define STRIP_PIN 1
#define PIXEL_COUNT 16
#define DELAY_VAL 50
#define BRIGHTNESS 0.2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);

void colorWipe(uint8_t wait, uint32_t color) {
  for(uint16_t i=0; i<PIXEL_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte pos) {
  pos = 255 - pos;
  if(pos < 85) {
    return strip.Color(255 - pos * 3, 0, pos * 3);
  }
  else if(pos < 170) {
    pos -= 85;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
  else {
    pos -= 170;
    return strip.Color(pos * 3, 255 - pos * 3, 0);
  }
}

void rainbow(uint8_t wait) {
  for(int j=0; j<256; j++) {
    for(int i=0; i<PIXEL_COUNT; i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait, uint8_t cycles = 5) {
  for(int j=0; j<256*cycles; j++) {
    for(int i=0; i<PIXEL_COUNT; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / PIXEL_COUNT) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(int(255 * BRIGHTNESS));
  strip.show();
}

void loop() {
  colorWipe( DELAY_VAL, strip.Color(255, 0, 0)); // Red
  colorWipe( DELAY_VAL, strip.Color(0, 255, 0));  // Green
  colorWipe( DELAY_VAL, strip.Color(0, 0, 255));  // Blue
  colorWipe( DELAY_VAL, strip.Color(255, 255, 0)); // Yellow
  colorWipe( DELAY_VAL, strip.Color(255, 0, 255)); // Magenta
  colorWipe( DELAY_VAL, strip.Color(0, 255, 255)); // Cyan
  colorWipe( DELAY_VAL, strip.Color(255, 255, 255)); // White
  rainbow(DELAY_VAL);
  rainbowCycle(DELAY_VAL);
}