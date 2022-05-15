#include "Timer.h"
#include <iostream>
#include <iomanip>

Timer::Timer() {
    start = clock();
}

Timer::~Timer() {
    end = clock();
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "DURATION " << std::fixed << std::setprecision(2) <<             duration * 1000.0 << " miliseconds\n";
    std::cout << std::setprecision(25);
    std::cout.unsetf(std::ios::fixed);
}