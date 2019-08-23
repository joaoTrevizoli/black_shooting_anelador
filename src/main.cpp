#include <Arduino.h>
#include "StepMotorDriver.hpp"
#include "I2CDisplay.hpp"

#define LCD_ADDR 0X27

// define números de pinos do driver no arduino
const int stepPin = 3;
const int enPin = 7;
const int dirPin = 2;
int startStopPin = 8;

const int potentioPin = A0;

I2CDisplay lcd(LCD_ADDR, 2, 16);
StepMotorDriver stepMotor(dirPin, enPin, stepPin, potentioPin, lcd);

void setup () {
    pinMode(startStopPin, INPUT);

    lcd.begin();
    lcd.lcd.setCursor(0, 0);
    lcd.lcd.print("SMA Eagle Anneal");
    
    stepMotor.begin();
    
    Serial.begin(9600);
}


void loop() {
    stepMotor.step(startStopPin);
}  