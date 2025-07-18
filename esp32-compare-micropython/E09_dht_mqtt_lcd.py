from machine import Pin, SoftI2C
from time import sleep, ticks_ms, ticks_diff
from i2c_lcd import I2cLcd
from dht import DHT22
from network import WLAN, STA_IF
from umqtt.simple import MQTTClient
from ujson import dumps

# WiFi credentials
SSID = "PORTABLE-PI"
PASSWORD = "180294mario"

# MQTT server
MQTT_SERVER = "10.9.141.1"
MQTT_TOPIC = "/home/esp32/micropython"
MQTT_ID = "EsaúCorzo MicroPython"

# DHT sensor setup
DHT_PIN = 4
dht_sensor = DHT22(Pin(DHT_PIN))

# LCD setup
I2C_ADDRESS = 0x27
LCD_COLUMNS = 16
LCD_ROWS = 2  
i2c = SoftI2C(scl=Pin(22), sda=Pin(21), freq=400000)
lcd = I2cLcd(i2c, I2C_ADDRESS, LCD_ROWS, LCD_COLUMNS)

# Timing variables
INTERVAL = 30000  # 30 seconds
previous_ticks = 0

# Connect to WiFi
def connect_to_wifi():
    wlan = WLAN(STA_IF)
    wlan.active(True)
    wlan.connect(SSID, PASSWORD)
    while not wlan.isconnected():
        print("Connecting to WiFi...")
        sleep(0.5)
    print("Connected to WiFi:", wlan.ifconfig())

# Update LCD display
def update_lcd(temp, hum):
    lcd.move_to(0, 0)
    lcd.putstr("Temp: {:3.1f} C".format(temp))
    lcd.move_to(0, 1)
    lcd.putstr("Hum: {:3.0f}%".format(hum))

def main():
    # Connect to WiFi
    connect_to_wifi()
    
    # Setup MQTT
    client = MQTTClient(MQTT_ID, MQTT_SERVER)
    client.connect()

    global previous_ticks
    while True:
        # Update current time
        current_ticks = ticks_ms()
        
        if ticks_diff(current_ticks, previous_ticks) >= INTERVAL:
            # Update last reading time
            previous_ticks = current_ticks

            # Read temperature and humidity
            dht_sensor.measure()
            temperature = dht_sensor.temperature()
            humidity = dht_sensor.humidity()

            # Update LCD display
            update_lcd(temperature, humidity)

            # Create JSON payload
            payload = dumps({"id":MQTT_ID,"temp": temperature, "hum": humidity})

            # Publish to MQTT
            client.publish(MQTT_TOPIC, payload)

            # Debug output
            print(payload)

main()