#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define STRIP_PIN   1
#define PIXEL_COUNT 16
#define LAST_LED    PIXEL_COUNT - 1
#define DELAY_VAL   50
#define BRIGHTNESS  0.2
#define DT_PIN      16
#define CLK_PIN     17
#define STEPS       1

Adafruit_NeoPixel strip(PIXEL_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);

int currentLed = 0;
bool dt = false;
bool clk = false;
bool clkOld = false;

void updateStrip(int ledIndex, uint32_t color1, uint32_t color2) {
  for (int i=0; i<PIXEL_COUNT; i++) {
    strip.setPixelColor(i, color1);
    if (i == ledIndex){
      continue;
    } else {
      strip.setPixelColor(i, color2);
    }
  }
  strip.show();
}

void setup() {
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  strip.begin();
  strip.setBrightness(int(255 * BRIGHTNESS));
  strip.show();
}

void loop() {
  dt = digitalRead(DT_PIN);
  clk = digitalRead(CLK_PIN);
  if(clk != clkOld && clk == LOW) {
    if(clk != dt) {
      currentLed += STEPS;
      currentLed > LAST_LED ? currentLed = 0 : currentLed;
    }
    if(clk == dt) {
      currentLed -= STEPS;
      currentLed < 0 ? currentLed = LAST_LED : currentLed;
    }
    updateStrip(currentLed, strip.Color(0, 0, 255), strip.Color(255, 0, 0));
  }
  clkOld = clk;
  delay(1);
}