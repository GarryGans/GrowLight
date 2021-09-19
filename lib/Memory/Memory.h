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

    void readSteam(int &addr, byte &var, byte minValue, byte maxValue);
    void readSteam(int &addr, boolean &var, boolean minValue, boolean maxValue);

    void read(int addr, byte &var, byte minValue, byte maxValue);
    void read(int addr, boolean &var, boolean minValue, boolean maxValue);

    void readEachSkip(Watch &watch);
    void readEachTime(Watch &watch);

    void readEachBright(Pot &pot);
    void readEachBright(Bright &bright);


    void writeTime(Watch &watch, byte id);

    void writeEachSkip(Watch &watch);
    void writeEachTime(Watch &watch);

    void writeEachBright(Pot &pot);
    void writeEachBright(Bright &bright);

    void writeChanges(Watch &watch, Pot &pot, Key &key);
    void writeChanges(Watch &watch, Bright &bright, Key &key);
};

#endif