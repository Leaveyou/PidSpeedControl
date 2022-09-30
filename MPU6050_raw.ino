#include "Encoder.h"
#include "EncoderPrim.cpp"
#include "Pin.h"
#include "Motor.cpp"
#include <ServoInput.h>
#include "EncoderInputPin.cpp"

#define ENCODER_PIN_A1 19
#define ENCODER_PIN_A2 23
#define ENCODER_PIN_B1 5
#define ENCODER_PIN_B2 17

#define MOTOR_A_1    2
#define MOTOR_A_2   16
#define MOTOR_A_PWM 18

#define MOTOR_B_1   33
#define MOTOR_B_2   32
#define MOTOR_B_PWM 25

#define CTLR_CH1 36
#define CTLR_CH2 39
#define CTLR_CH3 34
#define CTLR_CH4 35
#define CTLR_CH5 14
#define CTLR_CH6 13

#define SAMPLING_RATE 10

// Pin *pinEncA1;
// Pin *pinEncA2;
// Pin *pinEncB1;
// Pin *pinEncB2;

Motor *motorA;
Motor *motorB;

//Encoder *left_encoder;
//Encoder *right_encoder;

hw_timer_t * timer = NULL;

EncoderInputPin<12>* random_pin = new EncoderInputPin<12>;
EncoderInputPin<4>* random_pin2 = new EncoderInputPin<4> ;

EncoderPrim random_encoder(random_pin, random_pin2);

ServoInputPin<CTLR_CH1> input_steering(1000, 2000);
ServoInputPin<CTLR_CH2> input_throttle(1000, 2000);
ServoInputPin<CTLR_CH3> input_button(1000, 2000);
ServoInputPin<CTLR_CH4> input_switch(1000, 2000);
ServoInputPin<CTLR_CH5> input_knob_1(1000, 2000);
ServoInputPin<CTLR_CH6> input_knob_2(1000, 2000);



// Function is run with SAMPLING_RATE frequency
void IRAM_ATTR loopTimerInterrupt() {

  motorA->setSpeed(input_throttle.map(-256, 256) + input_steering.map(-256, 256));
  motorB->setSpeed(input_throttle.map(-256, 256) - input_steering.map(-256, 256));
  //int throttlePercent = throttle.map(-100, 100);  // remap to a percentage both forward and reverse

  Serial.print(",input_steering:");
	Serial.print(input_steering.map(-256, 256));
  Serial.print(",input_throttle:");
	Serial.print(input_throttle.map(-256, 256));
  // Serial.print(",input_button:");
	// Serial.print(input_button..map(-100, 100));
  // Serial.print(",input_switch: ");
	// Serial.print(input_switch.map(-100, 100));
  // Serial.print(",input_knob_1:");
	// Serial.print(input_knob_1.map(-100, 100));
  // Serial.print(",input_knob_2:");
	// Serial.print(input_knob_2.map(-100, 100));
  //Serial.print( ",left_encoder:");
  //Serial.print( left_encoder->sample());
  //Serial.print( ",right_encoder:");
  //Serial.print( right_encoder->sample());
  Serial.println("");
}

void setupLoopTimerInterrupt() {
  timer = timerBegin(0, (uint16_t)8000, true); // 10kHz frequency (80MHz / X)
  timerAttachInterrupt(timer, &loopTimerInterrupt, true);
  unsigned int intervalCycles = 10000/SAMPLING_RATE;
  timerAlarmWrite(timer, intervalCycles, true);
  timerAlarmEnable(timer);
}

void setup() {
  // serial needed just for development
  Serial.begin(921600);

  // pinEncA1 = new Pin(ENCODER_PIN_A1);
  // pinEncA2 = new Pin(ENCODER_PIN_A2);
  // pinEncB1 = new Pin(ENCODER_PIN_B1);
  // pinEncB2 = new Pin(ENCODER_PIN_B2);

  // left_encoder = new Encoder(pinEncA1, pinEncA2);
  // right_encoder = new Encoder(pinEncB1, pinEncB2);

  // attachInterrupt(ENCODER_PIN_A1, [] {pinEncA1->change(); },CHANGE);
  // attachInterrupt(ENCODER_PIN_A2, [] {pinEncA2->change(); },CHANGE);
  // attachInterrupt(ENCODER_PIN_B1, [] {pinEncB1->change(); },CHANGE);
  // attachInterrupt(ENCODER_PIN_B2, [] {pinEncB2->change(); },CHANGE);

  motorA = new Motor(MOTOR_A_1, MOTOR_A_2, MOTOR_A_PWM, 0);
  motorB = new Motor(MOTOR_B_1, MOTOR_B_2, MOTOR_B_PWM, 1);

  //ctlr_ch_1 = new Pin(CTLR_CH1);
  //ctlr_ch_2 = new Pin(CTLR_THROTTLE);
  //ctlr_ch_3 = new Pin(CTLR_CH3);
  //ctlr_ch_4 = new Pin(CTLR_CH4);
  //ctlr_ch_5 = new Pin(CTLR_CH5);
  //ctlr_ch_6 = new Pin(CTLR_CH6);
//
  //attachInterrupt(CTLR_CH1, [] {ctlr_ch_1->change(); },CHANGE);
  //attachInterrupt(CTLR_THROTTLE, [] {ctlr_ch_2->change(); },CHANGE);
  //attachInterrupt(CTLR_CH3, [] {ctlr_ch_3->change(); },CHANGE);
  //attachInterrupt(CTLR_CH4, [] {ctlr_ch_4->change(); },CHANGE);
  //attachInterrupt(CTLR_CH5, [] {ctlr_ch_5->change(); },CHANGE);
  //attachInterrupt(CTLR_CH6, [] {ctlr_ch_6->change(); },CHANGE);

  


	while (!ServoInput.available()) {  // wait for all signals to be ready
		Serial.println("Waiting for servo signals...");
		delay(500);
	}

  // setupLoopTimerInterrupt();
}

void loop() {

}
