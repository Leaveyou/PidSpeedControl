#pragma once
#include "Subscriber.h"

class Subscriber;
class Publisher {
  protected: 
  public:
    Subscriber *subscribers[3];
    virtual void attachTo(Subscriber *subscriber);
};