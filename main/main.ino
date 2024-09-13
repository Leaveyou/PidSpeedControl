
#include "config.h"
#include "PeriodicRunner.h"
#include "Task.h"

PeriodicRunner periodicRunner(SAMPLING_RATE);

void setup() {
  MainTask* mainTask = new MainTask();
  periodicRunner.appendTask(mainTask);
}

void loop() {
  periodicRunner.runIfDue();
}
