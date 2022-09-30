#pragma once
#include "arduino.h"
#include "Publisher.h"
class Pin  {

protected:

  //static void notify(int pin_number);
  
private:
  // int pin_number;
  // bool state;
  //void notify();

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
  virtual bool getState() = 0;
  virtual int getPinNumber() = 0;
};