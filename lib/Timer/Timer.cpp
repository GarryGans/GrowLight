#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::resetCounter()
{
    unfrizeCounter = maxCounter;
}

boolean Timer::unfrize()
{
    minusCounter(unfrizeCounter);

    if (unfrizeCounter == 0)
    {
        resetCounter();
        return true;
    }

    return false;
}

void Timer::minusCounter(byte &counter)
{
    if ((millis() - prewCounterMillis >= secMillis))
    {
        prewCounterMillis = millis();
        if (counter > 0)
        {
            counter--;
        }
    }
}

boolean Timer::wait(unsigned long &prewMillis, unsigned long setMillis)
{
    if (millis() - prewMillis >= setMillis)
    {
        prewMillis = millis();
        return true;
    }
    return false;
}

boolean Timer::blinkReady()
{
    if (millis() - prewBlinkMillis >= blinkMillis)
    {
        blink = false;

        if (millis() - prewBlinkMillis >= blinkMillis * 2)
        {
            prewBlinkMillis = millis();
            blink = true;
        }
    }

    return blink;
}

boolean Timer::moveReady()
{
    move = false;

    if (millis() - prewMoveMillis >= secMillis / 20)
    {
        prewMoveMillis = millis();
        move = true;
    }

    return move;
}