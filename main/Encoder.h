#pragma once

#include "Pin.h"

class Encoder : public Subscriber {
  private:
    Pin* first_pin;
    Pin* second_pin;
    int acumulator;
    bool isClockwiseTransition(int pin_number);

  public:
    Encoder(Pin* first_pin, Pin* second_pin);
    int sample();
    void getUpdated(int pin_number);
};
