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
    friend class Screen;

private:
    byte Amount;

    boolean reBright[lampAmount];

    byte riseBright[lampAmount];
    byte setBright[lampAmount];

    byte bright[lampAmount];

    byte autoMinBright = 0;
    byte maxBright[lampAmount];

    byte minManualBright = 0;
    byte maxManualBright = 99;

    DigiPot pot[lampAmount];

public:
    Pot();
    ~Pot();

    void setPot(DigiPot pot[]);
    void setMinBright(DigiPot &pot, byte &bright);
    void resetBright(DigiPot &pot, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    void autoBright(Watch &watch, Key &key, Timer &timer);
    void manualChangeBright(Key &key, Timer &timer);
    void resetAllPots();
    void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void changeBright(byte &bright, DigiPot &pot, Key &key, Timer &timer);
};

#endif