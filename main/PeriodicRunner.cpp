#include "PeriodicRunner.h"

PeriodicRunner::PeriodicRunner(int sampling_rate) {
  this->setupInterrupt(sampling_rate);
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

void PeriodicRunner::setupInterrupt(int sampling_rate) {
  int timer_frequency = 1000000;
  hw_timer_t *timer = timerBegin(timer_frequency);
  timerAttachInterrupt(timer, &timerInterrupt);
  timerAlarm(timer, timer_frequency / sampling_rate, true, 0);
}