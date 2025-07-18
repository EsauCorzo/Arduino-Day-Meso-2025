#include <Arduino.h>

// Built-in LED pin
const int ledPin = LED_BUILTIN;

// Stores the last time the LED was toggled
unsigned long previousMillis = 0;

// Interval at which to blink (milliseconds) 
const long interval = 1000;

void setup() {
    // Initialize the built-in LED (usually GPIO2 on ESP32)
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // Get the current time
    unsigned long currentMillis = millis();
    
    // Check if the toggle interval has passed
    if (currentMillis - previousMillis >= interval) {
        // Toggle the LED state
        digitalWrite(ledPin, !digitalRead(ledPin));
        // Update the last toggle time
        previousMillis = currentMillis;
    } 
}