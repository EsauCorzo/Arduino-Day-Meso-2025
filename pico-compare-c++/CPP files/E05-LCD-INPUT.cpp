#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    // Initialize the LCD and Serial communication
    lcd.init();
    lcd.backlight();
    Serial.begin(115200);
    
    // Print ready message on LCD
    lcd.print("Ready...");
}

void loop() {
    if (Serial.available()) {
        // Read the input from Serial
        String inputData = Serial.readStringUntil('\n');
        
        // Remove any trailing newline or spaces
        inputData.trim(); 
        
        // Check if the input specifies the line
        if (inputData.startsWith("1:")) {
            // Clear the line
            lcd.setCursor(0, 0);
            lcd.print("                ");
            
            // # Write the message
            lcd.setCursor(0, 0);
            lcd.print(inputData.substring(2,18));

        } else if (inputData.startsWith("2:")) {
            // Clear the line
            lcd.setCursor(0, 1);
            lcd.print("                ");
            
            // Write the message
            lcd.setCursor(0, 1);
            lcd.print(inputData.substring(2,18));
            
        } else {
            // Invalid data feedback
            Serial.println("Invalid input. Use '1:message' or '2:message'.");
        }
    }
}