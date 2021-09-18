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

    byte minSunRise[lampAmount] ; // 197(340mA) sunRise 216(120mA) sunSet   min 196(350mA) max 22(2700ma)
    byte minSunSet[lampAmount] ;

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

    void setMinRise();
    void setMinSet();
    void setRiseSpeed();

    void begin(byte startBrightPin);

    void brightLevelCount();

    void setMinBright(byte pin, byte &bright, byte minSunRise);
    void resetBright(byte pin, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Watch &watch, Key &key, Timer &timer);
    void resetAllBrights();
    void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void changeBright(byte &bright, byte pin, Key &key, Timer &timer, Watch &watch, byte min, byte max);
};

#endif