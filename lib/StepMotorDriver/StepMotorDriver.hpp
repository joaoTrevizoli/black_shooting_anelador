#ifndef STEP_MOTOR_DRIVER_HPP
#define STEP_MOTOR_DRIVER_HPP

#include <Arduino.h>

class StepMotorDriver
{
    public:
        StepMotorDriver(int directionPin, int enablePin,  int stepPin, int potentiometerPin, int pulsesPerRotation=200);
        void begin(bool direction=HIGH);
        void step(int &button);
        void stop(int &button);
        uint8_t motorPercentage(); 

    private:
        bool _stopped=true;
        uint32_t _lastUpdate = 0;
        uint32_t _updateInterval = 10; 
        uint32_t _lastButtonPress = 0;
        uint32_t _debounceInterval = 1000;
        uint16_t _motorUptiming = 3500;
        uint16_t _motorLowertiming = 150;
        int _directionPin;
        int _enablePin;
        int _stepPin;
        int _potentiometerPin;
        int _pulsesPerRotation;
};

#endif