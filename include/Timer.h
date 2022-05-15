#ifndef NONLINEARKNAPSACK_TIMER_H
#define NONLINEARKNAPSACK_TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
};


#endif //NONLINEARKNAPSACK_TIMER_H
