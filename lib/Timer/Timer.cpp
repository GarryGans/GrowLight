#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::minusCounter(byte &counter)
{
    if (wait(prewCounter, sec))
    {
        if (counter > 0)
        {
            counter--;
        }
    }
    if (counter == 0)
    {
        return true;
    }
    return false;
}


boolean Timer::ready(byte counter)
{
    static byte count = counter;

    if (minusCounter(count))
    {
        count = counter;
        return true;
    }

    return false;
}

boolean Timer::ready(byte counter, boolean reset)
{
    static byte count = counter;

    if (reset)
    {
        count = counter;
    }

    if (minusCounter(count))
    {
        count = counter;
        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long &prew, unsigned long set)
{
    if (millis() - prew >= set)
    {
        prew = millis();
        return true;
    }
    return false;
}

boolean Timer::riseReady(byte id)
{
    return wait(prewBright[id], rise * 10);
}

boolean Timer::blinkReady()
{
    if (millis() - prewBlink >= blinkMil)
    {
        blink = wait(prewBlink, blinkMil * 2);
    }

    return blink;
}

boolean Timer::moveReady()
{
    return move = wait(prewMove, sec / 20);
}