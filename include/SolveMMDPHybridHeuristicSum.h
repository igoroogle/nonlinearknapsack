#ifndef NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICSUM_H
#define NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICSUM_H

#include "SolveMMDP.h"

class SolveMMDPHybridHeuristicSum : public SolveMMDP {
public:
    explicit SolveMMDPHybridHeuristicSum(const InputData& inputData);
    void solve() override;
protected:
    TypeData lowerBound;
    Vector sumR;
    bool isFathoming(int n, int k, int p);
    bool isFathomingAbsolute(TypeData base, int n);
    void precalcHeuristic();
};


#endif //NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICSUM_H
