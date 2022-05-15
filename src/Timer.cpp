#include "Timer.h"
#include <iostream>
#include <iomanip>

Timer::Timer() {
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "DURATION " << std::fixed << std::setprecision(2) << duration.count() * 1000.0 << " miliseconds\n";
    std::cout << std::setprecision(25);
    std::cout.unsetf(std::ios::fixed);
}