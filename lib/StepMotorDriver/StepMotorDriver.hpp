#ifndef STEP_MOTOR_DRIVER_HPP
#define STEP_MOTOR_DRIVER_HPP

#include <Arduino.h>

class StepMotorDriver
{
    public:
        StepMotorDriver(int directionPin, int stepPin, int potentiometerPin, int pulsesPerRotation=200);
        void begin(bool direction=HIGH);
        void step();
        void stop();

    private:
        bool _stopped=true;
        uint32_t _lastUpdate = 0;
        uint32_t _updateInterval = 10; 
        int _directionPin;
        int _stepPin;
        int _potentiometerPin;
        int _pulsesPerRotation;
};

#endif