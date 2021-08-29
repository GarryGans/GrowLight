#include <main.h>


Timer timer(Amount);
Key key(keyPin, Amount);
Watch watch(Amount);
Switchers switchers(Amount);
Bright bright(Amount);
// Pot pot(Amount);
Memory memory(Amount);
// ScreenU8G2 screen(WavelengthSMD, lightColor, Amount);
Screen screen(WavelengthSMD, lightColor, Amount);

void setup()
{
    // Serial.begin(9600);

    screen.begin();

    screen.iGorLogo();
    delay(500);

    watch.begin();
    // watch.adjust(DateTime(F(__DATE__), F(__TIME__)));

    key.begin(KB4x4, 500, 200);

    // pot.setPot(potent);
    // pot.resetAllPots();
    bright.begin(startPinBright);

    switchers.begin(startPinLamp);

    // memory.begin(watch, pot);
    memory.begin(watch, bright);

    delay(500);
}

void loop()
{
    key.read();

    key.manualSwitchLight();
    watch.autoSwitcher(key);
    switchers.switcher(watch, key);

    // pot.autoBright(watch, key, timer);
    bright.autoBright(watch, key, timer);

    screen.showStartScreen(watch, key, timer);
    watch.dayReduration(key, timer);
    watch.setWatch(key, timer);

    // screen.showLampScreen(watch, switchers, timer, key, pot);
    screen.showLampScreen(watch, switchers, timer, key, bright);

    key.autoScreenMove(timer);
    key.manualChangeScreen(timer);
    watch.spectrumReDuration(key, timer);

    // pot.manualChangeBright(key, timer);
    // pot.changeMaxBright(key, watch, timer);
    bright.manualChangeBright(key, timer);
    bright.changeMaxBright(key, watch, timer);

    // memory.writeChanges(watch, pot, key);
    memory.writeChanges(watch, bright, key);

    key.home();
}
