#include <Bright.h>

Bright::Bright()
{
}

Bright::~Bright()
{
}

void Bright::begin(byte startBrightPin)
{
    this->startPinBright = startBrightPin;

    for (byte i = 0; i < lampAmount; i++)
    {
        this->pin[i] = startBrightPin + i;
        pinMode(pin[i], OUTPUT);
        bright[i] = minManualBright;
        analogWrite(pin[i], (maxPWM - bright[i]));
    }
}

void Bright::brightLevelCount()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        maxLevel[i] = maxBright[i] - minSunSet[i];
    }
}

void Bright::setMinBright(byte pin, byte &bright, byte minSunRise)
{
    if (bright < minSunRise)
    {
        bright = minSunRise;
        analogWrite(pin, (maxPWM - bright));
    }
}

void Bright::resetBright(byte pin, byte &bright)
{
    bright = minManualBright;
    analogWrite(pin, (maxPWM - bright));
}

void Bright::autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i)
{
    if (watch.autoSwitch[i] && !key.reduration[i] && !key.reBright[i])
    {
        if (!watch.brightDown[i])
        {
            setMinBright(pin[i], bright[i], minSunRise[i]);

            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] < maxBright[i])
            {
                bright[i]++;
                analogWrite(pin[i], (maxPWM - bright[i]));
            }
        }

        if (watch.brightDown[i])
        {
            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] > minSunSet[i])
            {
                bright[i]--;
                analogWrite(pin[i], (maxPWM - bright[i]));
            }

            if (bright[i] == minSunSet[i])
            {
                resetBright(pin[i], bright[i]);
                watch.autoSwitch[i] = false;
                watch.brightDown[i] = false;
            }
        }
    }
    else if (watch.skip[i] && key.screen != key.manual)
    {
        resetBright(pin[i], bright[i]);
    }
}

void Bright::resetAllBrights()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        resetBright(pin[i], bright[i]);
    }
}

void Bright::autoBright(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen != key.manual || key.screen != key.bright)
    {
        for (byte i = 0; i < lampAmount; i++)
        {
            autoChangeBright(watch, key, timer, i);
        }
    }
    if (key.resetManualBright)
    {
        resetAllBrights();
        key.resetManualBright = false;
    }
}

void Bright::changeBright(byte &bright, byte pin, Key &key, Timer &timer, Watch &watch, byte min, byte max)
{
    if (key.valChange(timer))
    {
        if (key.act == key.MINUS && bright > min)
        {
            bright--;
        }

        else if (key.act == key.PLUS && bright < max)
        {
            bright++;
        }

        if (!watch.brightDown[key.id] && watch.autoSwitch[key.id])
        {
            this->bright[key.id] = bright;
            analogWrite(pin, (maxPWM - this->bright[key.id]));
        }

        else if (key.buttonSwitch[key.id])
        {
            analogWrite(pin, (maxPWM - bright));
        }
    }
}

void Bright::manualChangeBright(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.manual)
    {
        if (key.buttonSwitch[key.id])
        {
            changeBright(bright[key.id], pin[key.id], key, timer, watch, minManualBright, maxManualBright);
        }

        else
        {
            resetBright(pin[key.id], bright[key.id]);
        }
    }
}

void Bright::setRiseSpeed()
{
}

void Bright::setMinSet()
{
}

void Bright::setMinRise()
{
}

void Bright::changeMaxBright(Key &key, Watch &watch, Timer &timer)
{
    if (key.changeMaxBright())
    {
        key.reBright[key.id] = true;
    }

    else if (key.screen == key.bright)
    {
        changeBright(maxBright[key.id], pin[key.id], key, timer, watch, minSunRise[key.id], maxManualBright);
    }
}