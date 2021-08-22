#include <Arduino.h>

#include <ScreenU8G2.h>
#include <Screen.h>
#include <Switchers.h>
#include <Timer.h>
#include <Watch.h>
#include <Key.h>
#include <Memory.h>
#include <Pot.h>
#include <Bright.h>

byte startPinBright = 2;

// byte startPinLamp = 11;
byte startPinLamp = 22;

// byte keyPin[] = {10, 9, 8, 7, 6, 5, 4, 3};
byte keyPin[] = {32, 34, 36, 38, 40, 42, 44, 46};

//SINGLE VERSION

String WavelengthSMD[] = {"3500k"};

String lightColor[] = {"LED"};

// DigiPot potent[] = {
//     DigiPot(2, 3, 4)};

// VERSION PEPPER
// String WavelengthSMD[] = {"3500k+6500k",
//                           "385nm+660nm+730nm+WC"};

// String lightColor[] = {"WC", "UFR"};

// DigiPot potent[] = {
//     DigiPot(2, 3, 4),
//     DigiPot(5, 6, 7)};

// SQUARE 250 Led //

// String WavelengthSMD[] = {
//     "3500k+full",
//     "3500k+full",
//     "3500k+full",
//     "660nm",
//     "6500k+full",
//     "6500k+full",
//     "6500k+full",
//     "365+385nm"};

// String lightColor[] = {"WF 1", "WF 2", "WF 3", "RED", "CF 1", "CF 2", "CF 3", "UV"};

// DigiPot potent[] = {
//     DigiPot(2, 3, 4),
//     DigiPot(5, 6, 7),
//     DigiPot(8, 9, 10),
//     DigiPot(11, 12, 13),
//     DigiPot(14, 15, 16),
//     DigiPot(17, 18, 19),
//     DigiPot(33, 35, 37),
//     DigiPot(39, 41, 43)};

// CREE Ultraviolet FarRed Red Blue //
// String WavelengthSMD[] = {"365nm+385nm", "365nm+385nm", "440nm", "440nm", "660nm", "660nm", "730nm", "730nm", "3000K"};

// String lightColor[] = {"UV 1", "UV 2", "BL 1", "BL 2", "R 1", "R 2", "FR 1", "FR 2", "CXB"};

// DigiPot potent[lampAmount] = {
//     DigiPot(2, 3, 4),
//     DigiPot(5, 6, 7),
//     DigiPot(8, 9, 10),
//     DigiPot(11, 12, 13),
//     DigiPot(14, 15, 16),
//     DigiPot(17, 18, 19),
//     DigiPot(37, 39, 41),
//     DigiPot(43, 45, 47),
//     DigiPot(31, 33, 35)};

// SpectrTEST ver. //
// String specWavelengthSMD[] = {"365nm+385nm", "440nm", "660nm", "730nm", "3000K"};
// String speclightColor[] = {"UV", "BL", "RED", "FR", "CXB"};

Watch watch;
Switchers switchers;
ScreenU8G2 screen;
// Screen screen;
Timer timer;
Key key(keyPin);
Memory memory;
// Pot pot;
Bright bright;

void setup()
{
    // Serial.begin(9600);

    // screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    // screen.display();
    // delay(500);
    // screen.clearDisplay();

    screen.begin();

    screen.setStrings(WavelengthSMD, lightColor);

    // screen.iGorLogo();
    // delay(500);

    watch.begin();
    // watch.adjust(DateTime(F(__DATE__), F(__TIME__)));

    key.begin(KB4x4, 500);

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
