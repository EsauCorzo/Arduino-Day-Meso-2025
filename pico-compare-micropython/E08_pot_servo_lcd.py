from machine import ADC, Pin, I2C
from i2c_lcd import I2cLcd
from servo import Servo
from time import sleep

# Constants
SERVO_PIN = 15  # Pin connected to the servo motor
POT_PIN = 28  # Pin connected to potentiometer
I2C_ADDRESS = 0x27  # I2C address of the LCD
LCD_COLUMNS = 16  # Number of columns on the LCD
LCD_ROWS = 2  # Number of rows on the LCD

# Initialize I2C for LCD
lcd = I2cLcd(I2C(0), I2C_ADDRESS, LCD_ROWS, LCD_COLUMNS)

# Initialize servo object
servo = Servo(Pin(SERVO_PIN))
servo.update_settings(servo_pwm_freq= 50,
                         min_u16_duty=2500, 
                         max_u16_duty=8500,
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
    lcd.putstr("  {:3d} degrees".format(angle))

# Map function to convert potentiometer value to servo angle
def map_value(value, in_min, in_max, out_min, out_max):
    return int((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

# Initialize the potentiometer on ADC pin
pot = ADC(Pin(POT_PIN))

while True:
    # Read potentiometer value
    pot_value = pot.read_u16() >> 4  # Read and shift right to get a 12-bit value
    
    # Map potentiometer value to servo angle (0-180 degrees)
    angle = map_value(pot_value, 0, 4095, 0, 180)

    # Print the potentiometer value and corresponding angle
    print("Potentiometer Value:", pot_value, "Mapped Angle:", angle)
    
    # Set servo angle
    servo.move(angle)
    
    # Display the angle on the LCD
    update_lcd(angle)
    
    # Small delay to avoid flickering
    sleep(0.02)

