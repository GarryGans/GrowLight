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

boolean Key::autoOk(Screen screen, Timer &timer)
{
    if (this->screen == screen)
    {
        if (timer.ready(5, reset))
        {
            return true;
        }
    }

    return false;
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
        if (autoMove && timer.ready(5, navigation()))
        {
            idChange();
        }

        if (!autoMove && timer.ready(5, navigation()))
        {
            autoMove = true;
        }
    }
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
            reset = true;

            return true;
        }

        else if (getNum == 15)
        {
            act = PLUS;
            reset = true;

            return true;
        }
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

boolean Key::chekSet(Screen screen)
{
    if (this->screen != lamp)
    {
        switch (this->screen)
        {
        case watch:
            setDateTime = true;
            break;

        case duration:
            writeTime = true;
            reduration[id] = false;
            break;

        case maxBright:
            writeBright = true;
            reBright[id] = false;
            break;

        case riseBright:
            writeBright = true;
            reBright[id] = false;
            break;

        case setBright:
            writeBright = true;
            reBright[id] = false;
            break;

        case dayDuration:
            writeDay = true;
            correctDay = true;
            reDay = false;
            break;

        case manual:
            resetManualPot = true;
            resetManualBright = true;

            for (byte i = 0; i < lampAmount; i++)
                buttonSwitch[i] = 0;
            break;

        case interval:
            writeSpeed = true;
            writeInterval = true;
            break;

        case speed:
            writeSpeed = true;
            writeInterval = true;
            break;

        default:
            break;
        }

        if (this->screen != screen)
            return false;

        return true;
    }

    return false;
}

void Key::setSpeed(Timer &timer)
{
    if ((justPressed() && getNum == 10) || autoOk(speed, timer) || autoOk(interval, timer))
    {
        autoMove = false;

        if (chekSet(speed) || chekSet(interval))
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
        menuScreen(speed, interval);
    }

    if (screen == speed)
    {
        if (valChange())
        {
            act == MINUS ? timer.rise-- : timer.rise++;
            if (timer.rise < 0)
                timer.rise = 255;
            if (timer.rise > 255)
                timer.rise = 0;
        }
    }
}

boolean Key::setWatch(Timer &timer)
{
    if ((justPressed() && getNum == 3) || autoOk(watch, timer))
    {
        autoMove = false;

        if (chekSet(watch))
        {
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

boolean Key::spectrumReDuration(Timer &timer)
{
    if ((justPressed() && getNum == 14) || autoOk(duration, timer))
    {
        autoMove = false;

        if (chekSet(duration))
        {
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

boolean Key::changeBright(Timer &timer)
{
    if ((justPressed() && getNum == 7) || (autoOk(maxBright, timer)) || (autoOk(riseBright, timer)) || (autoOk(setBright, timer)))
    {
        autoMove = false;

        if (chekSet(maxBright) || chekSet(riseBright) || chekSet(setBright))
        {
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

boolean Key::dayReduration(Timer &timer)
{
    if ((justPressed() && getNum == 2) || autoOk(dayDuration, timer))
    {
        reset = true;
        autoMove = false;

        if (chekSet(dayDuration))
        {
            screen = lamp;
        }
        else
        {
            reset = true;
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
        reset = true;
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
        if (chekSet(manual))
        {
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

boolean Key::allBrigh(Timer &timer)
{
    if (valChange())
    {
        if (screen == lamp)
        {
            screen = bright;
        }

        return true;
    }

    else if (autoOk(bright, timer) && !reset)
    {
        writeAllBright = true;
        screen = lamp;
    }
    else
    {
        reset = false;
    }

    return false;
}
