from machine import Pin
from time import sleep_ms
import neopixel

STRIP_PIN = 1
PIXEL_COUNT = 16
DELAY_VAL = 50
BRIGHTNESS = 0.2

strip = neopixel.NeoPixel(Pin(STRIP_PIN), PIXEL_COUNT)

def color_wipe(wait, color):
    for i in range(PIXEL_COUNT):
        strip[i] = tuple(int(val * BRIGHTNESS) for val in color)
        strip.write()
        sleep_ms(wait)

def wheel(pos):
    pos = 255 - pos
    if pos < 85:
        return (255 - pos * 3, 0, pos * 3)
    elif pos < 170:
        pos -= 85
        return (0, pos * 3, 255 - pos * 3)
    else:
        pos -= 170
        return (pos * 3, 255 - pos * 3, 0)

def rainbow(wait):
    for j in range(256):
        for i in range(PIXEL_COUNT):
            strip[i] = tuple(int(val * BRIGHTNESS) for val in wheel((i + j) & 255))
        strip.write()
        sleep_ms(wait)

def rainbow_cycle(wait, cycles=5):
    for j in range(256*cycles):
        for i in range(PIXEL_COUNT):
            strip[i] = tuple(int(val * BRIGHTNESS) for val in wheel((i * 256 // PIXEL_COUNT + j) & 255))
        strip.write()
        sleep_ms(wait)

while True:
    color_wipe(DELAY_VAL, (255, 0, 0))  # Red
    color_wipe(DELAY_VAL, (0, 255, 0))  # Green
    color_wipe(DELAY_VAL, (0, 0, 255))  # Blue
    color_wipe(DELAY_VAL, (255, 255, 0))  # Yellow
    color_wipe(DELAY_VAL, (0, 255, 255))  # Cyan
    color_wipe(DELAY_VAL, (255, 0, 255))  # Magenta
    color_wipe(DELAY_VAL, (255, 255, 255))  # White
    rainbow(DELAY_VAL)
    rainbow_cycle(DELAY_VAL)
