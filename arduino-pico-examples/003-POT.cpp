#include <Arduino.h>

const int POT_PIN = 26;
const int RESOLUTION = 16;

void setup() {
  Serial.begin(115200);
  analogReadResolution(RESOLUTION);
}

void loop() {
  int potValue = analogRead(POT_PIN);
  Serial.print("ADC Value: ");
  Serial.println(potValue);
  delay(10);
}