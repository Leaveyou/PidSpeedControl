#include "Encoder.h"
#include "Pin.h"

#define ENCODER_PIN_1 18
#define ENCODER_PIN_2 19
#define ENCODER_PIN_3 22
#define ENCODER_PIN_4 23

#define SAMPLING_RATE 1000

Pin *pin1 = new Pin(ENCODER_PIN_1);
Pin *pin2 = new Pin(ENCODER_PIN_2);
Pin *pin3 = new Pin(ENCODER_PIN_3);
Pin *pin4 = new Pin(ENCODER_PIN_4);

Encoder *encoder1;
Encoder *encoder2;

void setup() {

  Serial.begin(921600);

pin1->updateState();
pin2->updateState();
pin3->updateState();
pin4->updateState();

  encoder1 = new Encoder(pin1, pin2);
  encoder2 = new Encoder(pin3, pin4);

  attachInterrupt(ENCODER_PIN_1, [] {pin1->change(); },CHANGE);
  attachInterrupt(ENCODER_PIN_2, [] {pin2->change(); },CHANGE);
  attachInterrupt(ENCODER_PIN_3, [] {pin3->change(); },CHANGE);
  attachInterrupt(ENCODER_PIN_4, [] {pin4->change(); },CHANGE);
}

void loop() {
  delay(500);
  Serial.print( "pin1:");
  Serial.print( pin1->getState());
  Serial.print( ",pin2:");
  Serial.print( pin2->getState());
  Serial.print( ",pin3:");
  Serial.print( pin3->getState());
  Serial.print( ",pin4:");
  Serial.print( pin4->getState());
  Serial.print( ",encoder1:");
  Serial.print( encoder1->sample());
  Serial.print( ",encoder2:");
  Serial.println( encoder2->sample());
}
