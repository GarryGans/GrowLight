#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

boolean Timer::minusCounter(byte &counter)
{
    if (wait(sec))
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

boolean Timer::ready(byte counter, boolean reset)
{
    // static boolean first;

    if (reset || !first2)
    {
        count = counter;
        first2 = true;
    }

    if (minusCounter(count))
    {
        count = counter;
        first2 = false;
        return true;
    }

    return false;
}

boolean Timer::wait(unsigned long set)
{
    if (!first)
    {
        first = true;
        prew = millis();
    }

    if (millis() - prew >= set)
    {
        // prew = millis();
        first = false;
        return true;
    }

    return false;
}

boolean Timer::alternation(unsigned long set)
{
    // static boolean blink;

    if (wait(set))
    {
        if (!blink)
        {
            blink = true;
        }
        else
        {
            blink = false;
        }
    }

    return blink;
}
