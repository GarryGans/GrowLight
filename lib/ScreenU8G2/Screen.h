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

    void printDig(byte value);
    void printTime(byte hh, byte mm);
    void printWatch(byte hh, byte mm, byte ss);
    void printDate(byte day, byte month, int year);
    void printSpecTime(Watch &watch, byte id);

    void iGorLogo();

    void headerTime(Watch &watch);
    void headerDate(Watch &watch);

    void brightInfo(Pot &pot, Key &key, Timer &timer);
    void brightInfo(Bright &bright, Key &key, Timer &timer);

    void bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot);
    void bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright);

    void lampInfo(Watch &watch, Key &key, Timer &timer);

    void blinkDate(Key &key, Watch &watch, Timer &timer);
    void blinkTime(Key &key, Watch &watch, Timer &timer);

    void showSunTime(Watch &watch);

    void blinkSunTime(Key &key, Timer &timer, Watch &watch);

    void timerScreen(Watch &watch, Timer &timer, Key &key);

    void lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot);
    void lampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright);

    void setWatchScreen(Watch &watch, Key &key, Timer &timer);

    void sunTimeScreen(Watch &watch, Key &key, Timer &timer);

    void intervalScreen(Watch &watch, Key &key, Timer &timer);
    void riseSpeedScreen(Key &key, Timer &timer);

    void brightScreen(Pot &pot, Key &key, Timer &timer);

    void setScreen(Bright &bright, Key &key, Timer &timer);
    void riseScreen(Bright &bright, Key &key, Timer &timer);
    void maxBrightScreen(Bright &bright, Key &key, Timer &timer);
    void brightScreen(Bright &bright, Key &key, Timer &timer);

    void startScreen(Watch &watch, Key &key, Timer &timer);

    void screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot);
    void screens(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright);
};

#endif