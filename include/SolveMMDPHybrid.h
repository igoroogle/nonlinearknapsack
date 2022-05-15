#ifndef NONLINEARKNAPSACK_SOLVEMMDPHYBRID_H
#define NONLINEARKNAPSACK_SOLVEMMDPHYBRID_H

#include "SolveMMDP.h"

class SolveMMDPHybrid : public SolveMMDP {
public:
    SolveMMDPHybrid(const InputData& inputData);
    void solve() override;
protected:
    TypeData lowerBound;
    Vector sumR;
    //Vector pHeuristicMin;
    bool isFathoming(int n, int k, int p);
    bool isFathomingAbsolute(TypeData base, int n);
};


#endif //NONLINEARKNAPSACK_SOLVEMMDPHYBRID_H
