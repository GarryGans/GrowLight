#include <Bright.h>

Bright::Bright(byte amount)
{
    Amount = amount;

    pin = new byte[Amount];
    bright = new byte[Amount];

    maxBright = new byte[Amount];
    prewMaxBright = new byte[Amount];
}

Bright::~Bright()
{
}

void Bright::begin(byte startBrightPin)
{
    this->startPinBright = startBrightPin;

    for (byte i = 0; i < Amount; i++)
    {
        this->pin[i] = startBrightPin + i;
        pinMode(pin[i], OUTPUT);
        analogWrite(pin[i], 0);
    }
}

void Bright::setMinBright(byte pin, byte &bright)
{
    if (bright < autoMinBright)
    {
        bright = autoMinBright;
        analogWrite(pin, bright);
    }
}

void Bright::resetBright(byte pin, byte &bright)
{
    bright = minManualBright;
    analogWrite(pin, bright);
}

// void Bright::autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i)
void Bright::autoChangeBright(Watch &watch, KeyPad &key, Timer &timer, byte i)
{
    if (watch.autoSwitch[i] && !watch.skip[i] && !key.reduration[i] && !key.reBright[i])
    {
        if (!watch.brightDown[i])
        {
            setMinBright(pin[i], bright[i]);

            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] < maxBright[i])
            {
                bright[i]++;
                analogWrite(pin[i], bright[i]);
            }
        }

        if (watch.brightDown[i])
        {
            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] > autoMinBright)
            {
                bright[i]--;
                analogWrite(pin[i], bright[i]);
            }

            if (bright[i] == autoMinBright)
            {
                watch.autoSwitch[i] = false;
                watch.brightDown[i] = false;
                resetBright(pin[i], bright[i]);
            }
        }
    }
    else if (watch.skip[i] && key.screen != key.manual)
    {
        bright[i] = minManualBright;
        analogWrite(pin[i], bright[i]);
    }
}

// void Bright::autoBright(Watch &watch, Key &key, Timer &timer)
void Bright::autoBright(Watch &watch, KeyPad &key, Timer &timer)
{
    if (key.screen != key.manual || key.screen != key.bright)
    {
        for (byte i = 0; i < Amount; i++)
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

// void Bright::manualChangeBright(Key &key, Timer &timer)
void Bright::manualChangeBright(KeyPad &key, Timer &timer)
{
    if (key.screen == key.manual)
    {
        if (key.buttonSwitch[key.id])
        {
            changeBright(bright[key.id], pin[key.id], key, timer);
        }

        else
        {
            bright[key.id] = minManualBright;
            analogWrite(pin[key.id], bright[key.id]);
        }
    }
}

void Bright::resetAllBrights()
{
    for (byte i = 0; i < Amount; i++)
    {
        bright[i] = minManualBright;
        analogWrite(pin[i], 0);
    }
}

void Bright::correctBright(boolean brightDown, byte pin, byte &bright, byte maxBright, byte id)
{
    if (!brightDown)
    {
        if (bright > maxBright)
        {
            bright = maxBright;
            analogWrite(pin, bright);
        }

        else if (bright < maxBright)
        {
            bright = maxBright;
            analogWrite(pin, bright);
        }
    }

    else if (brightDown)
    {
        if (prewMaxBright[id] > maxBright)
        {
            bright -= (prewMaxBright[id] - maxBright);
            analogWrite(pin, bright);
        }

        else if (prewMaxBright[id] < maxBright)
        {

            bright += (maxBright - prewMaxBright[id]);
            analogWrite(pin, bright);
        }
    }
}

// void Bright::changeMaxBright(Key &key, Watch &watch, Timer &timer)
void Bright::changeMaxBright(KeyPad &key, Watch &watch, Timer &timer)
{
    if (key.changeMaxBright())
    {
        prewMaxBright[key.id] = maxBright[key.id];
        key.reBright[key.id] = true;
    }

    else if (key.screen == key.bright)
    {
        if (key.valChange(timer))
        {
            if (key.act == key.MINUS && maxBright[key.id] > autoMinBright)
            {
                maxBright[key.id]--;
            }

            if (key.act == key.PLUS && maxBright[key.id] < maxManualBright)
            {
                maxBright[key.id]++;
            }
        }
    }

    if (key.correctBright)
    {
        if (watch.autoSwitch[key.id])
        {
            correctBright(watch.brightDown[key.id], pin[key.id], bright[key.id], maxBright[key.id], key.id);
        }

        key.correctBright = false;
        key.reBright[key.id] = false;
    }
}

// void Bright::changeBright(byte &bright, byte pin, Key &key, Timer &timer)
void Bright::changeBright(byte &bright, byte pin, KeyPad &key, Timer &timer)
{
    if (key.valChange(timer))
    {
        if (key.act == key.MINUS && bright > minManualBright)
        {
            bright--;
            analogWrite(pin, bright);
        }
        else if (key.act == key.PLUS && bright < maxManualBright)
        {
            bright++;
            analogWrite(pin, bright);
        }
    }
}
