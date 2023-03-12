#include "PeriodicRunner.h"

PeriodicRunner::PeriodicRunner(int frequency) {
  this->setupInterrupt(frequency);
}

void PeriodicRunner::runIfDue() {
  if (run_interrupt) {
    run_interrupt = false;
    this->run();
  }
}

void PeriodicRunner::timerInterrupt() {
  run_interrupt = true;
}

void PeriodicRunner::appendTask(Task* task) {
    this->tasks.push_back(task);
}

void PeriodicRunner::run() {
  for (const auto& task : this->tasks) {
    task->run();
  }
}

void PeriodicRunner::setupInterrupt(int frequency) {
  hw_timer_t *timer = timerBegin(0, (uint16_t)80, true);
  timerAttachInterrupt(timer, &timerInterrupt, true);
  unsigned int intervalCycles = 1000000/frequency;
  timerAlarmWrite(timer, intervalCycles, true);
  timerAlarmEnable(timer);
}