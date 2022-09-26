#include "esp32-hal-gpio.h"
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

      ledcAttachPin(this->pinPWM, this->pwmChannel);

    }
    void setSpeed(int speed){
      if (speed < 0) {
        digitalWrite(this->pin1, HIGH);
        digitalWrite(this->pin2, LOW);
      } else {
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, HIGH);
      }
      ledcWrite(this->pwmChannel, abs(speed));
    }
  protected:
  private:
    int pin1;
    int pin2;
    int pinPWM;
    int pwmChannel;
};