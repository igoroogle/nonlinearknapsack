#ifndef NONLINEARKNAPSACK_SOLVEMMDPHYBRIDRANDOM_H
#define NONLINEARKNAPSACK_SOLVEMMDPHYBRIDRANDOM_H


#include "SolveMMDPHybridHeuristicBoth.h"

class SolveMMDPHybridHeuristicRandom : public SolveMMDPHybridHeuristicBoth {
public:
    explicit SolveMMDPHybridHeuristicRandom(const InputData& inputData);
    void solve() override;
};


#endif //NONLINEARKNAPSACK_SOLVEMMDPHYBRIDRANDOM_H
