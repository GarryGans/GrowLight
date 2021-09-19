#include "Memory.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::read(int addr, byte &var, byte minValue, byte maxValue)
{
    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);
}

void Memory::read(int addr, boolean &var, boolean minValue, boolean maxValue)
{
    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);
}

void Memory::readSteam(int &addr, byte &var, byte minValue, byte maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::readSteam(int &addr, boolean &var, boolean minValue, boolean maxValue)
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
        readSteam(skip_addr[id], watch.skip[id], false, true);
    }
}

void Memory::readEachTime(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readSteam(startHour_addr[id], watch.startHour[id], 0, 23);
        readSteam(startMinute_addr[id], watch.startMinute[id], 0, 59);
        readSteam(finishHour_addr[id], watch.finishHour[id], 0, 23);
        readSteam(finishMinute_addr[id], watch.finishMinute[id], 0, 59);
    }
}

void Memory::readEachBright(Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readSteam(setBright_addr[id], pot.setBright[id], pot.minManualBright, pot.maxManualBright);
        readSteam(riseBright_addr[id], pot.riseBright[id], pot.setBright[id], pot.maxManualBright);
        readSteam(maxBright_addr[id], pot.maxBright[id], pot.setBright[id], pot.maxManualBright);
    }
}

void Memory::readEachBright(Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readSteam(setBright_addr[id], bright.setBright[id], bright.minManualBright, bright.maxManualBright);
        readSteam(riseBright_addr[id], bright.riseBright[id], bright.setBright[id], bright.maxManualBright);
        readSteam(maxBright_addr[id], bright.maxBright[id], bright.setBright[id], bright.maxManualBright);
    }
}

void Memory::writeEachBright(Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        EEPROM.put(setBright_addr[id], pot.setBright[id]);
        EEPROM.put(riseBright_addr[id], pot.riseBright[id]);
        EEPROM.put(maxBright_addr[id], pot.maxBright[id]);
    }
}

void Memory::writeEachBright(Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        EEPROM.put(setBright_addr[id], bright.setBright[id]);
        EEPROM.put(riseBright_addr[id], bright.riseBright[id]);
        EEPROM.put(maxBright_addr[id], bright.maxBright[id]);
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

void Memory::writeChanges(Watch &watch, Pot &pot, Key &key)
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
        EEPROM.put(setBright_addr[key.id], pot.setBright[key.id]);
        EEPROM.put(riseBright_addr[key.id], pot.riseBright[key.id]);
        EEPROM.put(maxBright_addr[key.id], pot.maxBright[key.id]);

        key.writeBright = false;
    }

    else if (key.writeSkip)
    {
        EEPROM.put(skip_addr[key.id], watch.skip[key.id]);
    }
}

void Memory::writeChanges(Watch &watch, Bright &bright, Key &key)
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
        EEPROM.put(setBright_addr[key.id], bright.setBright[key.id]);
        EEPROM.put(riseBright_addr[key.id], bright.riseBright[key.id]);
        EEPROM.put(maxBright_addr[key.id], bright.maxBright[key.id]);

        key.writeBright = false;
    }

    else if (key.writeSkip)
    {
        EEPROM.put(skip_addr[key.id], watch.skip[key.id]);
        key.writeSkip = false;
    }
}

void Memory::begin(Watch &watch, Pot &pot)
{
    readEachBright(pot);
    readEachTime(watch);
    readEachSkip(watch);
}

void Memory::begin(Watch &watch, Bright &bright)
{
    readEachBright(bright);
    readEachTime(watch);
    readEachSkip(watch);
}