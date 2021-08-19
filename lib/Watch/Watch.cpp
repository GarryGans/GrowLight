#include "Watch.h"

#define OFF HIGH // реле: 1 - высокого уровня (или мосфет), 0 - низкого
#define ON LOW

// Watch::Watch() : RTC_ext_1307()
Watch::Watch() : RTC_ext_3231()
{
}

Watch::~Watch()
{
}

void Watch::timeFromMinute(int time, byte &hour, byte &minute)
{
    hour = 0;

    while (time >= 60)
    {
        time -= 60;
        hour++;
    }

    minute = time;
}

int Watch::calculateTimeToMinute(byte setHour, byte setMinute)
{
    return (setHour * 60 + setMinute);
}

int Watch::nowTime()
{
    DateTime time = now();
    return (calculateTimeToMinute(time.hour(), time.minute()));
}

void Watch::autoSwitchLight(int start, int finish, boolean &autoSwitch, boolean &brightDown)
{
    if (start == finish)
    {
        autoSwitch = true;
        brightDown = false;
    }

    else if (start > finish)
    {
        if ((nowTime() >= start && nowTime() <= midNightBefore) || (nowTime() >= midNightAfter && nowTime() < finish))
        {
            autoSwitch = true;
            brightDown = false;
        }
        else
        {
            brightDown = true;
        }
    }

    else if (start < finish)
    {
        if ((nowTime() >= start && nowTime() < finish))
        {
            autoSwitch = true;
            brightDown = false;
        }
        else
        {
            brightDown = true;
        }
    }

    else
    {
        autoSwitch = false;
    }
}

void Watch::autoSwitcher(Key &key)
{
    if (key.screen != key.dayDuration)
    {
        RiseHour = startHour[0];
        RiseMin = startMinute[0];
        SetHour = finishHour[0];
        SetMin = finishMinute[0];
    }

    if (key.screen != key.manual)
    {
        for (byte i = 0; i < lampAmount; i++)
        {
            if (!skip[i] && !key.reduration[i])
            {
                start[i] = calculateTimeToMinute(startHour[i], startMinute[i]);
                finish[i] = calculateTimeToMinute(finishHour[i], finishMinute[i]);
                autoSwitchLight(start[i], finish[i], autoSwitch[i], brightDown[i]);
            }
            else if (skip[i])
            {
                autoSwitch[i] = false;
            }
        }
    }

    else
    {
        for (byte i = 0; i < lampAmount; i++)
        {
            autoSwitch[i] = false;
        }
    }
}

void Watch::cursorChange(Key &key, byte &cursor)
{
    if (key.direction == key.FORWARD)
    {
        cursor++;
        if (cursor > 3)
        {
            cursor = 0;
        }
    }

    if (key.direction == key.BACK)
    {
        cursor--;
        cursor = constrain(cursor, 0, 3);
    }
}

void Watch::hmsChange(Key &key, byte &hms, byte &cursor, Timer &timer)
{
    if (key.valChange(timer))
    {
        if (key.act == key.MINUS)
        {
            hms--;
            if (cursor == 0 || cursor == 2)
            {
                hms = constrain(hms, 0, 23);
            }
            if (cursor == 1 || cursor == 3)
            {
                hms = constrain(hms, 0, 59);
            }
        }

        if (key.act == key.PLUS)
        {
            hms++;
            if ((cursor == 0 || cursor == 2) && hms > 23)
            {
                hms = 0;
            }
            if ((cursor == 1 || cursor == 3) && hms > 59)
            {
                hms = 0;
            }
        }
    }

    if (key.navigation())
    {
        cursorChange(key, cursor);
    }
}

void Watch::spectrumReDuration(Key &key, Timer &timer)
{
    if (key.spectrumReDuration())
    {
        key.reduration[key.id] = true;

        cursorSpectrum = 0;
    }

    if (key.screen == key.duration)
    {
        if (cursorSpectrum == 0)
        {
            hmsChange(key, startHour[key.id], cursorSpectrum, timer);
        }
        else if (cursorSpectrum == 1)
        {
            hmsChange(key, startMinute[key.id], cursorSpectrum, timer);
        }
        else if (cursorSpectrum == 2)
        {
            hmsChange(key, finishHour[key.id], cursorSpectrum, timer);
        }
        else if (cursorSpectrum == 3)
        {
            hmsChange(key, finishMinute[key.id], cursorSpectrum, timer);
        }
    }
}

