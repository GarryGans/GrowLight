#ifndef Brigh_H
#define Brigh_H

#include <Arduino.h>
#include <Timer.h>
#include <Key.h>
#include <Watch.h>

class Bright
{
    friend class Memory;
    friend class ScreenU8G2;
    friend class Screen;

private:
    byte startPinBright;
    // byte *pin;
    // byte *bright;
    byte pin[lampAmount];
    byte bright[lampAmount];

    byte minSunRise = minSunRiseBright; // 197(340mA) sunRise 216(120mA) sunSet   min 196(350mA) max 22(2700ma)
    byte minSunSet = minSunSetBright;
    // byte *maxBright;
    // byte *prewMaxBright;
    byte maxBright[lampAmount];
    byte prewMaxBright[lampAmount];

    byte minManualBright = minManual;
    byte maxManualBright = maxManual;

    byte brightLevel;
    byte lowLevel = 0;
    byte maxLevel[lampAmount];

    byte maxPWM = 255;

public:
    Bright();
    ~Bright();

    //void setMinManual();
    //void setMaxManual();
    //void setMinRise();
    //void setMinSet();
    //void setRiseSpeed();

    void begin(byte startBrightPin);

    void brightLevelCount();

    void setMinBright(byte pin, byte &bright);
    void resetBright(byte pin, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Watch &watch, Key &key, Timer &timer);
    void resetAllBrights();
    void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void changeBright(byte &bright, byte pin, Key &key, Timer &timer, Watch &watch, byte min, byte max);
};

#endif