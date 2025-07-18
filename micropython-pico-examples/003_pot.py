from machine import Pin, ADC
from time import sleep

POT_PIN = 26

pot = ADC(Pin(POT_PIN))

while True:
    pot_value = pot.read_u16()
    print("ADC Value:", pot_value)
    sleep(0.01)