from machine import Pin
from time import sleep_ms
from servo import Servo

SERVO_PIN = 19
DT_PIN = 16
CLK_PIN = 17
SW_PIN = 18
SERVO_STEPS = 10

servo = Servo(pin=SERVO_PIN)

servo_value = 90
dt = False
clk = False
clk_old = False
button_pressed = False

servo.move(servo_value)
encoder_dt = Pin(DT_PIN, Pin.IN)
encoder_clk = Pin(CLK_PIN, Pin.IN)
encoder_sw = Pin(SW_PIN, Pin.IN)

def button_handler(pin):
    global button_pressed
    button_pressed = True

def constrain_value(val, min_val, max_val):
  return min(max_val, max(min_val, val))

encoder_sw.irq(trigger=Pin.IRQ_FALLING, handler=button_handler)

while True:
    dt = encoder_dt.value()
    clk = encoder_clk.value()
    if clk != clk_old and clk == False:
        if clk != dt:
            servo_value = constrain_value(servo_value + SERVO_STEPS, 0, 180)
        if clk == dt:
            servo_value = constrain_value(servo_value - SERVO_STEPS, 0, 180)
        servo.move(servo_value)
        print(servo_value)
    clk_old = clk

    if button_pressed:
        servo_value = 90
        servo.move(servo_value)
        print(servo_value)
        button_pressed = False

    sleep_ms(1)