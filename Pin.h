#pragma once
#include "arduino.h"
#include "Publisher.h"
class Pin : public Publisher {

protected:

private:
  int pin_number;
  bool state;
  void notify();

public:

  void updateState();
  Subscriber *subscribers[3];
  int existent_subscribers = 0;

  Pin(int pin_number);
  void change();

  void attachTo(Subscriber *subscriber);
  bool getState();
  int getPinNumber();
};