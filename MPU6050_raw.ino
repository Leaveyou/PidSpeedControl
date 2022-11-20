#include "Encoder.cpp"
#include "Motor.cpp"
#include <ServoInput.h>
#include "EncoderInputPin.cpp"

#include "Wire.h"
#include <MPU6050_light.h>

#define SAMPLING_RATE 10

// encoder pins
#define ENCODER_PIN_A1 19
#define ENCODER_PIN_A2 23
#define ENCODER_PIN_B1 5
#define ENCODER_PIN_B2 17

// Motor A pins
#define MOTOR_A_1    2
#define MOTOR_A_2   16
#define MOTOR_A_PWM 18

// motor B pins
#define MOTOR_B_1   33
#define MOTOR_B_2   32
#define MOTOR_B_PWM 25

// controller channel pins
#define CTLR_CH1 36
#define CTLR_CH2 39
#define CTLR_CH3 34
#define CTLR_CH4 35
#define CTLR_CH5 14
#define CTLR_CH6 13


Encoder leftEncoder(new EncoderInputPin<ENCODER_PIN_A1>, new EncoderInputPin<ENCODER_PIN_A2>);
Encoder rightEncoder(new EncoderInputPin<ENCODER_PIN_B1>, new EncoderInputPin<ENCODER_PIN_B2>);

ServoInputPin<CTLR_CH1> inputSteering(1000, 2000);
ServoInputPin<CTLR_CH2> inputThrottle(1000, 2000);
// ServoInputPin<CTLR_CH3> inputButton(1000, 2000);
// ServoInputPin<CTLR_CH4> inputSwitch(1000, 2000);
// ServoInputPin<CTLR_CH5> inputKnob1(1000, 2000);
// ServoInputPin<CTLR_CH6> inputKnob2(1000, 2000);

Motor *motorA;
Motor *motorB;

hw_timer_t * timer = NULL;

MPU6050 mpu(Wire);

/**
 * Function is run with SAMPLING_RATE frequency
 */
void IRAM_ATTR periodicInterrupt()
{
  //mpu.update();

  motorA->setSpeed(inputThrottle.map(-256, 256) + inputSteering.map(-256, 256));
  motorB->setSpeed(inputThrottle.map(-256, 256) - inputSteering.map(-256, 256));
  Serial.print(",MAX:1200");
  //int throttlePercent = throttle.map(-100, 100);  // remap to a percentage both forward and reverse
  // Serial.print(",inputSteering:");
	// Serial.print(inputSteering.map(-256, 256));
  // Serial.print(",inputThrottle:");
	// Serial.print(inputThrottle.map(-256, 256));
  // Serial.print(",inputButton:");
	// Serial.print(inputButton..map(-100, 100));
  // Serial.print(",inputSwitch: ");
	// Serial.print(inputSwitch.map(-100, 100));
  // Serial.print(",inputKnob1:");
	// Serial.print(inputKnob1.map(-100, 100));
  // Serial.print(",inputKnob2:");
	// Serial.print(inputKnob2.map(-100, 100));
  // Serial.print( ",leftEncoder:");
  // Serial.print( leftEncoder.sample());
  // Serial.print( ",rightEncoder:");
  // Serial.print( rightEncoder.sample());

  Serial.println("");
}

void setupInterrupt() {
  timer = timerBegin(0, (uint16_t)80000, true); // 1kHz frequency (80MHz / X)
  timerAttachInterrupt(timer, &periodicInterrupt, true);
  unsigned int intervalCycles = 10000/SAMPLING_RATE;
  timerAlarmWrite(timer, intervalCycles, true);
  timerAlarmEnable(timer);
}

void setup() {
  // serial needed just for development
  Serial.begin(1000000);

  motorA = new Motor(MOTOR_A_1, MOTOR_A_2, MOTOR_A_PWM, 0);
  motorB = new Motor(MOTOR_B_1, MOTOR_B_2, MOTOR_B_PWM, 1);

  while (!ServoInput.available()) {  // wait for all signals to be ready
		Serial.println("Waiting for servo signals...");
		delay(500);
	}

  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(true,true); // gyro and accelero
  Serial.println("Done!\n");
  
  setupInterrupt();
}

void loop() {
  
}
