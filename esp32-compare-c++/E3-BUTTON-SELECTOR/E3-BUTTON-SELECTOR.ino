#include <Arduino.h>

// Define LED pins
const int ledPins[] = {16, 17, 18};
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

// Define push button pin
const int buttonPin = 4;

// Define buzzer pin
const int buzzerPin = 19;

// Use 10 bit precision for LEDC timer
const int resolution = 10;

// Initialize variables
volatile int currentLed = 0;
volatile bool buttonPressed = false;

// Turn off all LEDs
void turnOffAllLeds() {
    for (int i = 0; i < numLeds; i++) {
        digitalWrite(ledPins[i], LOW);
    }
}

// ISR for button press
void IRAM_ATTR buttonHandler() {
    buttonPressed = true;
}

// Function to play a tone on the buzzer
void playBuzzerTone(int frequency, int duration) {
    ledcAttach(buzzerPin, frequency, resolution);
    ledcWriteTone(buzzerPin, frequency);
    delay(duration);
    ledcDetach(buzzerPin);
}

// Play a startup sound on the buzzer
void playStartupSound() {
    int tones[][2] = {{500, 200}, {700, 200}, {900, 200}};
    for (int i = 0; i < 3; i++) {
        playBuzzerTone(tones[i][0], tones[i][1]);
        delay(100); // Short pause between tones
    }
}

void setup() {
    // Initialize LED pins
    for (int i = 0; i < numLeds; i++) {
        pinMode(ledPins[i], OUTPUT);
    }

    // Initialize button pin
    pinMode(buttonPin, INPUT);

    // Attach interrupt to the button pin
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonHandler, FALLING);

    // Initialize buzzer pin
    pinMode(buzzerPin, OUTPUT);

    // Play the startup sound and turn off all LEDs
    playStartupSound();
    turnOffAllLeds();
}

void loop() {
    if (buttonPressed) {
        // Turn off flag
        buttonPressed = false;

        // Turn off all LEDs
        turnOffAllLeds();

        // Turn on the next LED in sequence
        digitalWrite(ledPins[currentLed], HIGH);

        // Play a tone on the buzzer
        playBuzzerTone(1000, 100); // 1000 Hz for 100 ms

        // Update to the next LED
        currentLed = (currentLed + 1) % numLeds;
    }

    delay(10); // Debounce delay
}
