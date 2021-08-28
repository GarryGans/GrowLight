#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Watch.h>
#include <Pot.h>
#include <Key.h>
#include <KeyPad.h>
#include <Bright.h>


class Memory
{
private:
    byte Amount;

    byte startAddr = 0;
    byte start_addr_Size = 0;

    byte *maxBright_addr;

    byte *startHour_addr;
    byte *startMinute_addr;
    byte *finishHour_addr;
    byte *finishMinute_addr;

    byte *skip_addr;
    

public:
    Memory(byte amount);
    ~Memory();

    void begin(Watch &watch, Pot &pot);
    void begin(Watch &watch, Bright &bright);

    void firstHour(byte &hour);
    void firstMin(byte &min);

    void readTime(int prew_addr, byte prewVar, byte id, Watch &watch);
    void readEachTime(int prew_addr, byte prewVar, Watch &watch);

    void writeTime(int prew_addr, byte prewVar, byte id, Watch &watch);
    void writeEachTime(int prew_addr, byte prewVar, Watch &watch);

    void readBright(int prew_addr, byte prewVar, byte id, Pot &pot);
    void readBright(int prew_addr, byte prewVar, byte id, Bright &bright);
    void readEachBright(int prew_addr, byte prewVar, Pot &pot);
    void readEachBright(int prew_addr, byte prewVar, Bright &bright);

    void writeBright(int prew_addr, byte prewVar, byte id, Pot &pot);
    void writeBright(int prew_addr, byte prewVar, byte id, Bright &bright);
    void writeEachBright(int prew_addr, byte prewVar, Pot &pot);
    void writeEachBright(int prew_addr, byte prewVar, Bright &bright);

    void readSkip(int prew_addr, byte prewVar, byte id, Watch &watch);
    void readEachSkip(int prew_addr, byte prewVar, Watch &watch);

    void writeSkip(int prew_addr, byte prewVar, byte id, Watch &watch);
    void writeEachSkip(int prew_addr, byte prewVar, Watch &watch);

    // void writeChanges(Watch &watch, Pot &pot, Key &key);
    // void writeChanges(Watch &watch, Bright &bright, Key &key);
    void writeChanges(Watch &watch, Pot &pot, KeyPad &key);
    void writeChanges(Watch &watch, Bright &bright, KeyPad &key);
};

#endif