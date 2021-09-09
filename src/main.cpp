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
    screen.begin();

    // screen.iGorLogo();
    delay(100);

    watch.begin();
    // watch.adjust(DateTime(F(__DATE__), F(__TIME__)));
    delay(100);

    key.begin(KB4x4, holdDelay, holdSpeed);
    delay(100);

    switchers.begin(startPinLamp);
    delay(100);

    // pot.setPot(potent);
    // pot.resetAllPots();
    bright.begin(startPinBright);
    delay(100);

    // memory.begin(watch, pot);
    memory.begin(watch, bright);
    delay(100);
}

void loop()
{
    watch.autoSwitcher(key);
    switchers.switcher(watch, key);

    // pot.autoBright(watch, key, timer);
    bright.autoBright(watch, key, timer);

    screen.showStartScreen(watch, key, timer);
    watch.dayReduration(key, timer);
    watch.setWatch(key, timer);

    // screen.showLampScreen(watch, switchers, timer, key, pot);
    screen.showLampScreen(watch, switchers, timer, key, bright);
    screen.showBrightScreen(bright, key, timer);

    watch.spectrumReDuration(key, timer);

    // pot.manualChangeBright(key, timer);
    // pot.changeMaxBright(key, watch, timer);
    bright.manualChangeBright(watch, key, timer);
    bright.changeMaxBright(key, watch, timer);

    key.keyCommands(timer);
    // memory.writeChanges(watch, pot, key);
    memory.writeChanges(watch, bright, key);
}
