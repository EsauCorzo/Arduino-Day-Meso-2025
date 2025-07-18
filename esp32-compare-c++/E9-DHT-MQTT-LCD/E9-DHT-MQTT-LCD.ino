#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "PORTABLE-PI";
const char* password = "180294mario";

// MQTT server
const char* mqtt_server = "10.3.141.1";
const char* mqtt_topic = "/home/esp32/arduino";
const char* mqtt_id = "EsaúCorzo Arduino";

// DHT sensor setup
#define DHTPIN 4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// WiFi and MQTT clients
WiFiClient espClient;
PubSubClient client(espClient);

// Timing variables
unsigned long previousMillis = 0;
const long interval = 5000; // 5 seconds

// Connect to WiFi
void connectToWiFi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected!");
}

// Reconnect to MQTT broker
void reconnectMQTT() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (client.connect(mqtt_id)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

// Update LCD display
void updateLCD(float t, float h) {
    char buffer[16];
    sprintf(buffer, "Temp: %3.1f C", t);
    lcd.setCursor(0, 0);
    lcd.print(buffer);
    sprintf(buffer, "Hum: %3.0f%%", h);
    lcd.setCursor(0, 1);
    lcd.print(buffer);
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize DHT sensor
    dht.begin();

    // Initialize LCD
    lcd.init();
    lcd.backlight();

    // Connect to WiFi
    connectToWiFi();

    // Setup MQTT
    client.setServer(mqtt_server, 1883);
}

void loop() {
    // Ensure MQTT connection
    if (!client.connected()) {
        reconnectMQTT();
    }
    client.loop();

    // Update current time
    unsigned long currentMillis = millis();
    
    if (currentMillis - previousMillis >= interval) {
        // Update last reading time
        previousMillis = currentMillis;

        // Read temperature and humidity
        float temperature = dht.readTemperature();
        float humidity = dht.readHumidity();

        // Check if readings are valid
        if (isnan(temperature) || isnan(humidity)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        // Update LCD display
        updateLCD(temperature, humidity);

        // Create JSON payload
        JsonDocument jsonDoc;
        jsonDoc["id"] = mqtt_id;
        jsonDoc["temp"] = temperature;
        jsonDoc["hum"] = humidity;
        char jsonBuffer[128];
        serializeJson(jsonDoc, jsonBuffer);
        
        // Publish to MQTT
        client.publish(mqtt_topic, jsonBuffer);

        // Debug output
        Serial.println(jsonBuffer);
    }
}