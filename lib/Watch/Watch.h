#ifndef WATCH_H
#define WATCH_H

#include <Arduino.h>
#include <RTC_extention.h>
#include <Wire.h>
#include <Key.h>
#include <Timer.h>

class Watch : public RTC_ext_1307
// class Watch : public RTC_ext_3231
{
    friend class Memory;
    friend class ScreenU8G2;
    friend class Screen;
    friend class Switchers;
    friend class Pot;
    friend class Bright;

private:
    byte lampAmount;

    byte cursorDateTime;
    byte cursorSpectrum;
    byte cursorDay;

    boolean leapYear;

    int year;
    byte month;
    byte day;
    byte hour;
    byte min;
    byte sec;
    byte dow;

    int *start;
    int *finish;
    // int duration;

    int daySTD = 12 * 60;
    int totalDayLenght = daySTD;

    const int midNightBefore = 23 * 60 + 59;
    const int midNightAfter = 0;

    boolean *autoSwitch;
    boolean *skip;

    boolean *brightDown;

    int intervalDefault = 1;
    int interval = 0;

    byte startHourStd = 6;
    byte startMinuteStd = 0;
    byte finishHourStd = 18;
    byte finishMinuteStd = 0;

    byte *startHour;
    byte *startMinute;
    byte *finishHour;
    byte *finishMinute;

    byte RiseHour;
    byte RiseMin;
    byte SetHour;
    byte SetMin;

public:
    Watch(byte amount);
    ~Watch();

    void timeFromMinute(int time, byte &hour, byte &minute);
    int nowTime();
    int calculateTimeToMinute(byte setHour, byte setMinute);
    void autoSwitchLight(int start, int finish, boolean &autoSwitch, boolean &brightDown);
    void autoSwitcher(Key &key);

    void cursorChange(Key &key, byte &cursor);
    void hmsChange(Key &key, byte &hms, byte &cursor, Timer &timer);

    void spectrumReDuration(Key &key, Timer &timer);
    void dayReduration(Key &key, Timer &timer);

    void dtCursor(Key &key);
    void timeChange(byte &time, Key &key, Timer &timer);
    void yearChange(int &year, Key &key, Timer &timer);
    void monthChange(byte &month, Key &key, Timer &timer);
    void dayChange(byte &day, Key &key, Timer &timer);
    void leapYearDay();
    void setWatch(Key &key, Timer &timer);
};

#endif