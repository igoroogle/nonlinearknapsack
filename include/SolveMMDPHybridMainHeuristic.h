//
// Created by Игорь Глушков on 16.05.2022.
//

#ifndef NONLINEARKNAPSACK_SOLVEMMDPHYBRIDMAINHEURISTIC_H
#define NONLINEARKNAPSACK_SOLVEMMDPHYBRIDMAINHEURISTIC_H

#include "SolveMMDPHybrid.h"

class SolveMMDPHybridMainHeuristic : public SolveMMDPHybrid {
public:
    explicit SolveMMDPHybridMainHeuristic(const InputData& inputData);
    void solve() override;
protected:
    Matrix pHeuristic;
    void precalcHeuristic();
    bool isFathomingMainHeuristic(int n, int k, int p);
    bool isFathomingAbsoluteMainHeuristic(TypeData base, int n, int p);
    void restoreX(int p, Vector& x);
};


#endif //NONLINEARKNAPSACK_SOLVEMMDPHYBRIDMAINHEURISTIC_H
