#include "Screen.h"
#include "Css.cpp"

// Screen::Screen(String WavelengthSMD[], String lightColor[]) : U8G2_SH1106_128X64_NONAME_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE)
Screen::Screen(String WavelengthSMD[], String lightColor[]) : U8G2_SSD1306_128X64_NONAME_1_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE)

{
    for (byte i = 0; i < lampAmount; i++)
    {
        this->WavelengthSMD[i] = WavelengthSMD[i];
        this->lightColor[i] = lightColor[i];
    }
}

Screen::~Screen()
{
}

void Screen::iGorLogo()
{
    firstPage();
    do
    {
        setHeight(u8g2_font_timB14_tf);
        textAlign("Smart Garden", PosX::center, PosY::up);
        textAlign("iGor_2019", PosX::center, PosY::center);

    } while (nextPage());
}

void Screen::brightInfo(Pot &pot, Key &key, Timer &timer)
{
    setHeight(u8g2_font_courB08_tn);

    digAlign(pot.bright[key.id], PosX::rightHalf, PosY::downSpace);
}

void Screen::brightInfo(Bright &bright, Key &key, Timer &timer)
{
    setHeight(u8g2_font_pressstart2p_8f);

    digAlign(bright.bright[key.id], PosX::rightHalf, PosY::downSpace);
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot)
{
    if (watch.skip[key.id] && key.screen != key.manual)
    {
        setHeight(u8g2_font_pixelmordred_tf);
        textAlign("SKIP", PosX::center, PosY::downSpace);
    }

    else if (key.screen == key.manual)
    {
        setHeight(u8g2_font_pressstart2p_8f);
        textAlign("MANUAL", PosX::leftHalf, PosY::downSpace);

        brightInfo(pot, key, timer);
    }

    else
    {
        setHeight(u8g2_font_courB08_tn);
        setPosition("00:00-00:00", PosX::leftSpace, PosY::downSpace);

        showSpectrumTime(watch, key.id);
        brightInfo(pot, key, timer);
    }
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright)
{
    if (watch.skip[key.id] && key.screen != key.manual)
    {
        setHeight(u8g2_font_pressstart2p_8f);
        textAlign("SKIP", PosX::center, PosY::downSpace);
    }

    else if (key.screen == key.manual)
    {
        setHeight(u8g2_font_pixelmordred_tf);

        textAlign("manual", PosX::leftHalf, PosY::downSpace);
        brightInfo(bright, key, timer);
    }

    else
    {
        setHeight(u8g2_font_courB08_tn);
        setPosition("00:00-00:00", PosX::leftSpace, PosY::downSpace);

        showSpectrumTime(watch, key.id);
        brightInfo(bright, key, timer);
    }
}

void Screen::lampInfo(Watch &watch, Key &key)
{
    setHeight(u8g2_font_courB08_tf);

    stringAlign(WavelengthSMD[key.id], 21, PosX::left, PosY::upHalf);

    setHeight(u8g2_font_courB18_tr);

    stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

    stringAlign(state[watch.autoSwitch[key.id] || key.buttonSwitch[key.id]], 4, PosX::rightHalf, PosY::center);
}

void Screen::headerTime(Watch &watch)
{
    setHeight(u8g2_font_courB08_tn);

    setPosition("00:00:00", PosX::rightSpace, PosY::upSpace);

    Time now = watch.time();

    showStringWatch(now.hour(), now.minute(), now.second());
}

void Screen::headerDate(Watch &watch)
{
    setHeight(u8g2_font_courB08_tf);

    setPosition("00/00/0000", PosX::leftHalf, PosY::upSpace);

    Date now = watch.date();

    showStringDate(now.day(), now.month(), now.year());

    // setY = 16;
    textAlign(daysOfTheWeek[now.dayOfTheWeek()], PosX::leftHalf, PosY::upHalf);
}

void Screen::showBrightScreen(Pot &pot, Key &key, Timer &timer)
{
    if (key.screen == key.bright)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            textAlign("Max Bright", PosX::center, PosY::upSpace);

            setHeight(u8g2_font_courB18_tr);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            digAlign(pot.maxBright[key.id], PosX::rightHalf, PosY::center);

            if (timer.blinkReady())
            {
                frameAlign(getDigWidth(pot.maxBright[key.id]), getMaxCharWidth(), PosX::rightHalf, PosY::centerFrame);
            }
        } while (nextPage());
    }
}

