#include <Arduino.h>

#define DT_PIN      16
#define CLK_PIN     17
#define SW_PIN      18
#define STEPS       1

int value = 0;
bool dt = false;
bool clk = false;
bool clkOld = false;
volatile bool buttonPressed = false;

void buttonHandler() {
    buttonPressed = true;
}

void setup() {
  Serial.begin(115200);
  pinMode(DT_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);
  pinMode(SW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_PIN), buttonHandler, FALLING);
}

void loop() {
  dt = digitalRead(DT_PIN);
  clk = digitalRead(CLK_PIN);
  if(clk != clkOld && clk == LOW) {
    if(clk != dt) {
      value += STEPS;
    }
    if(clk == dt) {
      value -= STEPS;
    }
    Serial.println(value);
  }
  clkOld = clk;

  if(buttonPressed) {
    value = 0;
    Serial.println(value);
    buttonPressed = false;
  }
  delay(1);
}