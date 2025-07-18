#include <Arduino.h>

const int LED_PIN = 15;
const int DELAY_VAL = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(DELAY_VAL);
  digitalWrite(LED_PIN, LOW);
  delay(DELAY_VAL);
}