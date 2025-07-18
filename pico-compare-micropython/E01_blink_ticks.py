from machine import Pin
from time import ticks_ms, ticks_diff

# Initialize the built-in LED
led = Pin("LED", Pin.OUT)

# Stores the last time the LED was toggled
previous_ticks = 0

# Interval at which to blink (milliseconds)
INTERVAL = 100

# Where's the setup()?

while True:
    # Get the current time
    current_ticks = ticks_ms()
    
    # Check if the toggle interval has passed
    if ticks_diff(current_ticks, previous_ticks) >= INTERVAL:
        # Toggle the LED state
        led.value(not led.value())
        
        # Update the last toggle time
        previous_ticks = current_ticks