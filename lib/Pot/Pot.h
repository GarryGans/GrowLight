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
    Timer timer;

    byte speed;

    DigiPot pot[lampAmount];
    byte bright[lampAmount];

    byte riseBright[lampAmount];
    byte setBright[lampAmount];

    byte maxBright[lampAmount];

    byte minManualBright = 0;
    byte maxManualBright = 99;

    byte brightLevel;
    byte lowLevel = 0;
    byte maxLevel[lampAmount];

    byte allBrigh;
    byte maxAllBright = 99;

public:
    Pot();
    ~Pot();

    void brightLevelCount();

    void setRiseSpeed(Key &key);

    void begin(DigiPot pot[]);

    void setMinBright(DigiPot &pot, byte &bright, byte brightRise);
    void resetBright(DigiPot &pot, byte &bright);

    void autoChangeBright(Watch &watch, Key &key, byte i);
    void autoBright(Watch &watch, Key &key);
    void manualChangeBright(Watch &watch, Key &key);
    void resetAllPots();
    void changeMaxBright(byte &bright, DigiPot &pot, Key &key, Watch &watch, byte min, byte max);

    void setSetBright(byte &bright, Key &key, byte min, byte max);
    void setRiseBright(byte &brightRise, Key &key, byte min, byte max);
    void changeMaxBright(Key &key, Watch &watch);

    boolean setAllBrigh(Key &key);

    void commands(Watch &watch, Key &key);
};

#endif