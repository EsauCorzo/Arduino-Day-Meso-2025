#include <Arduino.h>

// Define the analog pin for the potentiometer
const int potPin = A2;

// Use 10 bit precision for PWM timer and ADC
const int resolution = 16;

// Fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
const int ledPin = LED_BUILTIN;

// use 1KHz as a LEDC base frequency
const int freq = 1000;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Configure the LED PWM frequency to 1kHz
  analogWriteFreq(freq);

  // Configure the LED PWM resolution to 16 bits
  analogWriteResolution(resolution);

  // Set ADC resolution to 16 bits (0-65535)
  analogReadResolution(resolution);
}

void loop() {
  // read the analog in value:
  int potValue = analogRead(potPin);

  // Map potentiometer value (0-65535) to duty cycle (0-65535)
  int dutyCycle = potValue;

  // Set PWM duty cycle
  analogWrite(ledPin, dutyCycle);

  // Print values on serial monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" ");
  Serial.print("Duty Cycle: ");
  Serial.println(dutyCycle);

  // Small delay to stabilize readings
  delay(10);
}
