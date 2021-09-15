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

// class Screen : public U8G2_SH1106_128X64_NONAME_1_HW_I2C
class Screen : public U8G2_SSD1306_128X64_NONAME_1_HW_I2C

{
private:
    String WavelengthSMD[lampAmount];
    String lightColor[lampAmount];
    const char *state[2] = {"OFF", "ON"};
    const char *solution[2] = {"MANUAL", "SKIP"};
    const char *advise[2] = {"Set SunTime", "Set MaxBright"};

    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    enum class PosX
    {
        center,
        left,
        leftSpace,
        leftHalf,
        right,
        rightSpace,
        rightHalf,
        centerFrame,
        rightFrameSide,
        rightFrameHalfSide,
        custom
    } pos_x;

    enum class PosY
    {
        center,
        up,
        upSpace,
        upHalf,
        down,
        downSpace,
        downHalf,
        centerFrame,
        upFrame,
        upFrameHalf,
        downFrame,
        downFrameSpace,
        downFrameHalf,
        custom
    } pos_y;

    const byte screenWidth = 128;
    const byte screenHeight = 64;

    byte borderW;
    byte borderH;

    byte width;
    byte height;

    byte x;
    byte y;
    byte setX;
    byte setY;
    byte blockWidth;

    byte move_x[10];
    boolean move[10];
    boolean moveLeft[10];
    boolean moveRight[10];
    byte start_x[10];
    byte start_y[10];

    int icon;
    int lock = 79;
    int unlock = 68;
    byte WH = 48;

public:
    Screen(String WavelengthSMD[], String lightColor[]);
    Screen();
    ~Screen();

    byte getDigWidth(byte value);

    void alignSimbols(byte WH, byte H, PosX pos_x, PosY pos_y);
    void frameAlign(byte W, byte H, PosX pos_x, PosY pos_y);
    void iconAlign(int icon, byte iconWH, PosX pos_x, PosY pos_y);
    void digStringAlign(byte dig, const char *string, PosX pos_x, PosY pos_y);
    void digAlign(byte dig, PosX pos_x, PosY pos_y);
    void setPosition(const char *format, PosX pos_x, PosY pos_y);
    void textAlign(const char *string, PosX pos_x, PosY pos_y);
    void stringAlign(String str, byte size, PosX pos_x, PosY pos_y);
    void setHeight(const uint8_t *font);

    void mover(byte &move_x, byte deep_x, byte id);
    void moveString(const char *string, PosX pos_x, PosY pos_y, Timer &timer, byte id);
    void escapeBar(Timer &timer);

    void iGorLogo();

    void showDig(byte value);

    void headerTime(Watch &watch);
    void headerDate(Watch &watch);

    void blinkFrame(byte value, boolean dig, PosX pos_x, PosY pos_y, Timer &timer);
    void blinkFrame(const char *format, byte digAmount, PosX pos_x, PosY pos_y, Timer &timer);

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