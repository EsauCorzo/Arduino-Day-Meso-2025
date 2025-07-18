#include <Arduino.h>

const int LED_PIN = 15;
const int POT_PIN = 26;
const int FREQUENCY = 5000;
const int RESOLUTION = 16;

void setup() {
  Serial.begin(115200);
  analogReadResolution(RESOLUTION);
  analogWriteResolution(RESOLUTION);
  analogWriteFreq(FREQUENCY);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  int dutyCycle = potValue;
  analogWrite(LED_PIN, dutyCycle);
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" ");
  Serial.print("Duty Cycle: ");
  Serial.println(dutyCycle);
  delay(10);
}