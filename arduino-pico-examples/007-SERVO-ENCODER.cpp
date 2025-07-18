#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN   19
#define DT_PIN      16
#define CLK_PIN     17
#define SW_PIN      18
#define SERVO_STEPS 10

Servo servo;

int servoValue = 90;
bool dt = false;
bool clk = false;
bool clkOld = false;
volatile bool buttonPressed = false;

void buttonHandler() {
    buttonPressed = true;
}

void setup() 
{
  Serial.begin(115200);
  servo.attach(SERVO_PIN, 550, 2300);
  servo.write(servoValue);
  pinMode(DT_PIN, INPUT);
  pinMode(CLK_PIN, INPUT);
  pinMode(SW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(SW_PIN), buttonHandler, FALLING);
}

void loop() 
{
  dt = digitalRead(DT_PIN);
  clk = digitalRead(CLK_PIN);
  
  if(clk != clkOld && clk == LOW) {
    if(clk == dt) {
      servoValue = constrain(servoValue + SERVO_STEPS, 0, 180);
    }
    if(clk != dt) {
      servoValue = constrain(servoValue - SERVO_STEPS, 0, 180);
    }
    servo.write(servoValue);
    Serial.println(servoValue);
  }
  clkOld = clk;

  if(buttonPressed) {
    servoValue = 90;
    Serial.println(servoValue);
    servo.write(servoValue);
    buttonPressed = false;
  }
  delay(1);
}