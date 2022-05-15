#ifndef NONLINEARKNAPSACK_TIMER_H
#define NONLINEARKNAPSACK_TIMER_H

#include <chrono>

class Timer {
 public:
    Timer();
    ~Timer();
 private:
    clock_t start, end;
};


#endif //NONLINEARKNAPSACK_TIMER_H
