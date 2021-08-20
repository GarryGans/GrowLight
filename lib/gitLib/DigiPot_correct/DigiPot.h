/*
 * DigiPotX9Cxxx.cpp - Arduino library for managing digital potentiometers X9Cxxx (xxx = 102,103,104,503).
 * By Timo Fager, Jul 29, 2011.
 * Released to public domain.
 **/

// With my correct
// Deleted microDelay!!!!!!!

#ifndef DIGIPOT_H
#define DIGIPOT_H

#include "Arduino.h"

#define DIGIPOT_UP HIGH
#define DIGIPOT_DOWN LOW
#define DIGIPOT_MAX_AMOUNT 99
#define DIGIPOT_UNKNOWN 255

class DigiPot
{

private:
  uint8_t inc;
  uint8_t ud;
  uint8_t cs;
  uint8_t currentValue;

public:
  void increase(uint8_t amount);
  void decrease(uint8_t amount);
  void change(uint8_t direction, uint8_t amount);
  void set(uint8_t value);
  uint8_t get();
  void reset();

  DigiPot();
  ~DigiPot();

  DigiPot(uint8_t inc, uint8_t ud, uint8_t cs);
};

#endif
