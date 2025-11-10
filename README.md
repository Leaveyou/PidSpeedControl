# PidSpeedControl

2 wheeled - self balancing robot

Communication is done with baud rate `115200`

Dependencies:

* esp32 board by Espressif Systems - v3.0.4
* ServoInput by David Madisson - v2.0.0
* MPU6050_light by rfetick - v1.2.1 - this either has issues or my board is damaged, but it intermitently refuses to work after reset. 

![Wiring diagram](docs/wiring.png)

# Build progress

I disabled the accelerometer due to  it being unreliable. 

An interrupt detects state changes from the encoders, interprets  rotation direction and accumulates rotation progress

Another timer interrupt meant to control the robot reads the accumulated pulses, resets them to 0 and returns them to be used to speed calculations

Robot Speed is proportional to the number of accumulated pulses, times the sampling frequency

THe problem is that the speed needs to be stored somewhere as it cannot be re-calculated; The calculation sampling the pulses resets them to 0. This is so that `getSpeed()` needs to be separate fron `calcSpeed()`

There might be to possible contexts:
* Sampling context
* Any other asynchronous operations

Current risk is that the system makes assumptions about the sampling: that it's executed at precise moments without fail. This is of course true due to the timer interrupts, but there is nothing preventing the calling of the sampling function out of scope.

It is important to model the code in such a way that the control processes are separate from the ones not changing the internal state.

In the end it is possible that all of the processes are time sensitive and tied in some way to the sampling

## Time sensitive:

# Encoder sampling
# Speed calculation
# PID feedback using the samples and the control input
# interpolating the input for smoothing of the commands

## Potentially separate context

Reading the input might be separate because it does not change as often as the PID control parameter. However there is no reason to NOT have it run just as often other than performance

Generating graphical data for PID tuning and debugging

Changing the sample rate might necessitate adjusting PID unless PID is based on a parameter sample rate independent. THis can be the actual impulses per second, which may be obtained by multiplying the sample rate by the accumulated pulses

