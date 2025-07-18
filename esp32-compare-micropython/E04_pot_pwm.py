from machine import Pin, ADC, PWM
from time import sleep

# Initialize ADC for pin 34
pot = ADC(Pin(35))

# Set attenuation for full range (0-3.3V)
pot.atten(ADC.ATTN_11DB)

# Set ADC resolution to 10 bits (0-1023)
pot.width(ADC.WIDTH_10BIT)

# Configure the LED (PWM) on GPIO2 and PWM frequency to 1kHz
led = PWM(Pin(17), freq=1000)
 
while True:
    # Read potentiometer value
    pot_value = pot.read()
    
    # Map potentiometer value (0-1023) to duty cycle (0-1023)
    duty_cycle = pot_value
    
    # Set PWM duty cycle
    led.duty(duty_cycle)
    
    # Print values on REPL
    print("Potentiometer Value:", pot_value, "Duty Cycle:", duty_cycle)
    
    # Small delay to stabilize readings
    sleep(0.01)