#include "Screen.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Screen::Screen() : Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
}

Screen::~Screen()
{
}

void Screen::begin()
{
    Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void Screen::setStrings(String *WavelengthSMD, String *lightColor)
{
    for (byte i = 0; i < lampAmount; i++)
    {
        this->WavelengthSMD[i] = WavelengthSMD[i];
        this->lightColor[i] = lightColor[i];
    }
}

void Screen::iGorLogo()
{
    clearDisplay();

    setTextColor(1);
    setTextSize(1);

    setCursor(65, 20);
    print("Grow Light");
    setCursor(70, 30);
    print("Control");
    setCursor(65, 40);
    print("iGor_2019");

    display();
}

void Screen::headerTime(Watch &watch)
{
    Time now = watch.time();

    setCursor(79, 2);
    showStringWatch(now.hour(), now.minute(), now.second());
}

void Screen::headerDate(Watch &watch)
{
    Date now = watch.date();

    setCursor(0, 0);
    print(daysOfTheWeek[now.dayOfTheWeek()]);

    setCursor(2, 10);
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

void Screen::showAlert()
{
    print("manual");
}

void Screen::brightInfo(Pot &pot, Key &key, Timer &timer)
{
    setTextSize(1);
    setCursor(80, 54);
    print(pot.bright[key.id]);
    if (key.screen != key.manual)
    {
        print("/");
        if (key.screen == key.bright)
        {
            showBlink(90, 52, timer);
            print(pot.maxBright[key.id]);
        }
        else
        {
            print(pot.maxBright[key.id]);
        }
    }
}

void Screen::brightInfo(Bright &bright, Key &key, Timer &timer)
{
    setTextSize(1);
    setCursor(80, 54);
    print(bright.bright[key.id]);
    if (key.screen != key.manual)
    {
        print("/");
        if (key.screen == key.bright)
        {
            showBlink(90, 52, timer);
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
        setTextSize(2);
        setCursor(25, 50);
        print("SKIP");
    }

    else if (key.screen == key.manual)
    {
        setTextSize(2);
        setCursor(0, 50);
        showAlert();
        brightInfo(pot, key, timer);
    }

    else
    {
        showBlinkSpectrumTime(watch, timer, key);

        brightInfo(pot, key, timer);
    }
}

void Screen::bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright)
{
    if (watch.skip[key.id] && key.screen != key.manual && key.screen != key.bright && key.screen != key.duration)
    {
        setTextSize(2);
        setCursor(25, 50);
        print("SKIP");
    }

    else if (key.screen == key.manual)
    {
        setTextSize(2);
        setCursor(0, 50);
        showAlert();
        brightInfo(bright, key, timer);
    }

    else
    {
        showBlinkSpectrumTime(watch, timer, key);

        brightInfo(bright, key, timer);
    }
}

void Screen::showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot)
{
    if (key.screen == key.lamp || key.screen == key.bright || key.screen == key.duration || key.screen == key.manual)
    {
        setTextColor(1);

        clearDisplay();
        headerTime(watch);
        lampInfo(watch, key);
        bottomLine(watch, timer, key, pot);
        display();
    }
}

void Screen::showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright)
{
    if (key.screen == key.lamp || key.screen == key.bright || key.screen == key.duration || key.screen == key.manual)
    {
        setTextColor(1);

        clearDisplay();
        headerTime(watch);
        lampInfo(watch, key);
        bottomLine(watch, timer, key, bright);
        display();
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

void Screen::showBlinkBig(byte x, byte y, Timer &timer)
{
    if (timer.blinkReady())
    {
        drawRect(x, y, 32, 24, SSD1306_WHITE);
    }
}

void Screen::showBlink(byte x, byte y, Timer &timer)
{
    if (timer.blinkReady())
    {
        drawRect(x, y, 16, 12, SSD1306_WHITE);
    }
}

void Screen::showBlinkYear(byte x, byte y, Timer &timer)
{
    if (timer.blinkReady())
    {
        drawRect(x, y, 32, 12, SSD1306_WHITE);
    }
}

void Screen::showBlinkSpectrumTime(Watch &watch, Timer &timer, Key &key)
{
    setTextSize(1);
    setCursor(5, 54);

    if (key.screen == key.duration)
    {
        switch (watch.cursorSpectrum)
        {
        case 0:
            showBlink(3, 52, timer);
            break;

        case 1:
            showBlink(21, 52, timer);
            break;

        case 2:
            showBlink(40, 52, timer);
            break;

        case 3:
            showBlink(56, 52, timer);
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

void Screen::lampInfo(Watch &watch, Key &key)
{
    setCursor(0, 9);
    setTextSize(1);
    print(WavelengthSMD[key.id]);

    setCursor(0, 24);
    setTextSize(3);

    print(lightColor[key.id]);

    setCursor(74, 24);

    if (watch.autoSwitch[key.id] || key.buttonSwitch[key.id])
    {
        print("ON");
    }
    else
    {
        print("OFF");
    }
}

void Screen::showBlinkSunRise(Key &key, Timer &timer, Watch &watch, byte hh, byte mm)
{
    setCursor(5, 30);
    setTextSize(1);
    print("Sun Rise:");
    setTextSize(2);
    setCursor(60, 24);
    if (key.screen == key.dayDuration)
    {
        switch (watch.cursorDay)
        {
        case 0:
            showBlinkBig(56, 20, timer);
            break;

        case 1:
            showBlinkBig(91, 20, timer);
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
    setTextSize(1);
    print("Sun Set:");
    setTextSize(2);
    setCursor(60, 46);

    if (key.screen == key.dayDuration)
    {
        switch (watch.cursorDay)
        {
        case 2:
            showBlinkBig(56, 40, timer);
            break;

        case 3:
            showBlinkBig(91, 40, timer);
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
        setCursor(79, 2);
        setTextSize(1);

        switch (watch.cursorDateTime)
        {
        case 3:
            showBlink(76, 0, timer);
            break;
        case 4:
            showBlink(94, 0, timer);
            break;
        case 5:
            showBlink(112, 0, timer);
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
        setTextSize(1);

        setCursor(0, 0);
        print(daysOfTheWeek[watch.dow]);

        setCursor(2, 10);

        switch (watch.cursorDateTime)
        {
        case 0:
            showBlink(0, 8, timer);
            break;

        case 1:
            showBlink(18, 8, timer);
            break;
        case 2:
            showBlinkYear(32, 8, timer);
            break;

        default:
            break;
        }

        showDig(watch.day);
        print('/');
        showDig(watch.month);
        print('/');
        print(watch.year);
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
        clearDisplay();

        setTextColor(1);

        blinkHeaderDate(key, watch, timer);
        // blinkHeaderTime(key, watch, timer);

        showBlinkSunRise(key, timer, watch, watch.RiseHour, watch.RiseMin);
        showBlinkSunSet(key, timer, watch, watch.SetHour, watch.SetMin);

        display();

        if (key.screen == key.dayDuration || key.screen == key.watch)
        {
            timer.resetCounter(timer.escapeCounter);
        }

        else if (timer.unfrize(timer.escapeCounter) && key.screen == key.start)
        {
            key.screen = key.lamp;
            key.autoMove = true;
            // Serial.println("unfrize");
        }
        // Serial.println("start");
    }
}
