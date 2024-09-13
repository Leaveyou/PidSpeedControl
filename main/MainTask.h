#pragma once

#include "config.h"
#include "Task.h"
#include "Motor.h"
#include "Encoder.h"
#include <ServoInput.h>
#include "Wire.h"
#include <MPU6050_light.h>

class MainTask: public Task {
public:
  MainTask();
  void run() override;

private:
  Encoder leftEncoder;
  Encoder rightEncoder;

  ServoInputPin<CTLR_CH1> inputSteering;
  ServoInputPin<CTLR_CH2> inputThrottle;
  ServoInputPin<CTLR_CH3> inputButton;
  ServoInputPin<CTLR_CH4> inputSwitch;
  ServoInputPin<CTLR_CH5> inputKnob1;
  ServoInputPin<CTLR_CH6> inputKnob2;

  Motor *motorA;
  Motor *motorB;

  MPU6050 mpu;
};