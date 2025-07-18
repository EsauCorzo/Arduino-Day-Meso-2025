#include <Arduino.h>

const int LED_PIN = 15;
const int BUTTON_PIN = 14;
bool buttonPressed = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN)) {
    if (!buttonPressed) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      buttonPressed = true;
    }
  } else {
    buttonPressed = false;
  }
  delay(10);
}