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

// boolean Timer::ready(byte counter)
// {
//     static byte count = counter;

//     if (minusCounter(count))
//     {
//         count = counter;
//         return true;
//     }

//     return false;
// }

boolean Timer::ready(byte counter, boolean reset)
{
    static byte count;

    static boolean flag;

    if (reset || !flag)
    {
        count = counter;
        Serial.println("good");
        flag = true;
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

boolean Timer::riseReady(byte speed, byte id)
{
    return wait(prewBright[id], speed * 10);
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