#include "arduino.h"

class Motor {
  public:
    Motor(int pin1, int pin2, int pinPWM, int pwmChannel) {
      this->pin1 = pin1;
      this->pin2 = pin2;
      this->pinPWM = pinPWM;
      this->pwmChannel = pwmChannel;
      pinMode(pin1, OUTPUT);
      pinMode(pin2, OUTPUT);
      pinMode(pinPWM, OUTPUT);
      
      int freq = 30000;
      int resolution = 9;
      ledcSetup(this->pwmChannel, freq, resolution);
      ledcWrite(this->pwmChannel, 10);
    }
  protected:
  private:
    int pin1;
    int pin2;
    int pinPWM;
    int pwmChannel;
};