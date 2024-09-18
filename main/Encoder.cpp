#include "Encoder.h"
#include "arduino.h"

Encoder::Encoder(Pin* first_pin, Pin* second_pin) {
  this->first_pin = first_pin;
  this->second_pin = second_pin;

  this->first_pin->attachTo(this);
  this->second_pin->attachTo(this);
  this->acumulator = 0;
}

int Encoder::sample() {
  int tmp = this->acumulator;
  this->acumulator = 0;
  return tmp;
}

void Encoder::update(int pin_number) {  
  int tmp = (int)this->isClockwiseTransition(pin_number)*2 - 1;
  this->acumulator += (tmp);
}

bool Encoder::isClockwiseTransition(int pin_number) {
  bool clockwise = 
    (pin_number == this->first_pin->getPinNumber()) ^
    (this->first_pin->getState() == this->second_pin->getState());
  return clockwise;
}