#ifndef SWITCHERS_H
#define SWITCHERS_H

#include <Arduino.h>

#include <Watch.h>
#include <Key.h>

#define OFF LOW // реле: 1 - высокого уровня (или мосфет), 0 - низкого
#define ON  HIGH

class Switchers
{
private:
    byte lamp_pins[lampAmount];

public:
    Switchers(/* args */);
    ~Switchers();

    void begin(byte &startPinLamp);
    void switcher(Watch &watch, Key &key);
};

#endif