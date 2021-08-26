#ifndef Pot_H
#define Pot_H

#include <Arduino.h>
#include <DigiPot.h>
#include <Timer.h>
#include <Key.h>
#include <Watch.h>

class Pot
{
    friend class Memory;
    friend class ScreenU8G2;
    friend class Screen;

private:
    byte bright[lampAmount];

    byte autoMinBright = 0;
    byte maxBright[lampAmount];
    byte prewMaxBright[lampAmount];

    byte minManualBright = 0;
    byte maxManualBright = 100;
    DigiPot pot[lampAmount];

public:
    Pot(/* args */);
    ~Pot();

    void setPot(DigiPot pot[]);
    void setMinBright(DigiPot &pot, byte &bright);
    void resetBright(DigiPot &pot, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Key &key, Timer &timer);
    void resetAllPots();
    void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void correctBright(boolean brightDown, DigiPot &pot, byte &bright, byte maxBright, byte id);
    void changeBright(byte &bright, DigiPot &pot, Key &key, Timer &timer);
};

#endif