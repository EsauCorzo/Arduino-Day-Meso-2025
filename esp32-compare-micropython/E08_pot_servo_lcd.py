from machine import ADC, Pin, SoftI2C
from i2c_lcd import I2cLcd
from servo import Servo
from time import sleep

# Constants
SERVO_PIN = 2  # Pin connected to the servo motor
POT_PIN = 35 # Pin connected to potentiometer
I2C_ADDRESS = 0x27  # I2C address of the LCD
LCD_COLUMNS = 16  # Number of columns on the LCD
LCD_ROWS = 2  # Number of rows on the LCD

# Initialize I2C for LCD
i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=400000)
lcd = I2cLcd(i2c, I2C_ADDRESS, LCD_ROWS, LCD_COLUMNS)

# Initialize servo object
servo = Servo(Pin(SERVO_PIN))
servo.update_settings(servo_pwm_freq= 50,
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
    lcd.putstr("  {:3d} degrees".format(angle))

# Map function to convert potentiometer value to servo angle
def map_value(value, in_min, in_max, out_min, out_max):
    return int((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

# Initialize the potentiometer on ADC pin
pot = ADC(Pin(POT_PIN))

# Set attenuation for full range (0-3.3V)
pot.atten(ADC.ATTN_11DB)

# Set ADC resolution to 12 bits (0-4095)
pot.width(ADC.WIDTH_12BIT)

while True:
    # Read potentiometer value
    pot_value = pot.read()
    
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

