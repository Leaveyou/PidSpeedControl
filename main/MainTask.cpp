#include "MainTask.h"
#include "EncoderInputPin.cpp"

MainTask::MainTask()
    : inputSteering(1000, 2000),
      inputThrottle(1000, 2000),
      inputButton(1000, 2000),
      inputSwitch(1000, 2000),
      inputKnob1(1000, 2000),
      inputKnob2(1000, 2000),
      mpu(Wire) {

    Serial.begin(115200);

    Encoder *leftEncoder = new Encoder(new EncoderInputPin<ENCODER_PIN_A1>, new EncoderInputPin<ENCODER_PIN_A2>);
    Encoder *rightEncoder = new Encoder(new EncoderInputPin<ENCODER_PIN_A1>, new EncoderInputPin<ENCODER_PIN_A2>);

    this->motorA = new Motor(MOTOR_A_1, MOTOR_A_2, MOTOR_A_PWM, leftEncoder);
    this->motorB = new Motor(MOTOR_B_1, MOTOR_B_2, MOTOR_B_PWM, rightEncoder);

    inputSteering.attach();
    inputThrottle.attach();
    inputButton.attach();
    inputSwitch.attach();
    inputKnob1.attach();
    inputKnob2.attach();

    Wire.begin();
    byte status = mpu.begin();

    if (status != 0) {
        Serial.println("Could not connect to MPU6050 gyroscope. Exiting.");
        while (1) {}
    }

    mpu.calcOffsets(true, true);  // gyro and accelero
};


void MainTask::run() {
    mpu.update();

    motorA->setDesiredSpeed(inputThrottle.map(-256, 256) + inputSteering.map(-256, 256));
    motorB->setDesiredSpeed(inputThrottle.map(-256, 256) - inputSteering.map(-256, 256));
    Serial.print("MAX:1200");


    {
        //Serial.print(",inputSteering:");
        //Serial.print(inputSteering.map(-256, 256));
        //Serial.print(",inputThrottle:");
        //Serial.print(inputThrottle.map(-256, 256));
        //Serial.print(",inputButton:");
        //Serial.print(inputButton.map(-100, 100));
        //Serial.print(",inputSwitch: ");
        //Serial.print(inputSwitch.map(-100, 100));
        //Serial.print(",inputKnob1:");
        //Serial.print(inputKnob1.map(-100, 100));
        //Serial.print(",inputKnob2:");
        //Serial.print(inputKnob2.map(-100, 100));
        //   Serial.print(",leftEncoder:");
        //   Serial.print(leftEncoder.sample());
        //   Serial.print(",rightEncoder:");
        //   Serial.print(rightEncoder.sample());

        // Serial.print( ",getAccX:");
        // Serial.print( mpu.getAccX());
        // Serial.print(",getAccY:");
        // Serial.print(mpu.getAccY());
        // Serial.print( ",getAccZ:");
        // Serial.print( mpu.getAccZ());

        // Serial.print( ",getGyroX:");
        // Serial.print( mpu.getGyroX());
        // Serial.print(",getGyroY:");
        // Serial.print(mpu.getGyroY());
        // Serial.print( ",getGyroZ:");
        // Serial.print( mpu.getGyroZ());

        // Serial.print( ",getAccAngleX:");
        // Serial.print( mpu.getAccAngleX());
        // Serial.print( ",getAccAngleY:");
        // Serial.print( mpu.getAccAngleY());

        // Serial.print( ",getAngleX:");
        // Serial.print( mpu.getAngleX());
        // Serial.print( ",getAngleY:");
        // Serial.print( mpu.getAngleY());
        // Serial.print( ",getAngleZ:");
        // Serial.print( mpu.getAngleZ());

        Serial.println("");
    }
};
