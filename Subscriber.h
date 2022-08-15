#pragma once
#include "Publisher.h"

class Subscriber
{
  public:
  virtual void update(int pin_number);
};