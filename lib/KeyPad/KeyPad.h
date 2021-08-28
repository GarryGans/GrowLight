#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>
#include "Adafruit_Keypad.h"
#include <Timer.h>

#define lampAmount 8

class KeyPad : public Adafruit_Keypad
{
    friend class ScreenU8G2;
    friend class Screen;
    friend class Switchers;
    friend class Pot;
    friend class Watch;
    friend class Memory;
    friend class Bright;

private:
    static const byte ROWS = 4;
    static const byte COLS = 4;

    char keys[ROWS][COLS] = {{'1', '2', '3', 'A'},
                             {'4', '5', '6', 'B'},
                             {'7', '8', '9', 'C'},
                             {'*', '0', '#', 'D'}};

    boolean hold;
    boolean press;

    char num;

    unsigned long prewDelay;
    unsigned long holdDelay;
    unsigned long prewSpeed;
    unsigned long holdSpeed;

    byte Amount;

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

    // boolean *buttonSwitch;
    // boolean *reduration;
    // boolean *reBright;

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
    byte idLast;

public:
    KeyPad(byte rowPins[], byte colPins[], byte amount);
    ~KeyPad();

    void begin(unsigned long holdDelay, unsigned long holdSpeed);
    boolean keyEvent();
    
    void test();

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