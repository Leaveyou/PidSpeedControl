#pragma once

#include "esp32-hal-gpio.h"
#include "driver/ledc.h"
#include "Encoder.h"

class Motor {
  public:
    Motor(int pin1, int pin2, int pinPWM, Encoder *encoder);
    void setDesiredSpeed(int speed);
    int getSpeed();

  protected:

  private:
    int pin1;
    int pin2;
    int pinPWM;
    Encoder *encoder;
};
