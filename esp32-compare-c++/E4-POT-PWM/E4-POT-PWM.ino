#include <Arduino.h>

// Define the analog pin for the potentiometer
const int potPin = 34;

// Use 10 bit precision for LEDC timer and ADC
const int resolution = 10;

// Fade LED PIN (replace with LED_BUILTIN constant for built-in LED)
const int ledPin = LED_BUILTIN;

// use 1KHz as a LEDC base frequency
const int freq = 1000;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set attenuation for full range (0-3.3V)
  analogSetAttenuation(ADC_11db);

  // Set ADC resolution to 10 bits (0-1023)
  analogReadResolution(resolution);

  // Configure the LED (PWM) on GPIO2 and PWM frequency to 1kHz
  ledcAttach(ledPin, freq, resolution);
}

void loop() {
  // read the analog in value:
  int potValue = analogRead(potPin);

  // Map potentiometer value (0-1023) to duty cycle (0-1023)
  int dutyCycle = potValue;

  // Set PWM duty cycle
  ledcWrite(ledPin, dutyCycle);

  // Print values on serial monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" ");
  Serial.print("Duty Cycle: ");
  Serial.println(dutyCycle);

  // Small delay to stabilize readings
  delay(10);
}
