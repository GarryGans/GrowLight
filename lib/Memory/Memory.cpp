#include "Memory.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::read(int &addr, unsigned int &var, unsigned int minValue, unsigned int maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::read(int &addr, byte &var, byte minValue, byte maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::read(int &addr, boolean &var, boolean minValue, boolean maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::readEachSkip(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(skip_addr[id], watch.skip[id], false, true);
    }
}

void Memory::readEachTime(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(startHour_addr[id], watch.startHour[id], 0, 23);
        read(startMinute_addr[id], watch.startMinute[id], 0, 59);
        read(finishHour_addr[id], watch.finishHour[id], 0, 23);
        read(finishMinute_addr[id], watch.finishMinute[id], 0, 59);
    }
}

void Memory::readEachBright(Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(setBright_addr[id], pot.setBright[id], pot.minManualBright, pot.maxManualBright);
        read(riseBright_addr[id], pot.riseBright[id], pot.setBright[id], pot.maxManualBright);
        read(maxBright_addr[id], pot.maxBright[id], pot.setBright[id], pot.maxManualBright);
    }
}

void Memory::readEachBright(Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(setBright_addr[id], bright.setBright[id], bright.minManualBright, bright.maxManualBright);
        read(riseBright_addr[id], bright.riseBright[id], bright.setBright[id], bright.maxManualBright);
        read(maxBright_addr[id], bright.maxBright[id], bright.setBright[id], bright.maxManualBright);
    }
}

void Memory::writeEachSkip(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        EEPROM.put(skip_addr[id], watch.skip[id]);
    }
}

void Memory::writeTime(Watch &watch, byte id)
{
    EEPROM.put(startHour_addr[id], watch.startHour[id]);
    EEPROM.put(startMinute_addr[id], watch.startMinute[id]);
    EEPROM.put(finishHour_addr[id], watch.finishHour[id]);
    EEPROM.put(finishMinute_addr[id], watch.finishMinute[id]);
}

void Memory::writeEachTime(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeTime(watch, id);
    }
}

void Memory::writeBright(Pot &pot, byte id)
{
    EEPROM.put(setBright_addr[id], pot.setBright[id]);
    EEPROM.put(riseBright_addr[id], pot.riseBright[id]);
    EEPROM.put(maxBright_addr[id], pot.maxBright[id]);
}

void Memory::writeBright(Bright &bright, byte id)
{
    EEPROM.put(setBright_addr[id], bright.setBright[id]);
    EEPROM.put(riseBright_addr[id], bright.riseBright[id]);
    EEPROM.put(maxBright_addr[id], bright.maxBright[id]);
}

void Memory::writeEachBright(Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeBright(pot, id);
    }
}

void Memory::writeEachBright(Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeBright(bright, id);
    }
}

void Memory::writeChanges(Watch &watch, Pot &pot, Key &key, Timer &timer)
{
    if (key.writeTime)
    {
        writeTime(watch, key.id);

        key.writeTime = false;
    }

    else if (key.writeDay)
    {
        writeEachTime(watch);

        key.writeDay = false;
    }

    else if (key.writeBright)
    {
        writeBright(pot, key.id);

        key.writeBright = false;
    }

    else if (key.writeSkip)
    {
        EEPROM.put(skip_addr[key.id], watch.skip[key.id]);

        key.writeSkip = false;
    }
}

void Memory::writeChanges(Watch &watch, Bright &bright, Key &key, Timer &timer)
{
    if (key.writeTime)
    {
        writeTime(watch, key.id);

        key.writeTime = false;
    }

    else if (key.writeDay)
    {
        writeEachTime(watch);

        key.writeDay = false;
    }

    else if (key.writeBright)
    {
        writeBright(bright, key.id);

        key.writeBright = false;
    }

    else if (key.writeSkip)
    {
        EEPROM.put(skip_addr[key.id], watch.skip[key.id]);

        key.writeSkip = false;
    }

    else if (key.writeInterval && key.writeSpeed)
    {
        EEPROM.put(interval_addr, watch.interval);

        key.writeInterval = false;

        EEPROM.put(speed_addr, timer.rise);
        key.writeSpeed = false;
    }

    else if (key.writeAllBright)
    {
        EEPROM.put(allBright_addr, bright.allBrigh);
        key.writeAllBright = false;
    }
}

void Memory::begin(Watch &watch, Pot &pot, Timer &timer)
{
    readEachBright(pot);
    readEachTime(watch);
    readEachSkip(watch);
    read(interval_addr, watch.interval, 0, 255);
    read(speed_addr, timer.rise, 0, 255);
}

void Memory::begin(Watch &watch, Bright &bright, Timer &timer)
{
    readEachBright(bright);
    readEachTime(watch);
    readEachSkip(watch);
    read(speed_addr, timer.rise, 0, 255);
    read(interval_addr, watch.interval, 0, 255);
    read(allBright_addr, bright.allBrigh, 0, bright.maxAllBright);
}