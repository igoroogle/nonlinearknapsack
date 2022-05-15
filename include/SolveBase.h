#ifndef NONLINEARKNAPSACK_SOLVEBASE_H
#define NONLINEARKNAPSACK_SOLVEBASE_H

#include "InOutData.h"

class SolveBase {
public:
    explicit SolveBase(const InputData& inputData);
    virtual void solve() = 0;
    InputData getInputData();
    OutputData getOutputData();
protected:
    InputData inputData;
    OutputData outputData;
    static bool isCorrectData(InputData inputData, const OutputData& outputData);
};


#endif //NONLINEARKNAPSACK_SOLVEBASE_H
