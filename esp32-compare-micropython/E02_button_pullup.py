from machine import Pin
from time import sleep

# Configure the LED pin and button pin
led = Pin(2, Pin.OUT)
button = Pin(4, Pin.IN, Pin.PULL_UP)

# Variable to track the button state
button_pressed = False

while True:
    # Button is pressed (active low)
    if not button.value():
        # Check if it was not already pressed
        if not button_pressed:
            # Toggle the LED
            led.value(not led.value())
            
            # Mark the button as pressed
            button_pressed = True  
    else:
        # Reset the button state when released
        button_pressed = False  
    
    # Debounce delay
    sleep(0.01)  