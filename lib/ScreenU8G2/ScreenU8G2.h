#ifndef SCREENU8G2_H
#define SCREENU8G2_H

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

#include <Watch.h>
#include <Switchers.h>
#include <Timer.h>
#include <Key.h>
#include <Pot.h>
#include <Bright.h>
#include <Data.h>

class ScreenU8G2 : public U8G2_SH1106_128X64_NONAME_1_HW_I2C
{
private:
    String WavelengthSMD[lampAmount];
    String lightColor[lampAmount];

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    enum PositionX
    {
        centerX,
        left,
        right,
        customX
    } position_x;

    enum PositionY
    {
        centerY,
        up,
        down,
        custom,
        centerFrame,
        upFrame,
        downFrame,
        customY
    } position_y;

    const byte screenWidth = 128;
    const byte screenHeight = 64;

    byte digWidth;
    byte digHeight;
    byte width;
    byte x;
    byte y;
    byte setX;
    byte setY;
    byte blockWidth;

    const byte deep_x = 30;
    byte start_x;
    byte move_x;
    byte bottom_y = 59;

    boolean moveLeft;
    boolean moveRight;
    boolean move;

    int icon;
    int lock = 79;
    int unlock = 68;
    byte WH = 48;

public:
    ScreenU8G2(String *WavelengthSMD, String *lightColor);
    ScreenU8G2();
    ~ScreenU8G2();

    byte intToChar(int value);
    void align(byte WH, byte H, PositionX position_x, PositionY position_y);
    void frameAlign(byte W, byte H, PositionX position_x, PositionY position_y);
    void iconAlign(int icon, byte iconWH, PositionX position_x, PositionY position_y);
    void digAlign(byte dig, const char *string, PositionX position_x, PositionY position_y);
    void textAlign(const char *string, PositionX position_x, PositionY position_y);
    void mover(byte deep_x);
    void moveString(Timer &timer, byte end_x, byte bottom_y, const char *string);
    void escapeBar(Timer &timer);

    void iGorLogo();

    void showDig(int value);

    void headerTime(Watch &watch);
    void headerDate(Watch &watch);
    void headerScreen(Watch &watch);

    void showBlink(int value, int x, int y, Timer &timer);
    void showBlinkYear(int year, int x, int y, Timer &timer);

    void showBlinkSpectrumTime(Watch &watch, Timer &timer, Key &key);

    void showStringTime(int hh, int mm);
    void showStringWatch(int hh, int mm, int ss);
    void showStringDate(int day, int month, int year);
    void showSpectrumTime(Watch &watch, int id);

    void brightInfo(Pot &pot, Key &key, Timer &timer);
    void brightInfo(Bright &bright, Key &key, Timer &timer);

    void bottomLine(Watch &watch, Timer &timer, Key &key, Pot &pot);
    void bottomLine(Watch &watch, Timer &timer, Key &key, Bright &bright);

    void lampInfo(Watch &watch, Key &key);

    void showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Pot &pot);
    void showLampScreen(Watch &watch, Switchers &switchers, Timer &timer, Key &key, Bright &bright);

    void showStartScreen(Watch &watch, Key &key, Timer &timer);

    void blinkHeaderDate(Key &key, Watch &watch, Timer &timer);
    void blinkHeaderTime(Key &key, Watch &watch, Timer &timer);

    void showBlinkSunRise(Key &key, Timer &timer, Watch &watch, int hh, int mm);
    void showBlinkSunSet(Key &key, Timer &timer, Watch &watch, int hh, int mm);
};

#endif