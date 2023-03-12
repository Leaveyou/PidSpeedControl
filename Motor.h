#pragma once

#include "esp32-hal-gpio.h"

class Motor {
public:
  Motor(int pin1, int pin2, int pinPWM, int pwmChannel);

  void setSpeed(int speed);

protected:
private:
  int pin1;
  int pin2;
  int pinPWM;
  int pwmChannel;
};
