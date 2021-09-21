#ifndef Brigh_H
#define Brigh_H

#include <Arduino.h>
#include <Timer.h>
#include <Key.h>
#include <Watch.h>

class Bright
{
    friend class Memory;
    friend class Screen;

private:
    byte startPinBright;

    byte pin[lampAmount];
    byte bright[lampAmount];

    byte riseBright[lampAmount]; // 197(340mA) sunRise 216(120mA) sunSet   min 196(350mA) max 22(2700ma)
    byte setBright[lampAmount];

    byte maxBright[lampAmount];

    byte minManualBright = minManual;
    byte maxManualBright = maxManual;


    byte brightLevel;
    byte lowLevel = 0;
    byte maxLevel[lampAmount];

    byte maxPWM = 255;

public:
    Bright();
    ~Bright();

    void brightLevelCount();

    void setRiseSpeed();

    void begin(byte startBrightPin);

    void setMinBright(byte pin, byte &bright, byte brightRise);
    void resetBright(byte pin, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Watch &watch, Key &key, Timer &timer);
    void resetAllBrights();
    void changeBright(Key &key, Watch &watch, Timer &timer);

    void setSetBright(byte &bright, Key &key, Timer &timer, byte min, byte max);
    void setRiseBright(byte &brightRise, Key &key, Timer &timer, byte min, byte max);
    void changeMaxBright(byte &bright, byte pin, Key &key, Timer &timer, Watch &watch, byte min, byte max);
};

#endif