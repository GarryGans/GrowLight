#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Watch.h>
#include <Pot.h>
#include <Key.h>
#include <Bright.h>

class Memory
{
private:
    int startAddr = 0;
    byte start_addr_Size = 0;

    int maxBright_addr[lampAmount];
    int riseBright_addr[lampAmount];
    int setBright_addr[lampAmount];

    int startHour_addr[lampAmount];
    int startMinute_addr[lampAmount];
    int finishHour_addr[lampAmount];
    int finishMinute_addr[lampAmount];

    int skip_addr[lampAmount];

public:
    Memory();
    ~Memory();

    void begin(Watch &watch, Pot &pot);
    void begin(Watch &watch, Bright &bright);

    void read(int startAddr, int &addr, byte &var, byte minValue, byte maxValue);

    void readEachBright(int startAddr, Pot &pot);
    void readEachBright(int startAddr, Bright &bright);

    void readEachTime(int prew_addr, byte prewVar, Watch &watch);

    void readEachSkip(int prew_addr, byte prewVar, Watch &watch);

    void writeEachBright(int prew_addr, byte prewVar, Pot &pot);
    void writeEachBright(int prew_addr, byte prewVar, Bright &bright);

    void writeSkip(int prew_addr, byte prewVar, byte id, Watch &watch);
    void writeEachTime(int startAdd, Watch &watch);
    void writeEachSkip(int prew_addr, byte prewVar, Watch &watch);

    void writeChanges(Watch &watch, Pot &pot, Key &key);
    void writeChanges(Watch &watch, Bright &bright, Key &key);
};

#endif