void Screen::showBrightScreen(Bright &bright, Key &key, Timer &timer)
{
    if (key.screen == key.bright)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            textAlign("Max Bright", PosX::center, PosY::upSpace);

            setHeight(u8g2_font_courB18_tr);

            stringAlign(lightColor[key.id], 4, PosX::leftHalf, PosY::center);

            digAlign(bright.maxBright[key.id], PosX::rightHalf, PosY::center);

            blinkFrame(bright.maxBright[key.id], PosX::rightHalf, PosY::centerFrame, timer);

        } while (nextPage());
    }
}

void Screen::timerScreen(Watch &watch, Timer &timer, Key &key)
{
    if (key.screen == key.duration)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_courB08_tn);

            textAlign("Set Spectrum Time", PosX::center, PosY::upSpace);

            setHeight(u8g2_font_courB08_tn);

            setPosition("00:00", PosX::center, PosY::upHalf);

            showStringTime(watch.startHour[key.id], watch.startMinute[key.id]);

            setPosition("00:00", PosX::center, PosY::downSpace);

            showStringTime(watch.finishHour[key.id], watch.finishMinute[key.id]);

            switch (watch.cursorSpectrum)
            {
            case 0:
                // blinkFrame(watch.startHour[key.id], x, 57, timer);
                break;

            case 1:
                // blinkFrame(watch.startMinute[key.id], nextX(watch.startHour[key.id], 5, ":"), 57, timer);
                break;

            case 2:
                // blinkFrame(watch.finishHour[key.id], 5 + getStrWidth("00:00-"), 57, timer);
                break;

            case 3:
                // blinkFrame(watch.finishMinute[key.id], 5 + getStrWidth("00:00-00:"), 57, timer);
                break;

            default:
                break;
            }

        } while (nextPage());
    }
}

void Screen::lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot)
{
    if (key.screen == key.lamp || key.screen == key.manual)
    {
        firstPage();
        do
        {
            headerTime(watch);
            lampInfo(watch, key);
            bottomLine(watch, timer, key, pot);
        } while (nextPage());
    }
}

void Screen::lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright)
{
    if (key.screen == key.lamp || key.screen == key.manual)
    {
        firstPage();
        do
        {
            headerTime(watch);
            lampInfo(watch, key);
            bottomLine(watch, timer, key, bright);
        } while (nextPage());
    }
}

void Screen::showDig(byte value)
{
    if (value < 10)
    {
        print("0");
    }

    print(value);
}

void Screen::showStringTime(byte hh, byte mm)
{
    showDig(hh);

    print(":");

    showDig(mm);
}

void Screen::showStringWatch(byte hh, byte mm, byte ss)
{
    showDig(hh);

    print(":");

    showDig(mm);

    print(":");

    showDig(ss);
}

void Screen::showStringDate(byte day, byte month, int year)
{
    showDig(day);

    print("/");

    showDig(month);

    print("/");

    print(year);
}

void Screen::showSpectrumTime(Watch &watch, byte id)
{
    showStringTime(watch.startHour[id], watch.startMinute[id]);

    print("-");

    showStringTime(watch.finishHour[id], watch.finishMinute[id]);
}

void Screen::blinkFrameYear(int year, byte x, byte y, Timer &timer)
{
    char val[5];
    String(year).toCharArray(val, 5);

    if (timer.blinkReady())
    {
        drawFrame(x, y, getStrWidth(val) + 3, getMaxCharWidth());
    }
}

void Screen::blinkHeaderTime(Key &key, Watch &watch, Timer &timer)
{
    setHeight(u8g2_font_courB08_tn);

    setPosition("00:00:00", PosX::center, PosY::downHalf);

    showStringWatch(watch.hour, watch.min, watch.sec);

    switch (watch.cursorDateTime)
    {
    case 3:
        // blinkFrame(watch.hour, 74, 0, timer);
        break;

    case 4:
        // blinkFrame(watch.min, 74 + getStrWidth("00:"), 0, timer);
        break;

    case 5:
        // blinkFrame(watch.sec, 74 + getStrWidth("00:00:"), 0, timer);
        break;

    default:
        break;
    }
}

