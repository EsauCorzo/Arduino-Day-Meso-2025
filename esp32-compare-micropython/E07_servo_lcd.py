from machine import Pin, SoftI2C
from servo import Servo
from i2c_lcd import I2cLcd

# Constants
SERVO_PIN = 2  # Pin connected to the servo motor
I2C_ADDRESS = 0x27  # I2C address of the LCD
LCD_COLUMNS = 16  # Number of columns on the LCD
LCD_ROWS = 2  # Number of rows on the LCD

# Initialize I2C for LCD
i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=400000)
lcd = I2cLcd(i2c, I2C_ADDRESS, LCD_ROWS, LCD_COLUMNS)

# Define servo object
my_servo = Servo(SERVO_PIN)
my_servo.update_settings(servo_pwm_freq= 50,
                         min_u10_duty=35, 
                         max_u10_duty=125,
                         min_angle=0, 
                         max_angle=180, 
                         pin=SERVO_PIN)

# Function to update the LCD display with the current servo angle
def update_lcd(angle):
    # Print header on line 1
    lcd.move_to(0, 0)
    lcd.putstr("Servo Angle:\n")
    
    # Print servo value on line 2
    lcd.move_to(0, 1)
    lcd.putstr("{:3d} degrees".format(angle))

def main():  
    # Set initial servo position to 90
    my_servo.move(90)
    
    # Display initial angle on the LCD
    update_lcd(90)

    while True:
        try:
            # Prompt user for input
            input_angle = input("Enter angle (0-180): ")
            angle = int(input_angle)
            
            # Ensure the angle is within the valid range (0 to 180)
            if 0 <= angle <= 180:
                # Move the servo to the specified angle
                my_servo.move(angle)
                
                # Display the angle on the LCD
                update_lcd(angle)
            else:
                # Invalid angle feedback
                print("Invalid angle. Enter a value between 0 and 180.")
        except ValueError:
            # Invalid data feedback
            print("Invalid input. Please enter a number.")

main()