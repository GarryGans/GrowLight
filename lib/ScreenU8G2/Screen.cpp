#include "Screen.h"

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

void Screen::align(byte W, byte H, PositionX position_x, PositionY position_y)
{
    switch (position_x)
    {
    case centerX:
        x = (screenWidth - W) / 2;
        break;

    case left:
        x = (screenWidth / 2 - W) / 2;
        break;

    case right:
        x = (screenWidth + screenWidth / 2 - W) / 2;
        break;

    case customX:
        x = setX;
        break;

    default:
        break;
    }

    switch (position_y)
    {
    case centerY:
        y = (screenHeight + H) / 2;
        break;

    case up:
        y = (screenHeight / 2 - H) / 2 + H;
        break;

    case down:
        y = (screenHeight + screenHeight / 2 - H) / 2 + H;
        break;

    case upFrame:
        y = (screenHeight / 2 - H) / 2;
        break;

    case downFrame:
        y = (screenHeight + screenHeight / 2 - H) / 2;
        break;

    case centerFrame:
        y = (screenHeight - H) / 2;
        break;

    case customY:
        y = setY;
        break;

    default:
        break;
    }
}

void Screen::textAlign(const char *string, PositionX position_x, PositionY position_y)
{
    align(getStrWidth(string), getMaxCharWidth(), position_x, position_y);
    setCursor(x, y);
    print(string);
}

void Screen::mover(byte deep_x)
{
    if (move_x > (start_x - deep_x) && moveLeft)
    {
        move_x--;
        if (move_x == start_x - deep_x)
        {
            moveLeft = false;
            moveRight = true;
        }
    }
    else if (move_x < (deep_x + start_x) && moveRight)
    {
        move_x++;
        if (move_x == deep_x + start_x)
        {
            moveRight = false;
            moveLeft = true;
        }
    }
}

void Screen::moveString(Timer &timer, byte deep_x, byte bottom_y, const char *string)
{
    if (!move)
    {
        move_x = (screenWidth - getStrWidth(string)) / 2;
        move = true;
        moveLeft = true;
        moveRight = false;
    }

    setCursor(move_x, bottom_y);
    print(string);

    if (timer.moveReady())
    {
        start_x = (screenWidth - getStrWidth(string)) / 2;
        deep_x = constrain(deep_x, 0, start_x);
        mover(deep_x);
    }
}

void Screen::digAlign(byte dig, const char *string, PositionX position_x, PositionY position_y)
{
    if (dig > 9 && dig < 100)
    {
        digWidth = getStrWidth("W") * 2;
    }
    else
    {
        digWidth = getStrWidth("W");
    }

    if (string != 0)
    {
        digWidth += getStrWidth(string);
    }

    align(digWidth, getMaxCharWidth(), position_x, position_y);
    setCursor(x, y);

    print(dig);
    if (string != 0)
    {
        print(string);
    }
}

void Screen::frameAlign(byte W, byte H, PositionX position_x, PositionY position_y)
{
    align(W, H, position_x, position_y);
    drawFrame(x, y, W, H);
}

void Screen::escapeBar(Timer &timer)
{
    if (!timer.escBar)
    {
        blockWidth = screenWidth / timer.maxEscapeCounter;
        timer.escBar = true;
    }

    width = blockWidth * (timer.maxEscapeCounter - timer.escapeCounter);
    drawBox(0, 58, width, 6);

    if (width == blockWidth * timer.maxEscapeCounter)
    {
        timer.escBar = false;
    }
}

void Screen::iconAlign(int icon, byte iconWH, PositionX position_x, PositionY position_y)
{
    align(iconWH, iconWH, position_x, position_y);
    drawGlyph(x, y, icon);
}

void Screen::iGorLogo()
{
    firstPage();
    do
    {
        setFont(u8g2_font_timB14_tf);
        textAlign("Smart Garden", centerX, up);
        textAlign("iGor_2019", centerX, centerY);

    } while (nextPage());
}

byte Screen::getWidth(byte value)
{
    char val[4];
    String(value).toCharArray(val, 4);

    return getStrWidth(val);
}

void Screen::showBlink(byte value, byte x, byte y, Timer &timer)
{
    if (timer.blinkReady())
    {
        drawFrame(x, y - 2, getWidth(value) + 4, getMaxCharHeight() + 4);
    }
}

