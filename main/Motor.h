#pragma once

#include "esp32-hal-gpio.h"
#include "driver/ledc.h"

class Motor {
public:
  Motor(int pin1, int pin2, int pinPWM, ledc_channel_t pwmChannel);

  void setSpeed(int speed);

protected:
private:
  int pin1;
  int pin2;
  int pinPWM;
  ledc_channel_t pwmChannel;
};
