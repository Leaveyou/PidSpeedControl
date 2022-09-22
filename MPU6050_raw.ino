#include "Encoder.h"
#include "Pin.h"
#include "Motor.cpp"

#define ENCODER_PIN_A1 19
#define ENCODER_PIN_A2 23
#define ENCODER_PIN_B1 17
#define ENCODER_PIN_B2 5

#define MOTOR_A_1    2
#define MOTOR_A_2   16
#define MOTOR_A_PWM 18

#define MOTOR_B_1   32
#define MOTOR_B_2   33
#define MOTOR_B_PWM 25

#define SAMPLING_RATE 100

Pin *pin1;
Pin *pin2;
Pin *pin3;
Pin *pin4;

Motor *motorA;
Motor *motorB;

Encoder *left_encoder;
Encoder *right_encoder;

hw_timer_t * timer = NULL;

// Function is run with SAMPLING_RATE frequency
void IRAM_ATTR loopTimerInterrupt() {
  Serial.print( "left_encoder:");
  Serial.print( left_encoder->sample());
  Serial.print( ",right_encoder:");
  Serial.println( right_encoder->sample());
}

void setupLoopTimerInterrupt() {
  timer = timerBegin(0, 8000, true);                  // Begin timer with 10 kHz frequency (80MHz/8kHz)
  timerAttachInterrupt(timer, &loopTimerInterrupt, true);
  unsigned int intervalCycles = 10000/SAMPLING_RATE;
  timerAlarmWrite(timer, intervalCycles, true);
  timerAlarmEnable(timer);
}

void setup() {
  // serial needed just for development
  Serial.begin(921600);

  pin1 = new Pin(ENCODER_PIN_A1);
  pin2 = new Pin(ENCODER_PIN_A2);
  pin3 = new Pin(ENCODER_PIN_B1);
  pin4 = new Pin(ENCODER_PIN_B2);

  left_encoder = new Encoder(pin1, pin2);
  right_encoder = new Encoder(pin3, pin4);

  attachInterrupt(ENCODER_PIN_A1, [] {pin1->change(); },CHANGE);
  attachInterrupt(ENCODER_PIN_A2, [] {pin2->change(); },CHANGE);
  attachInterrupt(ENCODER_PIN_B1, [] {pin3->change(); },CHANGE);
  attachInterrupt(ENCODER_PIN_B2, [] {pin4->change(); },CHANGE);

  motorA = new Motor(MOTOR_A_1, MOTOR_A_2, MOTOR_A_PWM, 0);
  motorB = new Motor(MOTOR_B_1, MOTOR_B_2, MOTOR_B_PWM, 1);

  setupLoopTimerInterrupt();


}

void loop() {
  motorA->setSpeed(30);
}
