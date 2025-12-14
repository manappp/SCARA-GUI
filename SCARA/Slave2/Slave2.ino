#include <AccelStepper.h>
#include <Wire.h>
#include "AS5600.h"
#include <PID_v1.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6); // RX, TX

#define DIR_PIN 4
#define STEP_PIN 3

AccelStepper stepper(1, STEP_PIN, DIR_PIN);
AS5600 as5600;

// PID
double Setpoint, Input, Output;
double Kp = 25, Ki = 0.00001, Kd = 0.1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

String inputString = "";
bool newData = false;
unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);

  Wire.begin();
  as5600.begin(2);
  as5600.setOffset(-90);

  stepper.setMaxSpeed(5000);

  Setpoint = 90;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-2000, 2000);

  Serial.println("SLAVE 2 READY");
}

void loop() {
  double angle = as5600.rawAngle() * AS5600_RAW_TO_DEGREES;
  double err = angularError(Setpoint, angle);

  Input = Setpoint - err;
  myPID.Compute();

  stepper.setSpeed(-Output);
  stepper.runSpeed();

  receiveData();

  if (millis() - lastPrint > 50) {
    lastPrint = millis();
    Serial.print("SP:");
    Serial.print(Setpoint);
    Serial.print(" POS:");
    Serial.print(angle, 1);
    Serial.print(" OUT:");
    Serial.println(Output);
  }
}

void receiveData() {
  while (mySerial.available()) {
    char c = mySerial.read();
    if (c=='\n' || c=='\r') newData = true;
    else inputString += c;
  }

  if (Serial.available()) {   // input manual via USB
    char c = Serial.read();
    if (c=='\n' || c=='\r') newData = true;
    else inputString += c;
  }

  if (newData) {
    newData = false;
    parseData(inputString);
    inputString = "";
  }
}

void parseData(String data) {
  int comma = data.indexOf(',');

  if (comma == -1) {
    Setpoint = data.toFloat();   
    Serial.print("Manual SP = ");
    Serial.println(Setpoint);
    return;
  }

  float sp2 = data.substring(comma + 1).toFloat();  // untuk slave 2
  Setpoint = sp2;

  Serial.print("Master SP2 = ");
  Serial.println(Setpoint);
}

double angularError(double target, double current) {
  double e = target - current;
  while (e > 180) e -= 360;
  while (e < -180) e += 360;
  return e;
}
