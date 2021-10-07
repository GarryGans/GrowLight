#include "Pot.h"

Pot::Pot()
{
}

Pot::~Pot()
{
}

void Pot::begin(DigiPot pot[])
{
    for (byte i = 0; i < lampAmount; i++)
    {
        this->pot[i] = pot[i];
        pot[i].reset();
        bright[i] = pot[i].get();
    }
}

void Pot::brightLevelCount()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        maxLevel[i] = maxBright[i] - setBright[i];
    }
}

void Pot::setMinBright(DigiPot &pot, byte &bright, byte brightRise)
{
    if (bright < brightRise)
    {
        pot.set(brightRise);
        bright = pot.get();
    }
}

void Pot::resetBright(DigiPot &pot, byte &bright)
{
    pot.reset();
    bright = pot.get();
}

void Pot::autoChangeBright(Watch &watch, Key &key, byte i)
{
    if (watch.autoSwitch[i] && !key.reduration[i] && !key.reBright[i])
    {
        if (!watch.brightDown[i])
        {
            setMinBright(pot[i], bright[i], riseBright[i]);

            if (timer.riseReady(speed, i) && bright[i] < maxBright[i])
            {
                pot[i].increase(1);
                bright[i] = pot[i].get();
            }
        }

        if (watch.brightDown[i])
        {
            if (timer.riseReady(speed, i) && bright[i] > setBright[i])
            {
                pot[i].decrease(1);
                bright[i] = pot[i].get();
            }

            if (bright[i] == setBright[i])
            {
                watch.autoSwitch[i] = false;
                watch.brightDown[i] = false;
                resetBright(pot[i], bright[i]);
            }
        }
    }
    else if (watch.skip[i] && key.screen != key.manual)
    {
        resetBright(pot[i], bright[i]);
    }
}

void Pot::resetAllPots()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        resetBright(pot[i], bright[i]);
    }
}

void Pot::autoBright(Watch &watch, Key &key)
{
    if (key.screen != key.manual || key.screen != key.maxBright)
    {
        for (byte i = 0; i < lampAmount; i++)
        {
            autoChangeBright(watch, key, i);
        }
    }
    if (key.resetManualPot)
    {
        resetAllPots();
        key.resetManualPot = false;
    }
}

void Pot::changeMaxBright(byte &bright, DigiPot &pot, Key &key, Watch &watch, byte min, byte max)
{
    if (key.valChange())
    {
        if (key.act == key.MINUS && bright > min)
        {
            bright--;

            if (!watch.brightDown[key.id] && watch.autoSwitch[key.id])
            {
                pot.decrease(1);
            }
        }
        else if (key.act == key.PLUS && bright < max)
        {
            bright++;

            if (!watch.brightDown[key.id] && watch.autoSwitch[key.id])
            {
                pot.increase(1);
            }
        }

        if (key.buttonSwitch[key.id])
        {
            pot.set(bright);
        }
    }
}

void Pot::manualChangeBright(Watch &watch, Key &key)
{
    if (key.screen == key.manual)
    {
        if (key.buttonSwitch[key.id])
        {
            setMinBright(pot[key.id], bright[key.id], riseBright[key.id]);
            changeMaxBright(bright[key.id], pot[key.id], key, watch, minManualBright, maxManualBright);
        }

        else
        {
            resetBright(pot[key.id], bright[key.id]);
        }
    }
}

void Pot::setRiseSpeed(Key &key)
{
    if (key.screen == key.speed)
    {
        if (key.valChange())
        {
            key.act == key.MINUS ? speed-- : speed++;

            if (speed < 0)
                speed = 255;

            if (speed > 255)
                speed = 0;
        }
    }
}

void Pot::setSetBright(byte &bright, Key &key, byte min, byte max)
{
    if (key.valChange())
    {
        if (key.act == key.MINUS && bright > min)
        {
            bright--;
        }

        else if (key.act == key.PLUS && bright < max)
        {
            bright++;
        }

        bright = constrain(bright, min, max);
    }
}

void Pot::setRiseBright(byte &brightRise, Key &key, byte min, byte max)
{
    if (key.valChange())
    {
        if (key.act == key.MINUS && brightRise > min)
        {
            brightRise--;
        }

        else if (key.act == key.PLUS && brightRise < max)
        {
            brightRise++;
        }
    }
}

void Pot::changeBright(Key &key, Watch &watch)
{
    if (key.changeBright())
    {
        switch (key.screen)
        {
        case key.maxBright:

            changeMaxBright(maxBright[key.id], pot[key.id], key, watch, riseBright[key.id], maxManualBright);
            break;

        case key.riseBright:

            setRiseBright(riseBright[key.id], key, minManualBright, maxBright[key.id]);
            break;

        case key.setBright:

            setSetBright(setBright[key.id], key, minManualBright, maxBright[key.id]);
            break;

        default:
            break;
        }
    }
}

boolean Pot::setAllBrigh(Key &key)
{
    if (key.allBrigh())
    {
        if (key.act == key.MINUS && allBrigh > 0)
            allBrigh--;

        else if (key.act == key.PLUS && allBrigh < maxAllBright)
            allBrigh++;
    }

    if (key.screen == key.bright)
    {
        return true;
    }

    return false;
}

void Pot::commands(Watch &watch, Key &key)
{
    autoBright(watch, key);
    manualChangeBright(watch, key);
    changeBright(key, watch);
    setRiseSpeed(key);
}
