#include <Arduino.h>

// LED pin and button pin
const int ledPin = LED_BUILTIN;
const int buttonPin = 4;

// Variable to track the button state
bool buttonPressed = false;

void setup() {
  // Configure the LED pin and button pin
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Button is pressed (active low)
  if (!digitalRead(buttonPin)) {
    // Check if it was not already pressed
    if (!buttonPressed) {
      // Toggle the LED
      digitalWrite(ledPin, !digitalRead(ledPin));

      // Mark the button as pressed
      buttonPressed = true;
    }
  } else {
    // Reset the button state when released
    buttonPressed = false;
  }

  // Debounce delay
  delay(10);
}
