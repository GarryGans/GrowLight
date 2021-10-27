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
    Timer timer;

    int startAddr = 0;
    byte start_addr_Size = 0;

    int allBright_addr;

    int maxBright_addr[lampAmount];
    int riseBright_addr[lampAmount];
    int setBright_addr[lampAmount];

    int startHour_addr[lampAmount];
    int startMinute_addr[lampAmount];
    int finishHour_addr[lampAmount];
    int finishMinute_addr[lampAmount];

    int skip_addr[lampAmount];

    int interval_addr;
    int speed_addr;

    byte zero = 0;

public:
    Memory();
    ~Memory();

    void begin(Watch &watch, Pot &pot);
    void begin(Watch &watch, Bright &bright);

    template <typename type>
    void read(int &addr, type &var, type minValue, type maxValue);

    void readEachSkip(Watch &watch);

    void readEachTime(Watch &watch);

    void readEachBright(Pot &pot);
    void readEachBright(Bright &bright);

    void write(int &addr, byte &var);
    void write(int &addr, boolean &var);

    void writeAllBright(Bright &bright);

    void writeEachSkip(Watch &watch);

    void writeTime(Watch &watch, byte id);

    void writeEachTime(Watch &watch);

    void writeBright(Pot &pot, byte id);
    void writeBright(Bright &bright, byte id);

    void writeEachBright(Pot &pot);
    void writeEachBright(Bright &bright);

    void writeChanges(Watch &watch, Pot &pot, Key &key);
    void writeChanges(Watch &watch, Bright &bright, Key &key);
};

#endif