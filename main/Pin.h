#pragma once
#include "Subscriber.h"

class Pin  {
public:
  virtual void attachTo(Subscriber *subscriber) = 0;
  virtual bool getState() = 0;
  virtual int getPinNumber() = 0;
};
