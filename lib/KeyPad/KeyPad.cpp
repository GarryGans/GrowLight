#include <KeyPad.h>

KeyPad::KeyPad(byte rowPins[], byte colPins[], byte amount) : Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS)
{
    Amount = amount;

    idLast = Amount - 1;

    // buttonSwitch = new boolean[Amount];
    // reduration = new boolean[Amount];
    // reBright = new boolean[Amount];
}

KeyPad::~KeyPad()
{
}

void KeyPad::begin(unsigned long holdDelay, unsigned long holdSpeed)
{
    Adafruit_Keypad::begin();

    this->holdDelay = holdDelay;
    this->holdSpeed = holdSpeed;
}

boolean KeyPad::keyEvent()
{
    // tick();

    while (available())
    {
        keypadEvent e = read();

        Serial.println((char)e.bit.KEY);

        if (e.bit.EVENT == KEY_JUST_PRESSED)
        {
            // Serial.println(" press");
            press = true;
            prewDelay = millis();
            num = (char)e.bit.KEY;

            return true;
        }

        else if (e.bit.EVENT == KEY_JUST_RELEASED)
        {
            // Serial.println(" released");
            press = false;
            hold = false;
            // num = 'N';
            // Serial.println(num);

            return false;
        }
    }

    if (press && millis() - prewDelay >= holdDelay && millis() - prewSpeed >= holdSpeed)
    {
        hold = true;
        // Serial.println("hold");
        prewSpeed = millis();

        return true;
    }
    else
    {
        hold = false;

        return false;
    }

    return false;
}

void KeyPad::test()
{
    if (keyEvent())
    {
        if (num == 'A')
        {
            Serial.println("on hold");
        }
    }
}

void KeyPad::idChange()
{
    id++;

    if (id > idLast)
    {
        id = idFirst;
    }
}

void KeyPad::autoScreenMove(Timer &timer)
{
    if (screen == lamp)
    {
        if (autoMove && timer.wait(timer.prewScreenMillis, timer.displayMillis))
        {
            idChange();
        }
    }
}

boolean KeyPad::navigation()
{
    if (keyEvent())
    {
        if (num == '8')
        {
            direction = FORWARD;
            return true;
        }

        else if (num == 'C')
        {
            direction = BACK;
            return true;
        }
    }

    return false;
}

boolean KeyPad::valChange(Timer &timer)
{
    if (keyEvent())
    {
        if (num == '6')
        {
            timer.blinkHide = true;
            act = MINUS;

            return true;
        }

        else if (num == '#')
        {
            timer.blinkHide = true;
            act = PLUS;

            return true;
        }
    }

    timer.blinkHide = false;
    return false;
}

void KeyPad::manualChangeScreen(Timer &timer)
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

            timer.resetCounter(timer.unfrizeCounter);
        }

        if (!autoMove && screen != manual)
        {
            if (timer.unfrize(timer.unfrizeCounter))
            {
                autoMove = true;
            }
        }
    }
}

void KeyPad::reset()
{
    resetManualPot = true;
    resetManualBright = true;

    for (byte i = 0; i < Amount; i++)
    {
        buttonSwitch[i] = 0;
    }
}

void KeyPad::home()
{
    if (keyEvent() && num == 'A')
    {
        screen = start;
        Serial.println("start");
    }
}

void KeyPad::setMode()
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

    else if (screen == bright)
    {
        writeBright = true;
        correctBright = true;
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

void KeyPad::resetToLamp()
{
    setMode();
    screen = lamp;
}

boolean KeyPad::checkSet(Screen set)
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

boolean KeyPad::ok()
{
    if (keyEvent() && num == '9')
    {
        return true;
    }
    return false;
}

boolean KeyPad::setWatch()
{
    if ((keyEvent() && num == '3') || (screen == watch && ok()))
    {
        return checkSet(watch);
    }

    return false;
}

boolean KeyPad::spectrumReDuration()
{
    if (keyEvent() && num == '*')
    {
        return checkSet(duration);
    }
    else if (screen == duration && ok())
    {
        resetToLamp();
    }

    return false;
}

boolean KeyPad::changeMaxBright()
{
    if ((keyEvent() && num == '7') || (screen == bright && ok()))
    {
        return checkSet(bright);
    }

    return false;
}

boolean KeyPad::dayReduration()
{
    if (keyEvent() && num == '2')
    {
        return checkSet(dayDuration);
    }

    else if (screen == dayDuration && ok())
    {
        resetToLamp();
    }

    return false;
}

boolean KeyPad::skipEnable(boolean &skip, byte id)
{
    if (keyEvent() && num == '4')
    {
        checkSet(lamp);

        if (!skip)
        {
            skip = true;
        }
        else
        {
            skip = false;
        }
        return true;
    }

    return false;
}

void KeyPad::manualSwitchLight()
{
    if (keyEvent() && num == '1')
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