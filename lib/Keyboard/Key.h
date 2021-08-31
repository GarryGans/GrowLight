#ifndef Key_H
#define Key_H

#include <Arduino.h>
#include <AmperkaKB.h>
#include <Timer.h>
#include <Data.h>

class Key : public AmperkaKB
{
    friend class ScreenU8G2;
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
        bright,
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
    boolean correctBright;

    boolean setDateTime;
    boolean setDate;
    boolean setTime;

    byte id;
    byte idFirst = 0;
    byte idLast = lampAmount - 1;

public:
    Key(byte pin[]);
    ~Key();

    //void setPresets() // Vega, Bloom(time, bright, spectr)

    void checkKeyboard();

    void keyCommands(Timer &timer);
    void idChange();
    void setSpec();

    void autoScreenMove(Timer &timer);
    void manualChangeScreen(Timer &timer);

    boolean skipEnable(boolean &skip, byte id);
    void manualSwitchLight();
    boolean spectrumReDuration();
    boolean valChange(Timer &timer);

    boolean changeMaxBright();
    boolean dayReduration();
    void reset();
    void home();
    void resetToLamp();
    void setMode();
    boolean checkSet(Screen set);

    boolean setWatch();
    boolean navigation();
    boolean ok();
};

#endif