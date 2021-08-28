#ifndef Pot_H
#define Pot_H

#include <Arduino.h>
#include <DigiPot.h>
#include <Timer.h>
#include <Key.h>
#include <KeyPad.h>
#include <Watch.h>

// #define lampAmount 8

class Pot
{
    friend class Memory;
    friend class ScreenU8G2;
    friend class Screen;

private:
    byte Amount;

    // byte bright[lampAmount];
    byte *bright;

    byte autoMinBright = 18;
    // byte maxBright[lampAmount];
    // byte prewMaxBright[lampAmount];
    byte *maxBright;
    byte *prewMaxBright;

    byte minManualBright = 0;
    byte maxManualBright = 60;
    
    DigiPot *pot;
    // DigiPot pot[lampAmount];

public:
    Pot(byte amount);
    ~Pot();

    void setPot(DigiPot pot[]);
    void setMinBright(DigiPot &pot, byte &bright);
    void resetBright(DigiPot &pot, byte &bright);

    // void autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i);
    // void autoBright(Watch &watch, Key &key, Timer &timer);
    // void manualChangeBright(Key &key, Timer &timer);
    void autoChangeBright(Watch &watch, KeyPad &key, Timer &timer, byte i);
    void autoBright(Watch &watch, KeyPad &key, Timer &timer);
    void manualChangeBright(KeyPad &key, Timer &timer);

    void resetAllPots();
    // void changeMaxBright(Key &key, Watch &watch, Timer &timer);
    void changeMaxBright(KeyPad &key, Watch &watch, Timer &timer);

    void correctBright(boolean brightDown, DigiPot &pot, byte &bright, byte maxBright, byte id);
    // void changeBright(byte &bright, DigiPot &pot, Key &key, Timer &timer);
    void changeBright(byte &bright, DigiPot &pot, KeyPad &key, Timer &timer);
};

#endif