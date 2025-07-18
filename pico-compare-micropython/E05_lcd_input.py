from machine import I2C, Pin
from i2c_lcd import I2cLcd
import sys

# Initialize the LCD
lcd = I2cLcd(I2C(0), 0x27, 2, 16)

# Print ready message on LCD
lcd.putstr("Ready...")

while True:
    try:
        # Read input from REPL
        input_data = input()
        
        # Remove any trailing newline or spaces
        input_data = input_data.strip()

        # Check if the input specifies the line
        if input_data.startswith("1:"):
            # Clear the line
            lcd.move_to(0, 0)
            lcd.putstr(" " * 16)
            
            # Write the message
            lcd.move_to(0, 0)
            lcd.putstr(input_data[2:18])  
        
        elif input_data.startswith("2:"):
            # Clear the line
            lcd.move_to(0, 1)
            lcd.putstr(" " * 16)
            
            # Write the message
            lcd.move_to(0, 1)
            lcd.putstr(input_data[2:18])
            
        else:
            # Invalid data feedback
            print("Invalid input. Use '1:message' or '2:message'.")
            
    except KeyboardInterrupt:
        # Exit program on keyboard interrupt
        print("\nExiting...")
        sys.exit()