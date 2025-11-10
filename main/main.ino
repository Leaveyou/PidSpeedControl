#include "config.h"
#include "PeriodicRunner.h"
#include "Task.h"

PeriodicRunner periodicRunner(RUNNER_FREQ);

void setup() {
    MainTask* mainTask = new MainTask();
    periodicRunner.appendTask(mainTask);
}

void loop() {
    periodicRunner.runIfDue();
}
