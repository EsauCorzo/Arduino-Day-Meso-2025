from machine import Pin
from time import sleep

LED_PIN = 15
DELAY_VAL = 1

led = Pin(LED_PIN, Pin.OUT)

while True:
    led.value(True)
    sleep(DELAY_VAL)
    led.value(False)
    sleep(DELAY_VAL)