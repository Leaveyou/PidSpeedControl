#include "config.h"
#include "PeriodicRunner.h"
#include "Task.h"

PeriodicRunner periodicRunner(RUNNER_FREQ);

void setup() {
    Serial.begin(115200);

    MainTask* mainTask = new MainTask();
    periodicRunner.appendTask(mainTask);
}
 
void loop() {
    periodicRunner.runIfDue();
}
