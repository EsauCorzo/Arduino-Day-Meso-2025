from machine import Pin, ADC, PWM
from time import sleep

LED_PIN = 15
POT_PIN = 26
FREQUENCY = 5000

pot = ADC(Pin(POT_PIN))
led = PWM(Pin(LED_PIN), freq=FREQUENCY, duty_u16=0)

while True:
    pot_value = pot.read_u16()
    duty_cycle = pot_value
    led.duty_u16(duty_cycle)
    print("Potentiometer Value:", pot_value, "Duty Cycle:", duty_cycle)
    sleep(0.01)