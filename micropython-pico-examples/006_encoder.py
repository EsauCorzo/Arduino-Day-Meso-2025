from machine import Pin
from time import sleep_ms

DT_PIN = 16
CLK_PIN = 17
SW_PIN = 18
STEPS = 1

value = 0
dt = False
clk = False
clk_old = False
button_pressed = False

encoder_dt = Pin(DT_PIN, Pin.IN)
encoder_clk = Pin(CLK_PIN, Pin.IN)
encoder_sw = Pin(SW_PIN, Pin.IN)

def button_handler(pin):
    global button_pressed
    button_pressed = True

encoder_sw.irq(trigger=Pin.IRQ_FALLING, handler=button_handler)

while True:
    dt = encoder_dt.value()
    clk = encoder_clk.value()
    if clk != clk_old and clk == False:
        if clk != dt:
            value += STEPS
        if clk == dt:
            value -= STEPS
        print(value)
    clk_old = clk

    if button_pressed:
        value = 0
        print(value)
        button_pressed = False
    sleep_ms(1)