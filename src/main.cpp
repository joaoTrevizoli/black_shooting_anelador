#include <Arduino.h>
#include "StepMotorDriver.hpp"
#include "I2CDisplay.hpp"

// define números de pinos do driver no arduino
const int stepPin = 3;
const int enPin = 7;
const int dirPin = 2;
int startStopPin = 8;

const int potentioPin = A0;



StepMotorDriver stepMotor(dirPin, enPin, stepPin, potentioPin);


void setup () {
    stepMotor.begin();
    pinMode(startStopPin, INPUT);
    Serial.begin(9600);
}


void loop() {
    stepMotor.step(startStopPin);
    // stepMotor.stop(startStopPin);
    // Serial.println(stepMotor.motorPercentage());
}  