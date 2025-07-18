from machine import Pin, ADC, SoftI2C
from time import sleep
from i2c_lcd import I2cLcd

# Initialize the LCD
i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=400000)
lcd = I2cLcd(i2c, 0x27, 2, 16)

# Initialize ADC for pin 34
pot = ADC(Pin(35))

# Set attenuation for full range (0-3.3V)
pot.atten(ADC.ATTN_11DB)

# Set resolution to 12 bits (0-4096)
pot.width(ADC.WIDTH_12BIT)

# Function to map value from one range to another
def map_value(value, in_min, in_max, out_min, out_max):
  mapped_value = (value - in_min) * (out_max - out_min) // (in_max - in_min) + out_min
  return mapped_value

while True:
    # Read analog value
    analog_value = pot.read()  
    analog_uv = pot.read_uv()
    
    # Print header on line 1
    lcd.move_to(0, 0) 
    lcd.putstr("Pot value:")
    
    # Map ADC value to percentage (0 - 100%)
    percent_value = map_value(analog_value, 0, 4095, 0, 100)  
    
    # Map ADC to voltage (0-3.3V)
    voltage_value = analog_uv / 1000000
    
    # Print raw and mapped values on line 2
    lcd.move_to(0, 1)
    lcd.putstr(f"{analog_value:4d}  {(voltage_value):1.1f}V  {percent_value:3d}%")
    
    # Small delay to avoid flickering
    sleep(0.01)  