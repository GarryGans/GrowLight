#include "Memory.h"

Memory::Memory()
{
}

Memory::~Memory()
{
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

    this->startAddr = addr + sizeof(var);
}

void Memory::read(int &addr, byte &var, byte minValue, byte maxValue)
{
    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);
}

void Memory::read(int &addr, boolean &var, boolean minValue, boolean maxValue)
{
    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);
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

void Memory::write(int &addr, byte &var)
{
    addr = startAddr;

    EEPROM.put(addr, var);

    startAddr = addr + sizeof(var);
}

void Memory::writeEachBright(Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(setBright_addr[id], pot.setBright[id]);
        write(riseBright_addr[id], pot.riseBright[id]);
        write(maxBright_addr[id], pot.maxBright[id]);
    }
}

void Memory::writeEachBright(Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(setBright_addr[id], bright.setBright[id]);
        write(riseBright_addr[id], bright.riseBright[id]);
        write(maxBright_addr[id], bright.maxBright[id]);
    }
}

void Memory::writeEachSkip(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(skip_addr[id], watch.skip[id]);
    }
}

void Memory::writeEachTime(Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(startHour_addr[id], watch.startHour[id]);
        write(startMinute_addr[id], watch.startMinute[id]);
        write(finishHour_addr[id], watch.finishHour[id]);
        write(finishMinute_addr[id], watch.finishMinute[id]);
    }
}

void Memory::writeChanges(Watch &watch, Pot &pot, Key &key)
{
    // if (key.writeTime)
    // {
    //     writeTime(maxBright_addr[lampAmount - 1], pot.maxBright[key.id], key.id, watch);
    //     key.writeTime = false;
    // }

    // else if (key.writeDay)
    // {
    //     writeEachTime(maxBright_addr[lampAmount - 1], pot.maxBright[key.id], watch);
    //     key.writeDay = false;
    // }

    // else if (key.writeBright)
    // {
    //     writeBright( start_addr_Size, key.id, pot);
    //     key.writeBright = false;
    // }

    // else if (key.skipEnable(watch.skip[key.id], key.id))
    // {
    //     writeSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[key.id], key.id, watch);
    // }
}

void Memory::writeChanges(Watch &watch, Bright &bright, Key &key)
{
    // if (key.writeTime)
    // {
    //     writeTime(maxBright_addr[lampAmount - 1], bright.maxBright[key.id], key.id, watch);
    //     key.writeTime = false;
    // }

    // else if (key.writeDay)
    // {
    //     writeEachTime(maxBright_addr[lampAmount - 1], bright.maxBright[key.id], watch);
    //     key.writeDay = false;
    // }

    // else if (key.writeBright)
    // {
    //     writeBright( start_addr_Size, key.id, bright);
    //     key.writeBright = false;
    // }

    // else if (key.skipEnable(watch.skip[key.id], key.id))
    // {
    //     writeSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[key.id], key.id, watch);
    // }
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