#include "Motor.h"

Motor::Motor(int pin1, int pin2, int pinPWM) {
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->pinPWM = pinPWM;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pinPWM, OUTPUT);
  
  int freq = 30000;
  int resolution = 9;

  ledcAttach(this->pinPWM, freq, resolution);
}

void Motor::setSpeed(int speed) {
  if (speed < 0) { // counterclockwise
    digitalWrite(this->pin1, HIGH);
    digitalWrite(this->pin2, LOW);
  } else { // clockwise
    digitalWrite(this->pin1, LOW);
    digitalWrite(this->pin2, HIGH);
  }
  ledcWrite(this->pinPWM, abs(speed));
}

int Motor::getSpeed() {
  return 0;
}
