#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define ADC for pin 34
const int potPin = 34;

// Use 12 bit precision for LEDC timer and ADC
const int resolution = 12;

// Buffer for LCD display
char buf[17]; 

void setup() {
    // Initialize the LCD
    lcd.init();
    lcd.backlight();
    
    // Set attenuation for full range (0-3.3V)
    analogSetAttenuation(ADC_11db);

    // Set ADC resolution to 12 bits (0-4095)
    analogReadResolution(resolution);
}

void loop() {
    // Read analog value
    int analogValue = analogRead(potPin);
    int analogMV = analogReadMilliVolts(potPin);
    
    // Print header on line 1
    lcd.setCursor(0, 0);
    sprintf(buf, "Pot value:");
    lcd.print(buf);

    // Map ADC value to percentage (0 - 100%)
    int percentValue = map(analogValue, 0, 4095, 0, 100);
    
    // Map ADC to voltage (0-3.3V)
    float voltageValue = (float)analogMV / 1000.0;

    // Print raw and mapped values on line 2
    lcd.setCursor(0, 1);
    sprintf(buf, "%4d  %1.1fV  %3d%%", analogValue, voltageValue, percentValue);
    lcd.print(buf);

    // Small delay to avoid flickering
    delay(10);
}