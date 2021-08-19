#ifndef Brigh_H
#define Brigh_H

#include <Arduino.h>
#include <Timer.h>
#include <Key.h>
#include <Watch.h>
// #include <Data.h>

class Bright
{
    friend class Memory;
    friend class ScreenU8G2;
    friend class Screen;

private:
    byte startPinBright;
    byte pin[lampAmount];
    int bright[lampAmount];

    int autoMinBright = 0;
    int maxBright[lampAmount];
    int prewMaxBright[lampAmount];

    int minManualBright = 0;
    int maxManualBright = 255;

public:
    Bright(/* args */);
    ~Bright();

    void begin(byte startBrightPin);

    void setMinBright(byte pin, int &bright);
    void resetBright(byte pin, int &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Key &key, Timer &timer);
    void resetAllBrights();
    void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void correctBright(boolean brightDown, byte pin, int &bright, int maxBright, int id);
    void changeBright(int &bright, byte pin, Key &key, Timer &timer);
};

#endif