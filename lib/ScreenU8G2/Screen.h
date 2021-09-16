#ifndef SCREEN_H
#define SCREEN_H

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include <Watch.h>
#include <Switchers.h>
#include <Timer.h>
#include <Key.h>
#include <Pot.h>
#include <Bright.h>
#include <EFX.h>

// class Screen : public U8G2_SH1106_128X64_NONAME_1_HW_I2C
class Screen : public EFX

{
private:
    String WavelengthSMD[lampAmount];
    String lightColor[lampAmount];
    const char *state[2] = {"OFF", "ON"};
    // const char *advise[2] = {"Set SunTime", "Set MaxBright"};

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

public:
    Screen(String WavelengthSMD[], String lightColor[]);
    ~Screen();

    void iGorLogo();

    void showDig(byte value);

    void headerTime(Watch &watch);
    void headerDate(Watch &watch);

    void showStringTime(byte hh, byte mm);
    void showStringWatch(byte hh, byte mm, byte ss);
    void showStringDate(byte day, byte month, int year);
    void showSpectrumTime(Watch &watch, byte id);

    void brightInfo(Pot &pot, Key &key, Timer &timer);
    void brightInfo(Bright &bright, Key &key, Timer &timer);

    void bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot);
    void bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright);

    void lampInfo(Watch &watch, Key &key, Timer &timer);

    void blinkHeaderDate(Key &key, Watch &watch, Timer &timer);
    void blinkHeaderTime(Key &key, Watch &watch, Timer &timer);

    void showSunTime(Watch &watch);

    void blinkSunTime(Key &key, Timer &timer, Watch &watch);

    void timerScreen(Watch &watch, Timer &timer, Key &key);

    void lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot);
    void lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright);

    void setWatchScreen(Watch &watch, Key &key, Timer &timer);

    void sunTimeScreen(Watch &watch, Key &key, Timer &timer);

    void showBrightScreen(Pot &pot, Key &key, Timer &timer);
    void showBrightScreen(Bright &bright, Key &key, Timer &timer);

    void startScreen(Watch &watch, Key &key, Timer &timer);

    void screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot);
    void screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright);
};

#endif