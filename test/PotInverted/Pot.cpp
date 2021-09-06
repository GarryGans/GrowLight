//inverted
#include "Pot.h"

Pot::Pot()
{
}

Pot::~Pot()
{
}

void Pot::setPot(DigiPot pot[])
{
    for (byte i = 0; i < lampAmount; i++)
    {
        this->pot[i] = pot[i];
    }
}

void Pot::setMinBright(DigiPot &pot, byte &bright)
{
    if (bright < autoMinBright)
    {
        bright = autoMinBright;
        pot.set((99 - bright));
    }
}

void Pot::resetBright(DigiPot &pot, byte &bright)
{
    bright = minManualBright;
    pot.set((99 - bright));
}

void Pot::autoChangeBright(Watch &watch, Key &key, Timer &timer, byte i)
{
    if (watch.autoSwitch[i] && !watch.skip[i] && !key.reduration[i] && !key.reBright[i])
    {
        if (!watch.brightDown[i])
        {
            setMinBright(pot[i], bright[i]);

            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] < maxBright[i])
            {
                bright[i]++;
                pot[i].set((99 - bright[i]));
            }
        }

        if (watch.brightDown[i])
        {
            if (timer.wait(timer.prewBrightMillis[i], timer.riseMillis) && bright[i] > autoMinBright)
            {
                bright[i]--;
                pot[i].set((99 - bright[i]));
            }

            if (bright[i] == autoMinBright)
            {
                resetBright(pot[i], bright[i]);
                watch.autoSwitch[i] = false;
                watch.brightDown[i] = false;
            }
        }
    }
    else if (watch.skip[i] && key.screen != key.manual)
    {
        bright[i] = minManualBright;
        pot[i].set((99 - bright[i]));
    }
}

void Pot::autoBright(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen != key.manual || key.screen != key.bright)
    {
        for (byte i = 0; i < lampAmount; i++)
        {
            autoChangeBright(watch, key, timer, i);
        }
    }
    if (key.resetManualPot)
    {
        resetAllPots();
        key.resetManualPot = false;
    }
}

void Pot::changeBright(byte &bright, DigiPot &pot, Key &key, Timer &timer)
{
    if (key.valChange(timer))
    {
        if (key.act == key.MINUS && bright > autoMinBright)
        {
            bright--;
            pot.set((99-bright));
        }
        else if (key.act == key.PLUS && bright < maxManualBright)
        {
            bright++;
            pot.set((99 - bright));
        }
    }
}

void Pot::manualChangeBright(Key &key, Timer &timer)
{
    if (key.screen == key.manual)
    {
        if (key.buttonSwitch[key.id])
        {
            setMinBright(pot[key.id], bright[key.id]);
            changeBright(bright[key.id], pot[key.id], key, timer);
        }

        else
        {
            bright[key.id] = minManualBright;
            pot[key.id].set((99 - bright[key.id]));
        }
    }
}

void Pot::resetAllPots()
{
    for (byte i = 0; i < lampAmount; i++)
    {
        bright[i] = minManualBright;
        pot[i].set((99 - bright[i]));
    }
}

void Pot::correctBright(boolean brightDown, DigiPot &pot, byte &bright, byte maxBright, byte id)
{
    if (!brightDown && prewMaxBright[id] > maxBright)
    {
        bright = maxBright;
        pot.set((99-bright));
    }
}

void Pot::changeMaxBright(Key &key, Watch &watch, Timer &timer)
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
            correctBright(watch.brightDown[key.id], pot[key.id], bright[key.id], maxBright[key.id], key.id);
        }

        key.correctBright = false;
        key.reBright[key.id] = false;
    }
}
