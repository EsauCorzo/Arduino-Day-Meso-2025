#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

// Constants
#define SERVO_PIN      2 // Pin connected to the servo motor
#define POT_PIN       35 // Pin connected to potentiometer
#define I2C_ADDRESS 0x27 // I2C address of the LCD
#define LCD_COLUMNS   16 // Number of columns on the LCD
#define LCD_ROWS       2 // Number of rows on the LCD

// Initialize the LCD
LiquidCrystal_I2C lcd(I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// Define servo object
Servo myServo;

// Function to update the LCD display with the current servo angle
void updateLCD(int angle) {
    // Buffer for LCD text
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

    // Initialize the LCD
    lcd.init();
    lcd.backlight();
    
    // Set attenuation for full range (0-3.3V)
    analogSetAttenuation(ADC_11db);

    // Set ADC resolution to 12 bits (0-4095)
    analogReadResolution(12);

    // Attach servo to SERVO_PIN
    myServo.attach(SERVO_PIN, 700, 2400);
}

void loop() {
  // Read potentiometer value
  int potValue = analogRead(POT_PIN);

  // Map potentiometer value to servo angle (0-180 degrees)
  int angle = map(potValue, 0, 4095, 0, 180);

  // Print the potentiometer value and corresponding angle
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" ");
  Serial.print("Mapped Angle: ");
  Serial.println(angle);

  // Set servo angle
  myServo.write(angle);
    
  // Display the angle on the LCD
  updateLCD(angle);

  // Small delay to avoid flickering
  delay(20);
}
