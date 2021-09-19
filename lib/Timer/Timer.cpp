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
    if ((millis() - prewCounterMil >= secMil))
    {
        prewCounterMil = millis();
        if (counter > 0)
        {
            counter--;
        }
    }
}

boolean Timer::wait(unsigned long &prewMil, unsigned long setMil)
{
    if (millis() - prewMil >= setMil)
    {
        prewMil = millis();
        return true;
    }
    return false;
}

boolean Timer::riseReady(byte id)
{
    return wait(prewBrightMil[id], riseMil);
}

boolean Timer::next()
{
    return wait(prewScreenMil, displayMil);
}

boolean Timer::blinkReady()
{
    if (millis() - prewBlinkMil >= blinkMil)
    {
        blink = false;

        if (millis() - prewBlinkMil >= blinkMil * 2)
        {
            prewBlinkMil = millis();
            blink = true;
        }
    }

    return blink;
}

boolean Timer::moveReady()
{
    move = false;

    if (millis() - prewMoveMil >= secMil / 20)
    {
        prewMoveMil = millis();
        move = true;
    }

    return move;
}