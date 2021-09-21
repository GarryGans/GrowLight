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

void Key::menuScreen(Screen start, Screen end)
{
    if (navigation())
    {
        if (direction == FORWARD)
        {
            if (changeScreen() > end)
            {
                screen = start;
            }
        }

        if (direction == BACK)
        {
            if (changeScreen() < start)
            {
                screen = end;
            }
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

    setSpeed(timer);
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

void Key::setSpeed(Timer &timer)
{
    if (justPressed() && getNum == 10)
    {
        autoMove = false;

        if (screen == speed || screen == interval)
        {
            screen = lamp;
            writeSpeed = true;
            writeInterval = true;
        }

        else
        {
            screen = speed;
        }
    }

    if (screen == speed || screen == interval)
    {
        menuScreen(speed, interval);
    }

    if (screen == speed)
    {
        if (valChange())
        {
            act == MINUS ? timer.riseMil-- : timer.riseMil++;
            if (timer.riseMil < 0)
                timer.riseMil = 255;
            if (timer.riseMil > 255)
                timer.riseMil = 0;
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

boolean Key::chekSet(Screen &screen)
{
    if (screen != lamp)
    {
        switch (screen)
        {
        case watch:
            setDateTime = true;
            screen = lamp;
            break;

        case duration:
            writeTime = true;
            reduration[id] = false;
            screen = lamp;
            break;

        case (maxBright || riseBright || setBright):
            writeBright = true;
            reBright[id] = false;
            screen = lamp;
            break;

        case dayDuration:
            writeDay = true;
            correctDay = true;
            screen = lamp;
            reDay = false;
            break;

        case manual:
            resetManualPot = true;
            resetManualBright = true;

            for (byte i = 0; i < lampAmount; i++)
                buttonSwitch[i] = 0;
            break;

        default:
            break;
        }

        if (this->screen != screen)
        {
            screen = lamp;
        }
        else
        {
            this->screen = screen;
        }

        return true;
    }
    else
    {
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
            reduration[id] = true;
        }
    }

    return reduration[id];
}

boolean Key::changeBright()
{
    if (justPressed() && getNum == 7)
    {
        autoMove = false;

        if (screen == maxBright || screen == riseBright || screen == setBright)
        {
            writeBright = true;
            reBright[id] = false;
            screen = lamp;
        }
        else
        {
            screen = maxBright;
            reBright[id] = true;
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

    return reBright[id];
}

boolean Key::dayReduration()
{
    if (justPressed() && getNum == 2)
    {
        autoMove = false;

        if (chekSet(dayDuration))
        {
        }
        else
        {
            screen = dayDuration;
            reDay = true;
        }
    }

    return reDay;
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

            autoMove = true;
            screen = lamp;
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
