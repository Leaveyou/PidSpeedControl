#pragma once

#include "Task.h"
#include "MainTask.h"
#include <vector>

class PeriodicRunner {
  public:
    inline static volatile bool run_interrupt = false;
    PeriodicRunner(int frequency);
    void runIfDue();
    static void timerInterrupt();
    void appendTask(Task* task);

  private:
    std::vector<Task*> tasks;
    void run();
    void setupInterrupt(int frequency);
};
