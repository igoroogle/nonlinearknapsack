#ifndef NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICMIN_H
#define NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICMIN_H

#include "SolveMMDPHybridHeuristicSum.h"

class SolveMMDPHybridHeuristicMin : public SolveMMDP {
public:
    explicit SolveMMDPHybridHeuristicMin(const InputData& inputData);
    void solve() override;
protected:
    TypeData lowerBound;
    std::vector<std::vector<long double>> pHeuristic;
    void precalcHeuristic();

    bool isFathoming(int n, int k, int p);
    bool isFathomingAbsolute(TypeData base, int n, int p);
};


#endif //NONLINEARKNAPSACK_SOLVEMMDPHYBRIDHEURISTICMIN_H
