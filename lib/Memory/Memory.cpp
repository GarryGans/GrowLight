#include "Memory.h"

Memory::Memory()
{
}

Memory::~Memory()
{
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

void Memory::read(int startAddr, int &addr, byte &var, byte minValue, byte maxValue)
{
    addr = startAddr;

    EEPROM.get(addr, var);

    var = constrain(var, minValue, maxValue);

    startAddr = addr + sizeof(var);
}

void Memory::readEachTime(int prew_addr, byte prewVar, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        read(startAddr, startHour_addr[id], watch.startHour[id], 0, 23);
        read(startAddr, startMinute_addr[id], watch.startMinute[id], 0, 23);
        read(startAddr, finishHour_addr[id], watch.finishHour[id], 0, 23);
        read(startAddr, finishMinute_addr[id], watch.finishMinute[id], 0, 23);
    }
}

void Memory::writeTime(int prew_addr, byte prewVar, byte id, Watch &watch)
{
    if (id == 0)
    {
        startHour_addr[id] = prew_addr + sizeof(prewVar);
    }

    else
    {
        startHour_addr[id] = finishMinute_addr[id - 1] + sizeof(watch.startHour[id - 1]);
    }

    EEPROM.put(startHour_addr[id], watch.startHour[id]);

    startMinute_addr[id] = startHour_addr[id] + sizeof(watch.startHour[id]);
    EEPROM.put(startMinute_addr[id], watch.startMinute[id]);

    finishHour_addr[id] = startMinute_addr[id] + sizeof(watch.startMinute[id]);
    EEPROM.put(finishHour_addr[id], watch.finishHour[id]);

    finishMinute_addr[id] = finishHour_addr[id] + sizeof(watch.finishHour[id]);
    EEPROM.put(finishMinute_addr[id], watch.finishMinute[id]);
}

void Memory::writeEachTime(int startAddr, Watch &watch)
{
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

void Memory::writeBright(int prew_addr, byte prewVar, byte id, Pot &pot)
{
    if (id == 0)
    {
        maxBright_addr[id] = prew_addr + prewVar;
    }

    else
    {
        maxBright_addr[id] = maxBright_addr[id - 1] + sizeof(pot.maxBright[id - 1]);
    }

    EEPROM.put(maxBright_addr[id], pot.maxBright[id]);
}

void Memory::writeBright(int prew_addr, byte prewVar, byte id, Bright &bright)
{
    if (id == 0)
    {
        maxBright_addr[id] = prew_addr + prewVar;
    }

    else
    {
        maxBright_addr[id] = maxBright_addr[id - 1] + sizeof(bright.maxBright[id - 1]);
    }

    EEPROM.put(maxBright_addr[id], bright.maxBright[id]);
}

void Memory::writeEachBright(int prew_addr, byte prewVar, Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeBright(prew_addr, prewVar, id, pot);
    }
}

void Memory::writeEachBright(int prew_addr, byte prewVar, Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeBright(prew_addr, prewVar, id, bright);
    }
}

void Memory::readEachSkip(int prew_addr, byte prewVar, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readSkip(prew_addr, prewVar, id, watch);
    }
}

void Memory::writeSkip(int prew_addr, byte prewVar, byte id, Watch &watch)
{
    if (id == 0)
    {
        skip_addr[id] = prew_addr + sizeof(prewVar);
    }

    else
    {
        skip_addr[id] = skip_addr[id - 1] + sizeof(watch.skip[id - 1]);
    }

    EEPROM.put(skip_addr[id], watch.skip[id]);
}

void Memory::writeEachSkip(int prew_addr, byte prewVar, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeSkip(prew_addr, prewVar, id, watch);
    }
}

void Memory::writeChanges(Watch &watch, Pot &pot, Key &key)
{
    if (key.writeTime)
    {
        writeTime(maxBright_addr[lampAmount - 1], pot.maxBright[key.id], key.id, watch);
        key.writeTime = false;
    }

    else if (key.writeDay)
    {
        writeEachTime(maxBright_addr[lampAmount - 1], pot.maxBright[key.id], watch);
        key.writeDay = false;
    }

    else if (key.writeBright)
    {
        writeBright(startAddr, start_addr_Size, key.id, pot);
        key.writeBright = false;
    }

    else if (key.skipEnable(watch.skip[key.id], key.id))
    {
        writeSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[key.id], key.id, watch);
    }
}

void Memory::writeChanges(Watch &watch, Bright &bright, Key &key)
{
    if (key.writeTime)
    {
        writeTime(maxBright_addr[lampAmount - 1], bright.maxBright[key.id], key.id, watch);
        key.writeTime = false;
    }

    else if (key.writeDay)
    {
        writeEachTime(maxBright_addr[lampAmount - 1], bright.maxBright[key.id], watch);
        key.writeDay = false;
    }

    else if (key.writeBright)
    {
        writeBright(startAddr, start_addr_Size, key.id, bright);
        key.writeBright = false;
    }

    else if (key.skipEnable(watch.skip[key.id], key.id))
    {
        writeSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[key.id], key.id, watch);
    }
}
