#pragma once
#include "Subscriber.h"

class Subscriber;
class Publisher {
  protected: 
  public:
    Subscriber *subscribers[3];
    void attachTo(Subscriber *subscriber);
};