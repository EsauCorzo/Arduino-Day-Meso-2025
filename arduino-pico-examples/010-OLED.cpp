#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include <logos.h>

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT   64

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  display.begin();
  display.setRotation(2);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.drawBitmap(0, 0, RPI_LOGO_BIG, SCREEN_WIDTH, SCREEN_HEIGHT, SH110X_WHITE);
  display.display();

/*
  display.clearDisplay();
  display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SH110X_BLACK);
  display.fillRect(32, 0, 64, 64, SH110X_WHITE);
  display.fillRect(36, 4, 56, 56, SH110X_BLACK);
  display.drawFastVLine(50, 16, 44, SH110X_WHITE);
  display.drawFastVLine(64, 4, 44, SH110X_WHITE);
  display.drawFastVLine(78, 16, 44, SH110X_WHITE);
  display.fillRect(84, 48, 4, 8, SH110X_WHITE);
  display.display(); 
*/
}

void loop() {

}