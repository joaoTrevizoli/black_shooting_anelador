#include <Arduino.h>
#include "StepMotorDriver.hpp"

// define números de pinos do driver no arduino
const int stepPin = 3;
const int dirPin = 2;
const int potentioPin = A0;

StepMotorDriver stepMotor(dirPin, stepPin, potentioPin);


void setup () {

    stepMotor.begin();
    Serial.begin(9600);
}


void loop() {
    stepMotor.step();
    
}  