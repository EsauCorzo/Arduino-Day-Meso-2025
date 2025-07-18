from machine import I2C
from sh1106 import SH1106_I2C
import framebuf
import logos

SCREEN_WIDTH  = 128
SCREEN_HEIGHT = 64

display = SH1106_I2C(SCREEN_WIDTH, SCREEN_HEIGHT, I2C(0))
fb = framebuf.FrameBuffer(bytearray(logos.RPI_LOGO_BIG), SCREEN_WIDTH, SCREEN_HEIGHT, framebuf.MONO_HLSB)
display.fill(0)
display.blit(fb, 0, 0)
display.show()

"""
display.fill(0)
display.fill_rect(32, 0, 64, 64, 1)
display.fill_rect(36, 4, 56, 56, 0)
display.vline(50, 16, 44, 1)
display.vline(64, 4, 44, 1)
display.vline(78, 16, 44, 1)
display.fill_rect(84, 48, 4, 8, 1)
display.show() 
"""