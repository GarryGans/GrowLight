#include <main.h>

Timer timer;
Key key(keyPin);
Watch watch;
Switchers switchers;
Bright bright;
// Pot pot;
Memory memory;
Screen screen(WavelengthSMD, lightColor);

void setup()
{
    Serial.begin(9600);

    key.begin(KB4x4, holdDelay, holdSpeed);
    delay(100);

    screen.begin();

    screen.iGorLogo();
    delay(100);

    switchers.begin(startPinLamp);
    delay(100);

    // memory.begin(watch, pot);
    delay(100);

    watch.begin();
    // watch.adjust(DateTime(F(__DATE__), F(__TIME__)));
    delay(100);

    // pot.setPot(potent);
    // pot.resetAllPots();
    bright.begin(startPinBright);
    delay(100);

    memory.begin(watch, bright, timer);
    delay(100);
}

void loop()
{
    watch.commands(key);
    switchers.switcher(watch, key);

    // pot.autoBright(watch, key);
    bright.autoBright(watch, key);

    // pot.manualChangeBright(key);
    // pot.changeMaxBright(key, watch);
    bright.manualChangeBright(watch, key);
    bright.changeBright(key, watch);

    key.keyCommands(timer);

    // screen.screens(watch,switchers,key,pot);
    screen.screens(watch, switchers, key, bright);

    // memory.writeChanges(watch, pot, key);
    memory.writeChanges(watch, bright, key, timer);
}
