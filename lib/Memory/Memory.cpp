#include "Memory.h"

Memory::Memory(byte amount)
{
    lampAmount = amount;

    maxBright_addr = new int[lampAmount];

    startHour_addr = new int[lampAmount];
    startMinute_addr = new int[lampAmount];
    finishHour_addr = new int[lampAmount];
    finishMinute_addr = new int[lampAmount];

    skip_addr = new int[lampAmount];
}

Memory::~Memory()
{
}

void Memory::begin(Watch &watch, Pot &pot)
{
    readEachBright(startAddr, start_addr_Size, pot);
    readEachTime(maxBright_addr[lampAmount - 1], pot.maxBright[lampAmount - 1], watch);
    readEachSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[lampAmount - 1], watch);
}

void Memory::begin(Watch &watch, Bright &bright)
{
    readEachBright(startAddr, start_addr_Size, bright);
    readEachTime(maxBright_addr[lampAmount - 1], bright.maxBright[lampAmount - 1], watch);
    readEachSkip(finishMinute_addr[lampAmount - 1], watch.finishMinute[lampAmount - 1], watch);
}

void Memory::firstHour(byte &hour)
{
    if (hour > 23 || hour < 0)
    {
        hour = 0;
    }
}

void Memory::firstMin(byte &min)
{
    if (min > 59 || min < 0)
    {
        min = 0;
    }
}

void Memory::readTime(int prew_addr, byte prewVar, byte id, Watch &watch)
{
    if (id == 0)
    {
        startHour_addr[id] = prew_addr + sizeof(prewVar);
    }

    else
    {
        startHour_addr[id] = startHour_addr[id - 1] + sizeof(watch.startHour[id - 1]);
    }

    EEPROM.get(startHour_addr[id], watch.startHour[id]);
    firstHour(watch.startHour[id]);

    startMinute_addr[id] = startHour_addr[id] + sizeof(watch.startHour);

    EEPROM.get(startMinute_addr[id], watch.startMinute[id]);
    firstMin(watch.startMinute[id]);

    finishHour_addr[id] = startMinute_addr[id] + sizeof(watch.startMinute);

    EEPROM.get(finishHour_addr[id], watch.finishHour[id]);
    firstHour(watch.finishHour[id]);

    finishMinute_addr[id] = finishHour_addr[id] + sizeof(watch.finishHour);

    EEPROM.get(finishMinute_addr[id], watch.finishMinute[id]);
    firstMin(watch.finishMinute[id]);
}

void Memory::readEachTime(int prew_addr, byte prewVar, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readTime(prew_addr, prewVar, id, watch);
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
        startHour_addr[id] = startHour_addr[id - 1] + sizeof(watch.startHour[id - 1]);
    }

    EEPROM.put(startHour_addr[id], watch.startHour[id]);

    startMinute_addr[id] = startHour_addr[id] + sizeof(watch.startHour);
    EEPROM.put(startMinute_addr[id], watch.startMinute[id]);

    finishHour_addr[id] = startMinute_addr[id] + sizeof(watch.startMinute);
    EEPROM.put(finishHour_addr[id], watch.finishHour[id]);

    finishMinute_addr[id] = finishHour_addr[id] + sizeof(watch.finishHour);
    EEPROM.put(finishMinute_addr[id], watch.finishMinute[id]);
}

void Memory::writeEachTime(int prew_addr, byte prewVar, Watch &watch)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        writeTime(prew_addr, prewVar, id, watch);
    }
}

void Memory::readBright(int prew_addr, byte prewVar, byte id, Pot &pot)
{
    if (id == 0)
    {
        maxBright_addr[id] = prew_addr + prewVar;
    }

    else
    {
        maxBright_addr[id] = maxBright_addr[id - 1] + sizeof(pot.maxBright[id - 1]);
    }

    EEPROM.get(maxBright_addr[id], pot.maxBright[id]);

    if (pot.maxBright[id] < pot.autoMinBright || pot.maxBright[id] > pot.maxManualBright)
    {
        pot.maxBright[id] = pot.autoMinBright;
    }
}

void Memory::readBright(int prew_addr, byte prewVar, byte id, Bright &bright)
{
    if (id == 0)
    {
        maxBright_addr[id] = prew_addr + prewVar;
    }

    else
    {
        maxBright_addr[id] = maxBright_addr[id - 1] + sizeof(bright.maxBright[id - 1]);
    }

    EEPROM.get(maxBright_addr[id], bright.maxBright[id]);

    if (bright.maxBright[id] < bright.autoMinBright || bright.maxBright[id] > bright.maxManualBright)
    {
        bright.maxBright[id] = bright.autoMinBright;
    }
}

void Memory::readEachBright(int prew_addr, byte prewVar, Pot &pot)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readBright(prew_addr, prewVar, id, pot);
    }
}

void Memory::readEachBright(int prew_addr, byte prewVar, Bright &bright)
{
    for (byte id = 0; id < lampAmount; id++)
    {
        readBright(prew_addr, prewVar, id, bright);
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

void Memory::readSkip(int prew_addr, byte prewVar, byte id, Watch &watch)
{

    if (id == 0)
    {
        skip_addr[id] = prew_addr + sizeof(prewVar);
    }

    else
    {
        skip_addr[id] = skip_addr[id - 1] + sizeof(watch.skip[id - 1]);
    }

    EEPROM.get(skip_addr[id], watch.skip[id]);

    if (watch.skip[id] < 0 || watch.skip[id] > 1)
    {
        watch.skip[id] = 0;
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
