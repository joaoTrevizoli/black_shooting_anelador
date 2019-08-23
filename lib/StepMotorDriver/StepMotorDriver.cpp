#include "StepMotorDriver.hpp"

StepMotorDriver::StepMotorDriver(int directionPin, int enablePin,
 int stepPin, int potentiometerPin,
 I2CDisplay &lcdDisplay, int pulsesPerRotation=200):
    _directionPin(directionPin),
    _enablePin(enablePin),
    _stepPin(stepPin),
    _potentiometerPin(potentiometerPin),
    lcdDisplayPtr(&lcdDisplay),
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
    this->EMA_state = analogRead(this->_potentiometerPin);
    this->_motorPercentage = this->motorPercentageUpdate();
    this->lcdDisplayPtr->logValue(1, "%", this->_motorPercentage);
}


void StepMotorDriver::step(int &button)
{
    this->EMA_state = lowPassFilter(analogRead(this->_potentiometerPin));

    this->_updateInterval = map(this->EMA_state, 0, 960, this->_motorUptiming, this->_motorLowertiming);
    if (micros() - this->_lastUpdate > this->_updateInterval)
    {
        this->_lastUpdate = micros();
        digitalWrite(this->_stepPin,HIGH);
        digitalWrite(this->_stepPin,LOW);
        uint8_t mPerc = this->motorPercentageUpdate();
        
        if (mPerc < (this->_motorPercentage - 1) || mPerc > (this->_motorPercentage + 1))
        {
            this->lcdDisplayPtr->logValue(1, "%", mPerc);
            this->_motorPercentage = mPerc;
        }
        this->stop(button);

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

uint8_t StepMotorDriver::motorPercentageUpdate()
{
    uint8_t speed =  map(this->EMA_state, 1, 1000, 0, 106);

    if (speed > 100)
        return 100;
    return speed;
}

float StepMotorDriver::lowPassFilter(int potentiometerValue)
{
    return (this->EMA_alpha * potentiometerValue) + ((1-EMA_alpha)*EMA_state); 
}