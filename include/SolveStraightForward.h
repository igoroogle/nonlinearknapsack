#ifndef NONLINEARKNAPSACK_SOLVESTRAIGHTFORWARD_H
#define NONLINEARKNAPSACK_SOLVESTRAIGHTFORWARD_H

#include "SolveBase.h"


class SolveStraightForward : public SolveBase {
public:
    explicit SolveStraightForward(const InputData& inputData);
    void solve() override;
private:
    void rec(int curInd, OutputData& curData, OutputData& bestData);
};


#endif //NONLINEARKNAPSACK_SOLVESTRAIGHTFORWARD_H
