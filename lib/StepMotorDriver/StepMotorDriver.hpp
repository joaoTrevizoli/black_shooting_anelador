#ifndef STEP_MOTOR_DRIVER_HPP
#define STEP_MOTOR_DRIVER_HPP

#include <Arduino.h>
#include "I2CDisplay.hpp"

class StepMotorDriver
{
    public:
        I2CDisplay* lcdDisplayPtr;

        StepMotorDriver(int directionPin, int enablePin,
         int stepPin, int potentiometerPin, I2CDisplay &lcdDisplay,
         int pulsesPerRotation=200);
        void begin(bool direction=HIGH);
        void step(int &button);
        // void step(int &button);
        void stop(int &button);
        uint8_t motorPercentageUpdate(); 

    private:
        bool _stopped=true;
        uint32_t _lastUpdate = 0;
        uint32_t _updateInterval = 10; 
        uint32_t _lastButtonPress = 0;
        uint32_t _debounceInterval = 1000;
        uint16_t _motorUptiming = 2000;
        uint16_t _motorLowertiming = 500;
        uint8_t _motorPercentage;
        float EMA_alpha = 0.1;
        uint16_t EMA_state = 0;    
        int _directionPin;
        int _enablePin;
        int _stepPin;
        int _potentiometerPin;
        int _pulsesPerRotation;

        float lowPassFilter(int potentiometerValue);

};

#endif