void Watch::dayReduration(Key &key, Timer &timer)
{
    if (key.dayReduration())
    {
        RiseHour = startHourStd;
        RiseMin = startMinuteStd;
        SetHour = finishHourStd;
        SetMin = finishMinuteStd;

        cursorDay = 0;
    }

    if (key.screen == key.dayDuration)
    {
        if (cursorDay == 0)
        {
            hmsChange(key, RiseHour, cursorDay, timer);
        }
        else if (cursorDay == 1)
        {
            hmsChange(key, RiseMin, cursorDay, timer);
        }
        else if (cursorDay == 2)
        {
            hmsChange(key, SetHour, cursorDay, timer);
        }
        else if (cursorDay == 3)
        {
            hmsChange(key, SetMin, cursorDay, timer);
        }
    }

    if (key.correctDay)
    {
        start[0] = calculateTimeToMinute(RiseHour, RiseMin);
        finish[0] = calculateTimeToMinute(SetHour, SetMin);

        for (byte id = 0; id < lampAmount; id++)
        {
            timeFromMinute(start[0] + interval, startHour[id], startMinute[id]);
            timeFromMinute(finish[0] - interval, finishHour[id], finishMinute[id]);
            interval += intervalDefault;
        }

        interval = 0;

        key.correctDay = false;
    }
}

void Watch::timeChange(int &dt, Key &key, Timer &timer)
{
    if (key.valChange(timer))
    {
        if (key.act == key.MINUS)
        {
            dt--;

            if (cursorDateTime == 3 && dt < 0)
            {
                dt = 23;
            }

            if ((cursorDateTime == 4 || cursorDateTime == 5) && dt < 0)
            {
                dt = 59;
            }
        }

        if (key.act == key.PLUS)
        {
            dt++;

            if (cursorDateTime == 3 && dt > 23)
            {
                dt = 0;
            }

            if ((cursorDateTime == 4 || cursorDateTime == 5) && dt > 59)
            {
                dt = 0;
            }
        }
    }

    if (key.navigation())
    {
        switch (key.direction)
        {
        case key.FORWARD:
            cursorDateTime++;
            cursorDateTime = constrain(cursorDateTime, 0, 5);
            break;

        case key.BACK:
            cursorDateTime--;
            cursorDateTime = constrain(cursorDateTime, 0, 5);
            break;

        default:
            break;
        }
    }
}

void Watch::dataChange(int &dt, Key &key, Timer &timer)
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        leapYear = true;
    }
    else
    {
        leapYear = false;
    }

    if (key.valChange(timer))
    {
        if (key.act == key.MINUS)
        {
            dt--;

            if (cursorDateTime == 0 && dt < 1)
            {
                if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                {
                    dt = 31;
                }
                else if (month == 4 || month == 6 || month == 9 || month == 11)
                {
                    dt = 30;
                }
                else if (month == 2 && leapYear)
                {
                    dt = 29;
                }
                else if (month == 2 && !leapYear)
                {
                    dt = 28;
                }
            }

            if (cursorDateTime == 1 && dt < 1)
            {
                dt = 12;
            }

            if (cursorDateTime == 2 && dt < 2000)
            {
                dt = 2000;
            }
        }

        if (key.act == key.PLUS)
        {
            dt++;

            if (cursorDateTime == 0)
            {
                if (dt > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                {
                    dt = 1;
                }

                else if (dt > 30 && (month == 4 || month == 6 || month == 9 || month == 11))
                {
                    dt = 1;
                }

                else if (dt > 29 && month == 2 && leapYear)
                {
                    dt = 1;
                }

                else if (dt > 28 && month == 2 && !leapYear)
                {
                    dt = 1;
                }
            }

            if (cursorDateTime == 1 && dt > 12)
            {
                dt = 1;
            }
        }
    }

    if (day > 29 && month == 2 && leapYear)
    {
        day = 29;
    }

    if (day > 28 && month == 2 && !leapYear)
    {
        day = 28;
    }

    if (key.navigation())
    {
        switch (key.direction)
        {
        case key.FORWARD:
            cursorDateTime++;
            cursorDateTime = constrain(cursorDateTime, 0, 5);
            break;

        case key.BACK:
            cursorDateTime--;
            cursorDateTime = constrain(cursorDateTime, 0, 5);
            break;

        default:
            break;
        }
    }
}

