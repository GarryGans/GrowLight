#include "Memory.h"

Memory::Memory()
{
}

Memory::~Memory()
{
}

void Memory::read(int startAddr, int &addr, byte &var, byte minValue, byte maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::read(int startAddr, int &addr, boolean &var, boolean minValue, boolean maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::readEachSkip(int startAddr, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(startAddr, skip_addr[id], watch.skip[id], false, true);
    }
}

void Memory::readEachTime(int prew_addr, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(startAddr, startHour_addr[id], watch.startHour[id], 0, 23);
        read(startAddr, startMinute_addr[id], watch.startMinute[id], 0, 59);
        read(startAddr, finishHour_addr[id], watch.finishHour[id], 0, 23);
        read(startAddr, finishMinute_addr[id], watch.finishMinute[id], 0, 59);
    }
}

void Memory::readEachBright(int startAddr, Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(startAddr, setBright_addr[id], pot.setBright[id], pot.minManualBright, pot.maxManualBright);
        read(startAddr, riseBright_addr[id], pot.riseBright[id], pot.setBright[id], pot.maxManualBright);
        read(startAddr, maxBright_addr[id], pot.maxBright[id], pot.setBright[id], pot.maxManualBright);
    }
}

void Memory::readEachBright(int startAddr, Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(startAddr, setBright_addr[id], bright.setBright[id], bright.minManualBright, bright.maxManualBright);
        read(startAddr, riseBright_addr[id], bright.riseBright[id], bright.setBright[id], bright.maxManualBright);
        read(startAddr, maxBright_addr[id], bright.maxBright[id], bright.setBright[id], bright.maxManualBright);
    }
}

void Memory::write(int startAddr, int &addr, byte &var)
{
    addr = startAddr;

    EEPROM.put(addr, var);

    startAddr = addr + sizeof(var);
}

void Memory::writeEachBright(int startAddr, Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(startAddr, setBright_addr[id], pot.setBright[id]);
        write(startAddr, riseBright_addr[id], pot.riseBright[id]);
        write(startAddr, maxBright_addr[id], pot.maxBright[id]);
    }
}

void Memory::writeEachBright(int startAddr, Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(startAddr, setBright_addr[id], bright.setBright[id]);
        write(startAddr, riseBright_addr[id], bright.riseBright[id]);
        write(startAddr, maxBright_addr[id], bright.maxBright[id]);
    }
}

void Memory::writeEachSkip(int startAddr, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(startAddr, skip_addr[id], watch.skip[id]);
    }
}

void Memory::writeEachTime(int startAddr, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        write(startAddr, startHour_addr[id], watch.startHour[id]);
        write(startAddr, startMinute_addr[id], watch.startMinute[id]);
        write(startAddr, finishHour_addr[id], watch.finishHour[id]);
        write(startAddr, finishMinute_addr[id], watch.finishMinute[id]);
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
    //     writeBright(startAddr, start_addr_Size, key.id, pot);
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
    //     writeBright(startAddr, start_addr_Size, key.id, bright);
    //     key.writeBright = false;
    // }

    // else if (key.skipEnable(watch.skip[key.id], key.id))
    // {
    //     writeSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[key.id], key.id, watch);
    // }
}

void Memory::begin(Watch &watch, Pot &pot)
{
    readEachBright(startAddr, pot);
    readEachTime(setBright_addr[lampAmount - 1], pot.maxBright[lampAmount - 1], watch);
    readEachSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[lampAmount - 1], watch);
}

void Memory::begin(Watch &watch, Bright &bright)
{
    readEachBright(startAddr, bright);
    readEachTime(setBright_addr[lampAmount - 1], bright.maxBright[lampAmount - 1], watch);
    readEachSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[lampAmount - 1], watch);
}