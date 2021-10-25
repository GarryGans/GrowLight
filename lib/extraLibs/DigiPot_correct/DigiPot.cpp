/* 
 * DigiPotX9Cxxx.cpp - Arduino library for managing digital potentiometers X9Cxxx (xxx = 102,103,104,503).
 * By Timo Fager, Jul 29, 2011.
 * Released to public domain.
 **/

// With my correct
// Deleted microDelay!!!!!!!

#include "Arduino.h"
#include "DigiPot.h"

DigiPot::DigiPot()
{
}

DigiPot::~DigiPot()
{
}

DigiPot::DigiPot(uint8_t inc, uint8_t ud, uint8_t cs)
{
  this->inc = inc;
  this->ud = ud;
  this->cs = cs;
  this->currentValue = DIGIPOT_UNKNOWN;

  pinMode(inc, OUTPUT);
  pinMode(ud, OUTPUT);
  pinMode(cs, OUTPUT);
  digitalWrite(cs, HIGH);
}

void DigiPot::reset()
{
  // change down maximum number of times to ensure the value is 0
  decrease(DIGIPOT_MAX_AMOUNT);
  currentValue = 0;
}

void DigiPot::set(uint8_t value)
{
  value = constrain(value, 0, DIGIPOT_MAX_AMOUNT);
  if (currentValue == DIGIPOT_UNKNOWN)
    reset();
  if (currentValue > value)
  {
    change(DIGIPOT_DOWN, currentValue - value);
  }
  else if (currentValue < value)
  {
    change(DIGIPOT_UP, value - currentValue);
  }
}

uint8_t DigiPot::get()
{
  return currentValue;
}

void DigiPot::increase(uint8_t amount)
{
  amount = constrain(amount, 0, DIGIPOT_MAX_AMOUNT);
  change(DIGIPOT_UP, amount);
}

void DigiPot::decrease(uint8_t amount)
{
  amount = constrain(amount, 0, DIGIPOT_MAX_AMOUNT);
  change(DIGIPOT_DOWN, amount);
}

void DigiPot::change(uint8_t direction, uint8_t amount)
{
  amount = constrain(amount, 0, DIGIPOT_MAX_AMOUNT);
  digitalWrite(ud, direction);
  digitalWrite(inc, HIGH);
  digitalWrite(cs, LOW);

  for (uint8_t i = 0; i < amount; i++)
  {
    digitalWrite(inc, LOW);
    digitalWrite(inc, HIGH);
    if (currentValue != DIGIPOT_UNKNOWN)
    {
      currentValue += (direction == DIGIPOT_UP ? 1 : -1);
      currentValue = constrain(currentValue, 0, DIGIPOT_MAX_AMOUNT);
    }
  }
  digitalWrite(cs, HIGH);
}
