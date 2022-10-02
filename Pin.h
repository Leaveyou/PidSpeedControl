#pragma once
#include "arduino.h"
#include "Subscriber.h"
class Pin  {

protected:
private:
public:

  // static int static_pin_number;
  // static Subscriber *static_subscribers[3];
  // static int static_existent_subscribers;

  // Subscriber *subscribers[3];
  // int existent_subscribers = 0;

  // Pin(int pin_number);
  // Pin();
  // void change();

  virtual void attachTo(Subscriber *subscriber) = 0;
  virtual bool IRAM_ATTR getState() = 0;
  virtual int IRAM_ATTR getPinNumber() = 0;
};