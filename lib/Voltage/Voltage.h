#ifndef Voltage_H
#define Voltage_H

#include <Arduino.h>

class Voltage
{
    friend class Screen;

private:
    byte volt;
    int ampere;

public:
    Voltage();
    ~Voltage();

    void begin(byte &startPin);
};

#endif