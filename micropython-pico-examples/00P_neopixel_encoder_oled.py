from machine import Pin, I2C
from time import sleep_ms, ticks_ms, ticks_diff
from sh1106 import SH1106_I2C
from neopixel import NeoPixel
import framebuf
import logos

SCREEN_WIDTH  = 128
SCREEN_HEIGHT = 64
DT_PIN = 16
CLK_PIN = 17
SW_PIN = 18
SW_TIMEOUT = 300
THRESHOLD = 80
STRIP_PIN = 1
PIXEL_COUNT = 16
DELAY_VAL = 1
BRIGHTNESS = 0.2

display = SH1106_I2C(SCREEN_WIDTH, SCREEN_HEIGHT, I2C(0))
strip = NeoPixel(Pin(STRIP_PIN), PIXEL_COUNT)

encoder_dt = Pin(DT_PIN, Pin.IN)
encoder_clk = Pin(CLK_PIN, Pin.IN)
encoder_sw = Pin(SW_PIN, Pin.IN)

def constrain_value(val, min_val, max_val):
    return min(max_val, max(min_val, val))

def show_splash():
    display.fill(0)
    fb = framebuf.FrameBuffer(bytearray(logos.RPI_LOGO_BIG), SCREEN_WIDTH, SCREEN_HEIGHT, framebuf.MONO_HLSB)
    display.blit(fb, 0, 0)
    display.show()
    sleep_ms(1000)
    display.fill(0)
    display.show()

def update_display(color):
    display.fill(0)
    if selected_color == 0:
        display.text(">", 25, 2)
    value_string = "ROJO " + str(color[0]) + "%"
    display.text(value_string, 35, 2)
    display.rect(0, 11, 128, 10, 1)
    display.fill_rect(2, 13, map_value(color[0], 0, 100, 0, 124), 6, 1)
    if selected_color == 1:
        display.text(">", 21, 22)
    value_string = "VERDE " + str(color[1]) + "%"
    display.text(value_string, 31, 22)
    display.rect(0, 31, 128, 10, 1)
    display.fill_rect(2, 33, map_value(color[1], 0, 100, 0, 124), 6, 1)
    if selected_color == 2:
        display.text(">", 25, 42)
    value_string = "AZUL " + str(color[2]) + "%"
    display.text(value_string, 35, 42)
    display.rect(0, 51, 128, 10, 1)
    display.fill_rect(2, 53, map_value(color[2], 0, 100, 0, 124), 6, 1)
    display.show()

def update_strip(color):
    for i in range(PIXEL_COUNT):
        strip[i] = tuple(int(map_value(val, 0, 100, 0, 255) * BRIGHTNESS ) for val in color)
    strip.write()

def map_value(value, in_min, in_max, out_min, out_max):
    mapped_value = (value - in_min) * (out_max - out_min) // (in_max - in_min) + out_min
    return mapped_value

def update_values(color, delta):
    global selected_color
    color = list(color) 
    color[selected_color] = constrain_value(color[selected_color] + delta, 0, 100)
    return tuple(color)

color_data = (0, 0, 0)  
selected_color = 0
dt = False
clk = False
clk_old = False
sw = False
last_changed = 0
last_updated = 0

update_strip(color_data)
show_splash()
update_display(color_data)

while True:
    sw = encoder_sw.value()
    if sw == False and ticks_diff(ticks_ms(), last_changed) > SW_TIMEOUT:
        last_changed = ticks_ms()
        selected_color+=1
        if selected_color > 2:
            selected_color = 0
        update_display(color_data)

    clk = encoder_clk.value()
    if clk != clk_old and clk == False:
        dt = encoder_dt.value()
        if ticks_diff(ticks_ms(), last_updated) < THRESHOLD:
            delta = 5 if dt else -5
        else:
            delta = 1 if dt else -1
        last_updated = ticks_ms()
        color_data = update_values(color_data, delta)
        update_display(color_data)
        update_strip(color_data)
    clk_old = clk
    sleep_ms(1)