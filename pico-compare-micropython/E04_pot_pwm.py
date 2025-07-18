from machine import Pin, ADC, PWM
from time import sleep

# Initialize ADC for pin 28
pot = ADC(Pin(28))

# Configure the LED (PWM) on LED_BUILTIN and PWM frequency to 1kHz
led = PWM(Pin("LED"), freq=1000)
 
while True:
    # Read potentiometer value
    pot_value = pot.read_u16()
    
    # Map potentiometer value (0-65535) to duty cycle (0-65535)
    duty_cycle = pot_value
    
    # Set PWM duty cycle
    led.duty_u16(duty_cycle)
    
    # Print values on REPL
    print("Potentiometer Value:", pot_value, "Duty Cycle:", duty_cycle)
    
    # Small delay to stabilize readings
    sleep(0.01)