#ifndef Key_H
#define Key_H

#include <Arduino.h>
#include <AmperkaKB.h>
#include <Timer.h>
#include <Data.h>

class Key : public AmperkaKB
{
    friend class Screen;
    friend class Switchers;
    friend class Pot;
    friend class Watch;
    friend class Memory;
    friend class Bright;

private:
    Timer timer;

    enum Screen
    {
        start,
        lamp,
        manual,
        duration,
        maxBright,
        riseBright,
        setBright,
        sunSpeed,
        dayDuration,
        watch,
        speed,
        interval,
        bright
    } screen = start;

    enum Direction
    {
        BACK,
        FORWARD
    } direction;

    enum Act
    {
        PLUS,
        MINUS
    } act;

    boolean autoMove;

    boolean buttonSwitch[lampAmount];
    boolean reduration[lampAmount];
    boolean reDay;

    boolean resetManualPot;
    boolean resetManualBright;

    boolean writeBright;
    boolean writeTime;
    boolean writeDay;
    boolean writeSkip;
    boolean writeInterval;
    boolean writeSpeed;
    boolean writeAllBright;

    boolean reBright[lampAmount];

    boolean correctDay;

    boolean setDateTime;
    boolean setDate;
    boolean setTime;

    byte id;
    byte idFirst = 0;
    byte idLast = lampAmount - 1;

public:
    Key(byte pin[]);
    Key();
    ~Key();

    //void setPresets() // Vega, Bloom(time, bright, spectr)
    Screen changeScreen();

    void checkKeyboard();

    void menuScreen(Screen start, Screen end);

    void setScreens();
    boolean chekSet(Screen screen);
    void keyCommands(Timer &timer);
    void idChange();
    void setSpec();

    void autoScreenMove(Timer &timer);
    void manualChangeScreen(Timer &timer);

    void skipEnable(boolean &skip);
    void manualSwitchLight();

    boolean ok();
    boolean valChange();
    boolean navigation();

    boolean spectrumReDuration();
    boolean riseSpeedChange();
    boolean changeBright();
    boolean dayReduration();
    boolean setWatch();
    void setSpeed(Timer &timer);
    boolean allBrigh();
};

#endif