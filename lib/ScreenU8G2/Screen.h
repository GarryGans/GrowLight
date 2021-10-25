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
#include <Voltage.h>

#include <time.h>

// class Screen : public U8G2_SH1106_128X64_NONAME_1_HW_I2C
class Screen : public EFX

{
private:
    // EFX efx;
    Timer timer;
    String WavelengthSMD[lampAmount];
    String lightColor[lampAmount];
    const String state[2] = {"OFF", "ON"};
    // const char *advise[2] = {"Set SunTime", "Set MaxBright"};

    const String daysOfTheWeek[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

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

    void brightInfo(Pot &pot, Key &key);
    void brightInfo(Bright &bright, Key &key);

    void bottomLine(Watch &watch, Key &key, Pot &pot);
    void bottomLine(Watch &watch, Key &key, Bright &bright);

    void lampInfo(Watch &watch, Key &key);

    void blinkDate(Key &key, Watch &watch);
    void blinkTime(Key &key, Watch &watch);

    void showSunTime(Watch &watch);

    void blinkSunTime(Key &key, Watch &watch);

    void timerScreen(Watch &watch, Key &key);

    void lampScreen(Watch &watch, Switchers &switchers, Key &key, Pot &pot);
    void lampScreen(Watch &watch, Switchers &switchers, Key &key, Bright &bright);

    void setWatchScreen(Watch &watch, Key &key);

    void sunTimeScreen(Watch &watch, Key &key);

    void intervalScreen(Watch &watch, Key &key);

    void riseSpeedScreen(Pot &pot, Key &key);
    void riseSpeedScreen(Bright &bright, Key &key);

    void setScreen(Bright &bright, Key &key);
    void riseScreen(Bright &bright, Key &key);
    void maxBrightScreen(Bright &bright, Key &key);
    void brightScreen(Bright &bright, Key &key);

    void setScreen(Pot &pot, Key &key);
    void riseScreen(Pot &pot, Key &key);
    void maxBrightScreen(Pot &pot, Key &key);
    void brightScreen(Pot &pot, Key &key);

    void allBrightScreen(Pot &pot, Key &key);
    void allBrightScreen(Bright &bright, Key &key);

    void voltageScreen(Bright &bright, Voltage &voltage, Key &key);

    void startScreen(Watch &watch, Key &key);

    void screens(Watch &watch, Switchers &switchers, Key &key, Pot &pot);
    void screens(Watch &watch, Switchers &switchers, Key &key, Bright &bright);
};

#endif