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
    unsigned long prew;
    boolean first;

    unsigned long sec = 1000;

    unsigned long display = 3000;

    unsigned int autoEsc = 5000;

    const byte maxEscapeCounter = 5;
    byte escapeCounter = maxEscapeCounter;

    byte maxCounter = 5;

    byte unfrizeCounter = maxCounter;

    boolean first2;
    byte count;
    boolean blink;

public:
    Timer();
    ~Timer();

    boolean minusCounter(byte &counter);
    boolean wait(unsigned long set);

    boolean alternation(unsigned long set = 500);

    boolean ready(byte counter = 5, boolean reset = false);
};

#endif