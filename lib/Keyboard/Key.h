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
        watch
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
    boolean reBright[lampAmount];

    boolean resetManualPot;
    boolean resetManualBright;

    boolean writeBright;
    boolean writeTime;
    boolean writeDay;
    boolean writeSkip;

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

    void setScreens();
    void keyCommands(Timer &timer);
    void idChange();
    void setSpec();

    void autoScreenMove(Timer &timer);
    void manualChangeScreen(Timer &timer);

    void skipEnable(boolean &skip);
    void manualSwitchLight();
    boolean spectrumReDuration();
    boolean valChange();

    boolean changeBright();
    boolean dayReduration();
    void reset();
    void home();
    void setMode();
    boolean checkSet(Screen set);

    boolean setWatch();
    boolean navigation();
    boolean ok();
};

#endif