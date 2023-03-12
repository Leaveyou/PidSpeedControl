#pragma once

#include "Pin.h"

class Encoder : public Subscriber {
private:
  Pin* first_pin;
  Pin* second_pin;
  int acumulator;

public:
  Encoder(Pin* first_pin, Pin* second_pin);
  int sample();
  void update(int pin_number);
  bool isClockwiseTransition(int pin_number);
};