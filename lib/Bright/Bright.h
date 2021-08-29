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

    byte autoMinBright = 198;
    // byte *maxBright;
    // byte *prewMaxBright;
    byte maxBright[lampAmount];
    byte prewMaxBright[lampAmount];

    byte minManualBright = 255;
    byte maxManualBright = 0;

public:
    Bright();
    ~Bright();

    void begin(byte startBrightPin);

    void setMinBright(byte pin, byte &bright);
    void resetBright(byte pin, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Key &key, Timer &timer);
    void resetAllBrights();
    void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void correctBright(boolean brightDown, byte pin, byte &bright, byte maxBright, byte id);
    void changeBright(byte &bright, byte pin, Key &key, Timer &timer);
};

#endif