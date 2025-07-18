from machine import Pin
from time import sleep

LED_PIN = 15
BUTTON_PIN = 14

led = Pin(LED_PIN, Pin.OUT)
button = Pin(BUTTON_PIN, Pin.IN)
button_pressed = False

while True:
    if button.value():
        if not button_pressed:
            led.value(not led.value())
            button_pressed = True  
    else:
        button_pressed = False  
    sleep(0.01)