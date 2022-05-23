#ifndef NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICBOTH_H
#define NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICBOTH_H

#include "SolveMMDP.h"

class SolveMMDPHybridHeuristicBoth : public SolveMMDP {
public:
    explicit SolveMMDPHybridHeuristicBoth(const InputData& inputData);
    void solve() override;
protected:
    TypeData lowerBound;
    Vector sumR;
    std::vector<std::vector<long double>> pHeuristic;
    void precalcHeuristic();
    bool isFathomingSum(int n, int k, int p);
    bool isFathomingAbsoluteSum(TypeData base, int n);
    bool isFathomingMin(int n, int k, int p);
    bool isFathomingAbsoluteMin(TypeData base, int n, int p);
};


#endif //NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICBOTH_H
