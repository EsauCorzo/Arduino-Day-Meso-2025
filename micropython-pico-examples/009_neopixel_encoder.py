from machine import Pin
from time import sleep_ms
import neopixel

STRIP_PIN = 1
PIXEL_COUNT = 16
LAST_LED = PIXEL_COUNT - 1
DELAY_VAL = 50
BRIGHTNESS = 0.2
DT_PIN = 16
CLK_PIN = 17
STEPS = 1

strip = neopixel.NeoPixel(Pin(STRIP_PIN), PIXEL_COUNT)

current_led = 0
dt = False
clk = False
clk_old = False

encoder_dt = Pin(DT_PIN, Pin.IN)
encoder_clk = Pin(CLK_PIN, Pin.IN)

def update_strip(led_index, color1, color2):
    for i in range(PIXEL_COUNT):
        strip[i] = tuple(int(val * BRIGHTNESS) for val in color1)
        if i == led_index:
            continue
        else:
            strip[i] = tuple(int(val * BRIGHTNESS) for val in color2)
    strip.write()

while True:
    dt = encoder_dt.value()
    clk = encoder_clk.value()
    if clk != clk_old and clk == False:
        if clk != dt:
            current_led += STEPS
            current_led = 0 if current_led > LAST_LED else current_led
        if clk == dt:
            current_led -= STEPS
            current_led = LAST_LED if current_led < 0 else current_led
        update_strip(current_led, (0, 0, 255), (255, 0, 0))
    clk_old = clk
    sleep_ms(1)