void Screen::blinkHeaderDate(Key &key, Watch &watch, Timer &timer)
{
    setHeight(u8g2_font_courB08_tf);

    setPosition("00/00/0000", PosX::center, PosY::upHalf);

    showStringDate(watch.day, watch.month, watch.year);

    // textAlign(daysOfTheWeek[now.dayOfTheWeek()], PosX::center, PosY::center);

    switch (watch.cursorDateTime)
    {
    case 0:
        // blinkFrame(watch.day, 0, 0, timer);
        break;

    case 1:
        // blinkFrame(watch.month, getStrWidth("00/"), 0, timer);
        break;

    case 2:
        // blinkFrameYear(watch.year, getStrWidth("00/00/"), 0, timer);
        break;

    default:
        break;
    }
}

void Screen::setWatchScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.watch)
    {
        firstPage();
        do
        {
            blinkHeaderDate(key, watch, timer);
            blinkHeaderTime(key, watch, timer);

        } while (nextPage());

        // if (timer.unfrize())
        // {
        //     key.setDateTime = true;
        //     key.screen = key.lamp;
        //     key.autoMove = true;
        // }
    }
}

void Screen::showSunTime(Watch &watch)
{
    setHeight(u8g2_font_9x18_tn);

    setPosition("00:00", PosX::rightSpace, PosY::center);
    showStringTime(watch.RiseHour, watch.RiseMin);

    setPosition("00:00", PosX::rightSpace, PosY::downSpace);
    showStringTime(watch.SetHour, watch.SetMin);
}

void Screen::blinkSunTime(Key &key, Timer &timer, Watch &watch)
{
    setHeight(u8g2_font_profont22_tn);

    setPosition("00:00", PosX::center, PosY::center);
    showStringTime(watch.RiseHour, watch.RiseMin);
    setPosition("00:00", PosX::center, PosY::downSpace);
    showStringTime(watch.SetHour, watch.SetMin);

    switch (watch.cursorDay)
    {
    case 0:
        setPosition("00:00", PosX::center, PosY::center);
        break;

    case 1:
        setPosition("00:00", PosX::center, PosY::centerFrame);
        break;

    case 2:
        setPosition("00:00", PosX::center, PosY::downSpace);
        break;

    case 3:
        // blinkFrame(watch.SetMin, 60 + getStrWidth("00:"), 52, timer);
        break;

    default:
        break;
    }

    blinkFrame(x, y, timer);
}

void Screen::sunTimeScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.dayDuration)
    {
        firstPage();
        do
        {
            setHeight(u8g2_font_pressstart2p_8f);

            setPosition("Set SunTime", PosX::center, PosY::upSpace);
            moveString(timer, x, y, "Set SunTime");
            blinkSunTime(key, timer, watch);
        } while (nextPage());

        // if (timer.unfrize())
        // {
        //     key.writeDay = true;
        //     key.correctDay = true;
        //     key.screen = key.lamp;
        //     key.autoMove = true;
        // }
    }
}

void Screen::startScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.start)
    {
        firstPage();
        do
        {
            headerDate(watch);
            headerTime(watch);

            showSunTime(watch);

        } while (nextPage());

        if (timer.unfrize())
        {
            key.screen = key.lamp;
            key.autoMove = true;
        }
    }
}

void Screen::screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot)
{
    startScreen(watch, key, timer);
    lampScreen(watch, switchers, timer, key, pot);
    setWatchScreen(watch, key, timer);
    sunTimeScreen(watch, key, timer);
    timerScreen(watch, timer, key);
    showBrightScreen(pot, key, timer);
}

void Screen::screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright)
{
    startScreen(watch, key, timer);
    lampScreen(watch, switchers, timer, key, bright);
    setWatchScreen(watch, key, timer);
    sunTimeScreen(watch, key, timer);
    timerScreen(watch, timer, key);
    showBrightScreen(bright, key, timer);
}
