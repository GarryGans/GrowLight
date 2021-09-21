#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Data.h>

class Timer
{
    friend class Pot;
    friend class Bright;
    friend class Screen;
    friend class Key;
    friend class EFX;
    friend class Memory;

private:
    unsigned long prewCounterMil;
    unsigned long secMil = 1000;

    unsigned long prewScreenMil;
    unsigned long displayMil = 3000;

    unsigned long prewCursorMil;

    unsigned long prewBlinkMil;
    unsigned long blinkMil = 500;

    unsigned long prewBrightMil[lampAmount];

    unsigned int riseMil;

    unsigned long prewMoveMil;

    const byte maxEscapeCounter = 5;
    byte escapeCounter = maxEscapeCounter;

    byte maxCounter = 5;

    byte unfrizeCounter = maxCounter;

    boolean escBar;
    boolean blink;
    boolean move;

public:
    Timer();
    ~Timer();

    void minusCounter(byte &counter);
    boolean wait(unsigned long &prewMil, unsigned long setMil);

    boolean riseReady(byte id);
    boolean next();
    boolean blinkReady();
    boolean unfrize();
    void resetCounter();
    boolean moveReady();
};

#endif