void Watch::clockChange(int &dt, Key &key, Timer &timer)
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        leapYear = true;
    }
    else
    {
        leapYear = false;
    }

    if (key.valChange(timer))
    {
        if (key.act == key.MINUS)
        {
            dt--;

            if (cursorDateTime == 0 && dt < 1)
            {
                if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
                {
                    dt = 31;
                }
                else if (month == 4 || month == 6 || month == 9 || month == 11)
                {
                    dt = 30;
                }
                else if (month == 2 && leapYear)
                {
                    dt = 29;
                }
                else if (month == 2 && !leapYear)
                {
                    dt = 28;
                }
            }

            if (cursorDateTime == 1 && dt < 1)
            {
                dt = 12;
            }

            if (cursorDateTime == 2 && dt < 2000)
            {
                dt = 2000;
            }

            if (cursorDateTime == 3 && dt < 0)
            {
                dt = 23;
            }

            if ((cursorDateTime == 4 || cursorDateTime == 5) && dt < 0)
            {
                dt = 59;
            }
        }

        if (key.act == key.PLUS)
        {
            dt++;

            if (cursorDateTime == 0)
            {
                if (dt > 31 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12))
                {
                    dt = 1;
                }

                else if (dt > 30 && (month == 4 || month == 6 || month == 9 || month == 11))
                {
                    dt = 1;
                }

                else if (dt > 29 && month == 2 && leapYear)
                {
                    dt = 1;
                }

                else if (dt > 28 && month == 2 && !leapYear)
                {
                    dt = 1;
                }
            }

            if (cursorDateTime == 1 && dt > 12)
            {
                dt = 1;
            }

            if (cursorDateTime == 3 && dt > 23)
            {
                dt = 0;
            }

            if ((cursorDateTime == 4 || cursorDateTime == 5) && dt > 59)
            {
                dt = 0;
            }
        }
    }

    if (day > 29 && month == 2 && leapYear)
    {
        day = 29;
    }

    if (day > 28 && month == 2 && !leapYear)
    {
        day = 28;
    }

    if (key.navigation())
    {
        switch (key.direction)
        {
        case key.FORWARD:
            cursorDateTime++;
            cursorDateTime = constrain(cursorDateTime, 0, 5);
            break;

        case key.BACK:
            cursorDateTime--;
            cursorDateTime = constrain(cursorDateTime, 0, 5);
            break;

        default:
            break;
        }
    }
}

void Watch::setWatch(Key &key, Timer &timer)
{
    if (key.setWatch())
    {
        cursorDateTime = 0;

        DateTime time = now();
        dow = time.dayOfTheWeek();

        if (time.year() < 2021)
        {
            year = 2021;
        }
        else
        {
            year = time.year();
        }

        month = time.month();
        day = time.day();
        hour = time.hour();
        min = time.minute();
        sec = time.second();
    }

    if (key.screen == key.watch)
    {
        if (cursorDateTime == 0)
        {
            clockChange(day, key, timer);
        }
        else if (cursorDateTime == 1)
        {
            clockChange(month, key, timer);
        }
        else if (cursorDateTime == 2)
        {
            clockChange(year, key, timer);
        }
        else if (cursorDateTime == 3)
        {
            clockChange(hour, key, timer);
        }
        else if (cursorDateTime == 4)
        {
            clockChange(min, key, timer);
        }
        else if (cursorDateTime == 5)
        {
            clockChange(sec, key, timer);
        }
    }

    if (key.setDateTime)
    {
        adjust(DateTime(year, month, day, hour, min, sec));
        key.setDateTime = false;
    }
}
