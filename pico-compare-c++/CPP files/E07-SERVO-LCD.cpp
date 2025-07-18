#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Constants
#define SERVO_PIN     15 // Pin connected to the servo motor
#define I2C_ADDRESS 0x27 // I2C address of the LCD
#define LCD_COLUMNS   16 // Number of columns on the LCD
#define LCD_ROWS       2 // Number of rows on the LCD

// Initialize the LCD
LiquidCrystal_I2C lcd(I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Define servo object
Servo myServo;

// Function to update the LCD display with the current servo angle
void updateLCD(int angle) {
    // Buffer for storing LCD text
    char buffer[16];
    
    // Print header on line 1
    lcd.setCursor(0, 0);
    sprintf(buffer, "Servo Angle:");
    lcd.print(buffer);
    
    // Print servo value on line 2
    lcd.setCursor(0, 1);
    sprintf(buffer, "%3d degrees", angle);
    lcd.print(buffer);
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize LCD
    lcd.init();
    lcd.backlight();

    // Attach servo to SERVO_PIN
    myServo.attach(SERVO_PIN, 800, 2550);

    // Set initial servo position to 90
    myServo.write(90);
    
    // Display initial angle on the LCD
    updateLCD(90);

    // Prompt user for input
    Serial.println("Enter angle (0-180): ");
}

void loop() {
    // Check if data is available on the serial monitor
    if (Serial.available()) {
        // Read the input angle from the serial monitor
        int angle = Serial.parseInt();
        
        // Read the newline character
        char c = Serial.read();
        
        // Ensure the angle is within the valid range (0 to 180)
        // and check for newline character
        if (angle >= 0 && angle <= 180 && c == '\n') {
            // Move the servo to the specified angle
            myServo.write(angle);

            // Display the angle on the LCD
            updateLCD(angle);

        } else {
            // Invalid data feedback
            Serial.println("Invalid angle. Enter a value between 0 and 180.");
        }
        // Prompt user for next input
        Serial.println("Enter angle (0-180): ");
    }
}