void Screen::brightInfo(Pot &pot, Key &key, Timer &timer)
{
    setFont(u8g2_font_courB08_tn);

    setCursor(80, 57);
    print(pot.bright[key.id]);
    if (key.screen != key.manual)
    {
        print("/");
        if (key.screen == key.bright)
        {

            print(pot.maxBright[key.id]);
        }
        else
        {
            print(pot.maxBright[key.id]);
        }
    }
}

byte Screen::nextX(byte prewX, byte value,  char simbol[] = 0)
{
    return (prewX + getWidth(value) + getStrWidth(simbol));
}

void Screen::brightInfo(Bright &bright, Key &key, Timer &timer)
{
    setFont(u8g2_font_courB08_tn);

    setCursor(80, 57);
    print(bright.bright[key.id]);
    if (key.screen != key.manual)
    {
        print("/");

        if (key.screen == key.bright)
        {
            showBlink(bright.maxBright[key.id], nextX(80, bright.bright[key.id], "/"), 57 - 8, timer);

            print(bright.maxBright[key.id]);
        }
        else
        {
            print(bright.maxBright[key.id]);
        }
    }
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot)
{
    if (watch.skip[key.id] && key.screen != key.manual && key.screen != key.bright && key.screen != key.duration)
    {
        setFont(u8g2_font_pressstart2p_8f);
        textAlign("SKIP", centerX, down);
    }

    else if (key.screen == key.manual)
    {
        setFont(u8g2_font_pixelmordred_tf);

        textAlign("manual", left, down);
        brightInfo(pot, key, timer);
    }

    else
    {
        setFont(u8g2_font_courB08_tn);

        setCursor(5, 57);

        showBlinkSpectrumTime(watch, timer, key);

        brightInfo(pot, key, timer);
    }
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright)
{
    if (watch.skip[key.id] && key.screen != key.manual && key.screen != key.bright && key.screen != key.duration)
    {
        setFont(u8g2_font_pressstart2p_8f);
        textAlign("SKIP", centerX, down);
    }

    else if (key.screen == key.manual)
    {
        setFont(u8g2_font_pixelmordred_tf);
        textAlign("manual", left, down);

        brightInfo(bright, key, timer);
    }

    else
    {
        setFont(u8g2_font_courB08_tn);

        setCursor(5, 57);

        showBlinkSpectrumTime(watch, timer, key);

        brightInfo(bright, key, timer);
    }
}

void Screen::lampInfo(Watch &watch, Key &key)
{
    setCursor(0, 16);
    setFont(u8g2_font_courB08_tf);

    print(WavelengthSMD[key.id]);

    setFont(u8g2_font_courB18_tr);
    setCursor(5, 38);

    print(lightColor[key.id]);

    setCursor(74, 38);

    if (watch.autoSwitch[key.id] || key.buttonSwitch[key.id])
    {
        print("ON");
    }
    else
    {
        print("OFF");
    }
}

void Screen::headerTime(Watch &watch)
{
    Time now = watch.time();

    setFont(u8g2_font_courB08_tn);

    setCursor(74, 8);
    showStringWatch(now.hour(), now.minute(), now.second());
}

void Screen::headerDate(Watch &watch)
{
    Date now = watch.date();

    setFont(u8g2_font_courB08_tf);

    setY = 16;
    textAlign(daysOfTheWeek[now.dayOfTheWeek()], left, customY);

    setCursor(0, 8);
    showDig(now.day());
    print('/');
    showDig(now.month());
    print('/');
    print(now.year());
}

void Screen::headerScreen(Watch &watch)
{
    headerDate(watch);
    headerTime(watch);
}

