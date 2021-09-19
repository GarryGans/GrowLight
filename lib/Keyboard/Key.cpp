#include "Key.h"

Key::Key(byte pin[]) : AmperkaKB(pin[0], pin[1], pin[2], pin[3], pin[4], pin[5], pin[6], pin[7])
{
}

Key::Key()
{
}

Key::~Key()
{
}

Key::Screen Key::changeScreen()
{
    if (direction == FORWARD)
    {
        screen = (Screen)(Key::screen + 1);
    }

    else if (direction == BACK)
    {
        screen = (Screen)(Key::screen - 1);
    }

    return screen;
}

void Key::checkKeyboard()
{
    Serial.println(getNum);
}

void Key::setScreens()
{
    dayReduration();
}

void Key::keyCommands(Timer &timer)
{
    read();

    manualSwitchLight();
    autoScreenMove(timer);
    manualChangeScreen(timer);

    home();
}

void Key::idChange()
{
    id++;

    if (id > idLast)
    {
        id = idFirst;
    }
}

void Key::autoScreenMove(Timer &timer)
{
    if (screen == lamp)
    {
        if (autoMove && timer.next())
        {
            idChange();
        }
    }
}

boolean Key::navigation()
{
    if (onHold() || justPressed())
    {
        if (getNum == 8)
        {
            direction = FORWARD;
            return true;
        }

        else if (getNum == 12)
        {
            direction = BACK;
            return true;
        }
    }

    return false;
}

boolean Key::valChange()
{
    if (onHold() || justPressed())
    {
        if (getNum == 6)
        {
            act = MINUS;
            return true;
        }

        else if (getNum == 15)
        {
            act = PLUS;
            return true;
        }
    }

    return false;
}

void Key::manualChangeScreen(Timer &timer)
{
    if (screen == lamp || screen == manual)
    {
        if (navigation())
        {
            if (direction == BACK)
            {
                autoMove = false;

                id--;
                id = constrain(id, 0, idLast);
            }

            else if (direction == FORWARD)
            {
                autoMove = false;

                id++;
                if (id > idLast)
                {
                    id = idFirst;
                }
            }

            timer.resetCounter();
        }

        if (!autoMove && screen != manual)
        {
            if (timer.unfrize())
            {
                autoMove = true;
            }
        }
    }
}

void Key::reset()
{
    resetManualPot = true;
    resetManualBright = true;

    for (byte i = 0; i < lampAmount; i++)
    {
        buttonSwitch[i] = 0;
    }
}

void Key::home()
{
    if (justPressed() && getNum == 10)
    {
        screen = start;
    }
}

void Key::setMode()
{
    if (screen == duration)
    {
        writeTime = true;
        reduration[id] = false;
    }

    else if (screen == dayDuration)
    {
        writeDay = true;
        correctDay = true;
    }

    else if (screen == maxBright)
    {
        writeBright = true;
        reBright[id] = false;
    }

    else if (screen == watch)
    {
        setDateTime = true;
    }

    else if (screen == manual)
    {
        reset();
        autoMove = true;
    }
}

boolean Key::checkSet(Screen set)
{
    if (screen != lamp)
    {
        setMode();
    }

    if (screen != set)
    {
        if (set == manual)
        {
            autoMove = false;
            resetManualPot = true;
            resetManualBright = true;
        }

        screen = set;
        return true;
    }

    else if (screen == set)
    {
        screen = lamp;
    }

    return false;
}

boolean Key::ok()
{
    if (justPressed() && getNum == 9)
    {
        return true;
    }
    return false;
}

boolean Key::setWatch()
{
    if ((justPressed() && getNum == 3) || (screen == watch && ok()))
    {
        return checkSet(watch);
    }

    return false;
}

boolean Key::spectrumReDuration()
{
    if ((justPressed() && getNum == 14) || (screen == duration && ok()))
    {
        return checkSet(duration);
    }

    return false;
}

boolean Key::changeBright()
{
    if ((justPressed() && getNum == 7) || (screen == maxBright && ok()))
    {
        return checkSet(maxBright);
    }

    else if (navigation() && (screen == maxBright || screen == setBright || screen == riseBright))
    {
        writeBright = true;

        if (direction == FORWARD)
        {
            if (changeScreen() > setBright)
            {
                screen = maxBright;
            }
        }
        if (direction == BACK)
        {
            if (changeScreen() < maxBright)
            {
                screen = setBright;
            }
        }
    }

    return false;
}

boolean Key::dayReduration()
{
    if ((justPressed() && getNum == 2) || (screen == dayDuration && ok()))
    {
        return checkSet(dayDuration);
    }

    return false;
}

void Key::skipEnable(boolean &skip)
{
    if (justPressed() && getNum == 4)
    {
        // setMode();

        if (!skip)
        {
            skip = true;
        }
        else
        {
            skip = false;
        }

        writeSkip = true;
    }
}

void Key::manualSwitchLight()
{
    if (justPressed() && getNum == 1)
    {
        checkSet(manual);
    }

    if (screen == manual && ok())
    {
        if (!buttonSwitch[id])
        {
            buttonSwitch[id] = true;
        }

        else
        {
            buttonSwitch[id] = false;
        }
    }
}
