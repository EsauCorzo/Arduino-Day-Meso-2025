#include <Arduino.h>

const int LED_PIN = 15;
const int PWM_RESOLUTION = 16;
const int PWM_FREQUENCY = 5000;
const int PWM_MAX = (1 << PWM_RESOLUTION) - 1;
const int PWM_STEP = PWM_MAX / 256;
const int DELAY_VAL = 5;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  analogWriteFreq(PWM_FREQUENCY);
  analogWriteResolution(PWM_RESOLUTION);
}

void loop() {
  for (int value = 0; value <= PWM_MAX; value += PWM_STEP) {
    analogWrite(LED_PIN, value);
    delay(DELAY_VAL);
  }

  for (int value = PWM_MAX; value >= 0; value -= PWM_STEP) {
    analogWrite(LED_PIN, value);
    delay(DELAY_VAL);
  }
}