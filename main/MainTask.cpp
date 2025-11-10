#include "MainTask.h"
#include "EncoderInputPin.h"

MainTask::MainTask()
    : inputSteering(1000, 2000)
      ,inputThrottle(1000, 2000)
      ,inputButton(1000, 2000)
      ,inputSwitch(1000, 2000)
      ,inputKnob1(1000, 2000)
      ,inputKnob2(1000, 2000)
      // ,accelerometer(Wire) 
      {

    Serial.begin(115200);

    Encoder *leftEncoder = new Encoder(new EncoderInputPin<ENCODER_PIN_A1>, new EncoderInputPin<ENCODER_PIN_A2>);
    Encoder *rightEncoder = new Encoder(new EncoderInputPin<ENCODER_PIN_A1>, new EncoderInputPin<ENCODER_PIN_A2>);

    this->leftMotor = new Motor(MOTOR_A_1, MOTOR_A_2, MOTOR_A_PWM, leftEncoder);
    this->rightMotor = new Motor(MOTOR_B_1, MOTOR_B_2, MOTOR_B_PWM, rightEncoder);

    inputSteering.attach();
    inputThrottle.attach();
    inputButton.attach();
    inputSwitch.attach();
    inputKnob1.attach();
    inputKnob2.attach();

	while (!ServoInput.available()) {  // wait for all signals to be ready
		Serial.println("\nWaiting for servo signals...");
		delay(1000);
	}
    
	// Serial.println("Servo signal found. Initializing accelerometer.");

    Wire.begin();


	Serial.println("Accelerometer is temporarily disabled due to it not booting up reliably. Either hardware or software issue.");
// delay(100);

    //byte status = accelerometer.begin();

    //if (status != 0) {
    //    Serial.println("Could not connect to MPU6050 accelerometer. Exiting.");
    //    delay(200);
    //    while (1) {}
    // }

    //Serial.println("Accelerometer initialized. Calculating offsets...");

    //accelerometer.calcOffsets(true, true);  // gyro and accelero
};

void MainTask::run() {
    // accelerometer.update();


    // pseudocode:

    float setPoint = 0; // target value
    float processVariable = 0; // measured value

    float inputValue = inputThrottle.map(-256, 256) + inputSteering.map(-256, 256);
    float controllerOutput = inputValue;



leftMotor->setDesiredSpeed(controllerOutput);

    // old demo
    // leftMotor->setDesiredSpeed(inputThrottle.map(-256, 256) + inputSteering.map(-256, 256));
    // rightMotor->setDesiredSpeed(inputThrottle.map(-256, 256) - inputSteering.map(-256, 256));

    // Serial.print("MAX:1200");

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

        // Serial.println("");
    }
};
