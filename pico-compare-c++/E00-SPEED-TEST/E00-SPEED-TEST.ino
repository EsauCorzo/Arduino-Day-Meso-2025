#include <Arduino.h>

unsigned long totalCalculations = 0;
unsigned long calculations = 0;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Iniciando C++ Test...");

  for (int second = 1; second < 4; second++) {
    calculations = 0;
    unsigned long startTime = millis();
    unsigned long endTime = startTime + 1000;

    while (millis() < endTime) {
      float result = (1234.56 * 7890.12) / 345.67;
      calculations++;
    }

    totalCalculations += calculations;
    Serial.print("Total en segundo ");
    Serial.print(second);
    Serial.print(": ");
    Serial.println(calculations);
  }

  Serial.print("Total en 3 segundos: ");
  Serial.println(totalCalculations);
}

void loop() {
  // there's nothing here... f**k off now, I'm gonna loop now
}