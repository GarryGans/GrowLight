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

#define holdSpeed 50
#define holdDelay 500

// byte startPinLamp = 11;
byte startPinLamp = 22;
byte startPinBright = 2; //198 ~ 24 QuantumBoard 0.30 ~ 2.70

// byte keyPin[] = {10, 9, 8, 7, 6, 5, 4, 3};
byte keyPin[] = {32, 34, 36, 38, 40, 42, 44, 46};

//SINGLE VERSION
// String WavelengthSMD[] = {"3500k+UV+RED+FR"};

// String lightColor[] = {"QB"};

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

String WavelengthSMD[] = {
    "3500k+full",
    "3500k+full",
    "3500k+full",
    "660nm",
    "6500k+full",
    "6500k+full",
    "6500k+full",
    "365+385nm"};

String lightColor[] = {"WF 1", "WF 2", "WF 3", "RED", "CF 1", "CF 2", "CF 3", "UV"};

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

// DigiPot potent[] = {
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

// byte Amount = sizeof(lightColor) / sizeof(String);