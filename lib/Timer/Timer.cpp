#include "Timer.h"

Timer::Timer(byte amount)
{
    prewBrightMillis = new unsigned long[amount];
}

Timer::~Timer()
{
}

void Timer::resetCounter(byte &counter)
{
    counter = maxCounter;
}

boolean Timer::unfrize(byte &counter)
{
    minusCounter(counter);

    if (counter == 0)
    {
        resetCounter(counter);
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

    if (blinkHide)
    {
        blink = false;
    }

    else
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