void Screen::showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot)
{
    if (key.screen == key.lamp || key.screen == key.bright || key.screen == key.duration || key.screen == key.manual)
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

void Screen::showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright)
{
    if (key.screen == key.lamp || key.screen == key.bright || key.screen == key.duration || key.screen == key.manual)
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

void Screen::showDig(byte value)
{
    if (value < 10)
    {
        print("0");
    }
    print(value);
}

void Screen::showBlinkYear(int year, byte x, byte y, Timer &timer)
{
    char val[5];
    String str = String(year);
    str.toCharArray(val, 5);

    if (timer.blinkReady())
    {
        drawFrame(x, y, getStrWidth(val) + 3, getMaxCharHeight());
    }
}

void Screen::showBlinkSpectrumTime(Watch &watch, Timer &timer, Key &key)
{
    if (key.screen == key.duration)
    {
        setFont(u8g2_font_courB08_tn);

        setCursor(5, 57);

        switch (watch.cursorSpectrum)
        {
        case 0:
            showBlink(watch.startHour[key.id], 5, 57 - 8, timer);
            break;

        case 1:
            showBlink(watch.startMinute[key.id], 5 + getStrWidth("00:"), 57 - 8, timer);

            break;

        case 2:
            showBlink(watch.finishHour[key.id], 5 + getStrWidth("00:00-"), 57 - 8, timer);
            break;

        case 3:
            showBlink(watch.finishMinute[key.id], 5 + getStrWidth("00:00-00:"), 57 - 8, timer);
            break;

        default:
            break;
        }

        showSpectrumTime(watch, key.id);
    }
    else
    {
        showSpectrumTime(watch, key.id);
    }
}

void Screen::showBlinkSunRise(Key &key, Timer &timer, Watch &watch, byte hh, byte mm)
{
    setCursor(5, 30);
    setFont(u8g2_font_courB08_tf);

    print("Sun Rise:");

    setFont(u8g2_font_pressstart2p_8f);

    setCursor(60, 30);

    if (key.screen == key.dayDuration)
    {
        switch (watch.cursorDay)
        {
        case 0:
            showBlink(hh, 60, 30 - 8, timer);
            break;

        case 1:
            showBlink(mm, 60 + getStrWidth("00:"), 30 - 8, timer);
            break;

        default:
            break;
        }
        showStringTime(hh, mm);
    }
    else
    {
        showStringTime(hh, mm);
    }
}

void Screen::showBlinkSunSet(Key &key, Timer &timer, Watch &watch, byte hh, byte mm)
{
    setCursor(5, 52);
    setFont(u8g2_font_courB08_tf);
    print("Sun Set:");

    setFont(u8g2_font_pressstart2p_8f);

    setCursor(60, 52);

    if (key.screen == key.dayDuration)
    {
        switch (watch.cursorDay)
        {
        case 2:
            showBlink(hh, 60, 52 - 8, timer);
            break;

        case 3:
            showBlink(mm, 60 + getStrWidth("00:"), 52 - 8, timer);
            break;

        default:
            break;
        }

        showStringTime(hh, mm);
    }
    else
    {
        showStringTime(hh, mm);
    }
}

void Screen::blinkHeaderTime(Key &key, Watch &watch, Timer &timer)
{
    if (key.screen == key.watch)
    {
        setFont(u8g2_font_courB08_tn);

        setCursor(74, 8);

        switch (watch.cursorDateTime)
        {
        case 3:
            showBlink(watch.hour, 74, 0, timer);
            break;

        case 4:
            showBlink(watch.min, 74 + getStrWidth("00:"), 0, timer);
            break;

        case 5:
            showBlink(watch.sec, 74 + getStrWidth("00:00:"), 0, timer);
            break;

        default:
            break;
        }

        showStringWatch(watch.hour, watch.min, watch.sec);
    }

    else
    {
        headerTime(watch);
    }
}

void Screen::blinkHeaderDate(Key &key, Watch &watch, Timer &timer)
{
    if (key.screen == key.watch)
    {
        setFont(u8g2_font_courB08_tf);

        setCursor(0, 9);

        switch (watch.cursorDateTime)
        {
        case 0:
            showBlink(watch.day, 0, 0, timer);
            break;

        case 1:
            showBlink(watch.month, getStrWidth("00/"), 0, timer);
            break;

        case 2:
            showBlinkYear(watch.year, getStrWidth("00/00/"), 0, timer);
            break;

        default:
            break;
        }

        showStringDate(watch.day, watch.month, watch.year);
    }
    else
    {
        headerDate(watch);
    }
}

void Screen::showStartScreen(Watch &watch, Key &key, Timer &timer)
{
    if (key.screen == key.start || key.screen == key.watch || key.screen == key.dayDuration)
    {
        firstPage();
        do
        {
            blinkHeaderDate(key, watch, timer);
            blinkHeaderTime(key, watch, timer);

            showBlinkSunRise(key, timer, watch, watch.RiseHour, watch.RiseMin);
            showBlinkSunSet(key, timer, watch, watch.SetHour, watch.SetMin);

        } while (nextPage());

        if (key.screen == key.dayDuration || key.screen == key.watch)
        {
            timer.resetCounter();
        }

        else if (timer.unfrize() && key.screen == key.start)
        {
            key.screen = key.lamp;
            key.autoMove = true;
        }
    }
}
