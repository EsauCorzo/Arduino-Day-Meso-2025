from time import ticks_ms

total_calculations = 0
calculations = 0

print("Iniciando MicroPython Test...")

for second in range(1, 4):
    calculations = 0
    start_time = ticks_ms()
    end_time = start_time + 1000
    
    while ticks_ms() < end_time:
        result = (1234.56 * 7890.12) / 345.67
        calculations += 1
    
    total_calculations += calculations
    print(f"Total en segundo {second}: {calculations}")

print(f"Total en 3 segundos: {total_calculations}")

# WTF? where's the loop? 