from machine import Pin, PWM
from time import sleep_ms

LED_PIN = 15
PWM_RESOLUTION = 16
PWM_FREQUENCY = 5000
PWM_MAX = (1 << PWM_RESOLUTION) -1
PWM_STEP = PWM_MAX // 256
DELAY_VAL = 5

led = PWM(Pin(LED_PIN), freq=PWM_FREQUENCY, duty_u16=0)

while True:
    for value in range(0, PWM_MAX + 1, PWM_STEP):
        led.duty_u16(value)
        sleep_ms(DELAY_VAL)

    for value in range(PWM_MAX, -1, -PWM_STEP):
        led.duty_u16(value)
        sleep_ms(DELAY_VAL)