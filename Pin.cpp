#include "Pin.h"
#include "arduino.h"
#include <iostream>

#include "encoder.h"

Pin::Pin(int pin_number) {
  this->pin_number = pin_number;    
}

void Pin::attachTo(Subscriber *subscriber) {
  this->subscribers[this->existent_subscribers] = subscriber;
  this->existent_subscribers++;
}

void Pin::change() {
  this->updateState();
  this->notify();
}

void Pin::notify()
{
  for(int i = 0; i < this->existent_subscribers; i++) {    
      this->subscribers[i]->update(this->pin_number);
  }
}

void Pin::updateState() {
  this->state = (bool)digitalRead(this->pin_number);
}

bool Pin::getState() {
  return this->state;
}

int Pin::getPinNumber() {
  return this->pin_number;
}

