from machine import Pin, PWM
from time import sleep
import sys

# Initialize LED pins
led_pins = [Pin(11, Pin.OUT), Pin(12, Pin.OUT), Pin(13, Pin.OUT)]

# Initialize button pin
button_pin = Pin(15, Pin.IN)

# Initialize buzzer pin
buzzer_pin = Pin(14, Pin.OUT)

# Initialize variables
current_led = 0
button_pressed = False

# Turn off all LEDs
def turn_off_all_leds():
    for led in led_pins:
        led.value(0)

# ISR for button press
def button_handler(pin):
    global button_pressed
    button_pressed = True

# Function to play a tone on the buzzer
def play_buzzer_tone(frequency, duration):
    pwm = PWM(buzzer_pin)
    pwm.freq(frequency)
    pwm.duty_u16(32768)
    sleep(duration)
    pwm.deinit()

# Play a startup sound on the buzzer
def play_startup_sound():
    tones = [(500, 0.2), (700, 0.2), (900, 0.2)]  
    for frequency, duration in tones:
        play_buzzer_tone(frequency, duration)
        sleep(0.1)  # Short pause between tones

# Attach interrupt to the button pin
button_pin.irq(trigger=Pin.IRQ_RISING, handler=button_handler)

# Play the startup sound and turn off all LEDs
play_startup_sound()
turn_off_all_leds()

try:
    # Main loop (does nothing, just keeps the program running)
    while True:
        if button_pressed:
            # Turn off flag
            button_pressed = False
            
            # Turn off all LEDs
            turn_off_all_leds()
            
            # Turn on the next LED in sequence
            led_pins[current_led].value(1)
            
            # Play a tone on the buzzer
            play_buzzer_tone(1000, 0.1)  # 1000 Hz for 0.1 seconds
            
            # Update to the next LED
            current_led = (current_led + 1) % len(led_pins)
            
        # Debounce delay
        sleep(0.01)
except KeyboardInterrupt:
    # Play an outro tune on the buzzer
    outro_tones = [(900, 0.2), (700, 0.2), (500, 0.2)]  # List of (frequency, duration)
    for frequency, duration in outro_tones:
        play_buzzer_tone(frequency, duration)
        sleep(0.1)  # Short pause between tones
    print("Exiting program. Goodbye!")
    
    # Turn off all LEDs before exiting
    turn_off_all_leds()
    sys.exit()



