#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <Data.h>

// #define lampAmount 4

class Timer
{
    friend class Pot;
    friend class Bright;
    friend class ScreenU8G2;
    friend class Screen;
    friend class Key;

private:
    unsigned long prewCounterMillis;
    unsigned long secMillis = 1000;

    unsigned long prewScreenMillis;
    unsigned long displayMillis = 3000;

    unsigned long prewCursorMillis;

    unsigned long prewBlinkMillis;
    unsigned long blinkMillis = 500;

    unsigned long prewBrightMillis[lampAmount];
    unsigned long riseMillis = 10;

    unsigned long prewMoveMillis;

    const byte maxEscapeCounter = 5;
    byte escapeCounter = maxEscapeCounter;

    byte maxCounter = 5;

    byte unfrizeCounter = maxCounter;

    boolean escBar;
    boolean blink;
    boolean blinkHide;
    boolean move;


public:
    Timer();
    ~Timer();

    void minusCounter(byte &counter);
    boolean wait(unsigned long &prewMillis, unsigned long setMillis);
    boolean blinkReady();
    boolean unfrize(byte &counter);
    void resetCounter(byte &counter);
    boolean moveReady();
};

#endif