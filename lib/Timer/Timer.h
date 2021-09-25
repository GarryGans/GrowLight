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
    unsigned long prewCounter;
    unsigned long sec = 1000;

    unsigned long prewScreen;
    unsigned long display = 3000;

    unsigned long prewCursor;

    unsigned long prewBlink;
    unsigned long blinkMil = 500;

    unsigned long prewBright[lampAmount];

    unsigned int rise;

    unsigned long prewMove;

    unsigned long prewUnfrize;

    unsigned long prewEsc;
    unsigned int autoEsc = 5000;

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

    boolean minusCounter(byte &counter);
    boolean wait(unsigned long &prew, unsigned long set);


    boolean riseReady(byte id);
    boolean blinkReady();
    boolean ready(byte counter = 5);
    boolean moveReady();
};

#endif