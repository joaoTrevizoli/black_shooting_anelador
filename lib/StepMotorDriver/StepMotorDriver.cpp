#include "StepMotorDriver.hpp"

StepMotorDriver::StepMotorDriver(int directionPin, int enablePin, int stepPin, int potentiometerPin, int pulsesPerRotation=200):
    _directionPin(directionPin),
    _enablePin(enablePin),
    _stepPin(stepPin),
    _potentiometerPin(potentiometerPin),
    _pulsesPerRotation(pulsesPerRotation)
{

}

void StepMotorDriver::begin(bool direction)
{
    pinMode(this->_stepPin, OUTPUT);
    pinMode(this->_enablePin, OUTPUT);
    pinMode(this->_directionPin, OUTPUT);
    digitalWrite(this->_directionPin, direction);
    digitalWrite(this->_enablePin, HIGH);
}

void StepMotorDriver::step(int &button)
{
    this->_updateInterval = map(analogRead(this->_potentiometerPin), 1, 1023, this->_motorUptiming, this->_motorLowertiming);
    if (micros() - this->_lastUpdate > this->_updateInterval)
    {
        this->_lastUpdate = micros();
        digitalWrite(this->_stepPin,HIGH);
        digitalWrite(this->_stepPin,LOW);
        // uint32_t start = micros();
        this->stop(button);
        // this->_lastUpdate = this->_lastUpdate - (micros() - start);
    }
}

void StepMotorDriver::stop(int &button)
{
    if ((millis() - this->_lastButtonPress > this->_debounceInterval) &&  (digitalRead(button) == HIGH))
    {
        this->_lastButtonPress = millis();
        this->_stopped = !this->_stopped;
        digitalWrite(this->_enablePin, _stopped);
   
    }
}

uint8_t StepMotorDriver::motorPercentage()
{
    return map(this->_updateInterval, this->_motorUptiming, this->_motorLowertiming, 0, 107);
}