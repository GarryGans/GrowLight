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

void Key::menuScreen(byte start, byte end)
{
    if (direction == FORWARD)
    {
        if (changeScreen() > end)
        {
            screen = maxBright;
        }
    }
    if (direction == BACK)
    {
        if (changeScreen() < start)
        {
            screen = setBright;
        }
    }
}

void Key::checkKeyboard()
{
    Serial.println(getNum);
}

void Key::keyCommands(Timer &timer)
{
    read();

    manualSwitchLight();
    autoScreenMove(timer);
    manualChangeScreen(timer);

    setSpeed();
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
    if (screen == lamp || screen == start)
    {
        if (autoMove && timer.next())
        {
            idChange();
        }

        if (!autoMove && timer.unfrize())
        {
            autoMove = true;
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
            autoMove = false;

            if (direction == BACK)
            {
                id--;
                id = constrain(id, 0, idLast);
            }

            else if (direction == FORWARD)
            {
                id++;

                if (id > idLast)
                {
                    id = idFirst;
                }
            }

            timer.resetCounter();
        }
    }
}

void Key::setSpeed()
{
    if (justPressed() && getNum == 10)
    {
        autoMove = false;

        if (screen == speed)
        {
            screen = lamp;
        }

        else
        {
            screen = speed;
        }
    }
    if (screen == speed || screen == interval)
    {
        if (navigation())
        {
            if (/* condition */)
            {
                /* code */
            }
        }
    }
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
    if (justPressed() && getNum == 3)
    {
        autoMove = false;

        if (screen == watch)
        {
            setDateTime = true;
            screen = lamp;
        }
        else
        {
            autoMove = false;
            screen = watch;
            return true;
        }
    }

    return false;
}

boolean Key::spectrumReDuration()
{
    if (justPressed() && getNum == 14)
    {
        autoMove = false;

        if (screen == duration)
        {
            writeTime = true;
            reduration[id] = false;
            screen = lamp;
        }

        else
        {
            screen = duration;
            return true;
        }
    }

    return false;
}

boolean Key::changeBright()
{
    if (justPressed() && getNum == 7)
    {
        autoMove = false;

        if (screen == maxBright || screen == riseBright || screen == setBright)
        {
            writeBright = true;
            screen = lamp;
        }
        else
        {
            screen = maxBright;
            return true;
        }
    }

    else if (navigation() && (screen == maxBright || screen == riseBright || screen == setBright))
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
    if (justPressed() && getNum == 2)
    {
        autoMove = false;

        if (screen == dayDuration)
        {
            writeDay = true;
            correctDay = true;
            screen = lamp;
        }
        else
        {
            screen = dayDuration;
            return true;
        }
    }

    return false;
}

void Key::skipEnable(boolean &skip)
{
    if (justPressed() && getNum == 4)
    {
        autoMove = false;

        if (!skip)
        {
            skip = true;
        }
        else
        {
            skip = false;
        }

        screen = lamp;

        writeSkip = true;
    }
}

void Key::manualSwitchLight()
{
    if (justPressed() && getNum == 1)
    {
        if (screen == manual)
        {
            resetManualPot = true;
            resetManualBright = true;

            for (byte i = 0; i < lampAmount; i++)
            {
                buttonSwitch[i] = 0;
            }

            screen = lamp;

            autoMove = true;
        }

        else
        {
            autoMove = false;

            resetManualPot = true;
            resetManualBright = true;

            screen = manual;
        }
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
