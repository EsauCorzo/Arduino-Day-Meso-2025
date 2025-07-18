#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SH110X.h>
#include "logos.h"

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define DT_PIN        16
#define CLK_PIN       17
#define SW_PIN        18
#define SW_TIMEOUT    300
#define THRESHOLD     80
#define STRIP_PIN     1
#define PIXEL_COUNT   16
#define DELAY_VAL     1
#define BRIGHTNESS    0.2

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
Adafruit_NeoPixel strip(PIXEL_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);

typedef enum {
  ROJO,
  VERDE,
  AZUL,
} ColorSelector;

struct ColorVariable {
  uint8_t rojo = 0;
  uint8_t verde = 0;
  uint8_t azul = 0;
};

ColorVariable colorData = {0, 0, 0};
ColorSelector selectedColor = ROJO;

void nextColor() {
  switch (selectedColor) {
    case ROJO:
      selectedColor = VERDE;
      break;
    case VERDE:
      selectedColor = AZUL;
      break;
    case AZUL:
      selectedColor = ROJO;
      break;
  }
}

void showSplash() {
  display.clearDisplay();
  display.drawBitmap(0, 0, RPI_LOGO_BIG, SCREEN_WIDTH, SCREEN_HEIGHT, SH110X_WHITE);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
}

ColorVariable updateValue(ColorVariable color, int delta) {
  switch (selectedColor) {
    case ROJO:
      color.rojo = constrain(color.rojo + delta, 0, 100);
      break;
    case VERDE:
      color.verde = constrain(color.verde + delta, 0, 100);
      break;
    case AZUL:
      color.azul = constrain(color.azul + delta, 0, 100);
      break;
  }
  return color;
}

void updateStrip(ColorVariable color) {
  strip.clear();
  for(int i=0; i<PIXEL_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(
      map(color.rojo, 0, 100, 0, 255),
      map(color.verde, 0, 100, 0, 255),
      map(color.azul, 0, 100, 0, 255)
    ));
  }
  strip.show();
}

void updateDisplay(ColorVariable color) {
  char buffer[11] = "";
  display.clearDisplay();
  display.setFont();
  display.setTextColor(SH110X_WHITE);

  if (selectedColor == ROJO) {
    display.setCursor(32, 2);
    display.print(">");
  }
  display.setCursor(42, 2);
  sprintf(buffer, "ROJO %3d%%", color.rojo);
  display.print(buffer);
  display.drawRoundRect(0, 11, 128, 10, 1, SH110X_WHITE);
  display.fillRect(2, 13, map(color.rojo, 0, 100, 0, 124), 6, SH110X_WHITE);

  if (selectedColor == VERDE) {
    display.setCursor(32, 22);
    display.print(">");
  }
  display.setCursor(39, 22);
  sprintf(buffer, "VERDE %3d%%", color.verde);
  display.print(buffer);
  display.drawRoundRect(0, 31, 128, 10, 1, SH110X_WHITE);
  display.fillRect(2, 33, map(color.verde, 0, 100, 0, 124), 6, SH110X_WHITE);

  if (selectedColor == AZUL) {
    display.setCursor(32, 42);
    display.print(">");
  }
  display.setCursor(42, 42);
  sprintf(buffer, "AZUL %3d%%", color.azul);
  display.print(buffer);
  display.drawRoundRect(0, 51, 128, 10, 1, SH110X_WHITE);
  display.fillRect(2, 53, map(color.azul, 0, 100, 0, 124), 6, SH110X_WHITE);

  display.display();
}

long int lastChanged = 0;
long int lastUpdated = 0;
bool oldClk = HIGH;
int delta = 0;

void setup() {
  display.begin();
  display.setRotation(2);
  strip.begin();
  strip.setBrightness(int(255 * BRIGHTNESS));

  pinMode(DT_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);
  pinMode(SW_PIN, INPUT);

  updateStrip(colorData);
  showSplash();
  updateDisplay(colorData);
}

void loop() {
  bool sw = digitalRead(SW_PIN);
  if (sw == LOW && millis() - lastChanged > SW_TIMEOUT) {
    lastChanged = millis();
    nextColor();
    updateDisplay(colorData);
  }

  bool clk = digitalRead(CLK_PIN);
  if (clk != oldClk && clk == LOW) {
    bool dt = digitalRead(DT_PIN);
    if (millis() - lastUpdated < THRESHOLD) {
      delta = dt ? 5 : -5;
    } else {
      delta = dt ? 1 : -1;
    }
    lastUpdated = millis();
    colorData = updateValue(colorData, delta);
    updateStrip(colorData);
    updateDisplay(colorData);
  }
  oldClk = clk;
  delay(1);
}