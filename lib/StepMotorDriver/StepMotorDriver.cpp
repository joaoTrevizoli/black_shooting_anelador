#include "StepMotorDriver.hpp"

StepMotorDriver::StepMotorDriver(int directionPin, int stepPin, int potentiometerPin, int pulsesPerRotation=200):
    _directionPin(directionPin),
    _stepPin(stepPin),
    _potentiometerPin(potentiometerPin),
    _pulsesPerRotation(pulsesPerRotation)
{

}

void StepMotorDriver::begin(bool direction)
{
    pinMode(this->_stepPin, OUTPUT);
    pinMode(this->_directionPin, OUTPUT);
    digitalWrite(this->_directionPin, direction);
}

void StepMotorDriver::step()
{
    this->_updateInterval = map(analogRead(this->_potentiometerPin), 1, 1023, 20000, 4000);
    if (micros() - this->_lastUpdate > this->_updateInterval && !this->_stopped)
    {
        this->_lastUpdate = micros();
        digitalWrite(this->_stepPin,HIGH);
        digitalWrite(this->_stepPin,LOW);
    }
}

void StepMotorDriver::stop()
{
    this->_stopped = !this->_stopped;
}