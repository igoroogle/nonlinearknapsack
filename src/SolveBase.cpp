#include "SolveBase.h"

SolveBase::SolveBase(const InputData& inputData) {
    this->inputData = inputData;
}

InputData SolveBase::getInputData() {
    return inputData;
}

OutputData SolveBase::getOutputData() {
    return outputData;
}

bool SolveBase::isCorrectData(InputData inputData, const OutputData& outputData) {
    int n = inputData.n;
    int m = inputData.m;
    int k = inputData.k;
    Vector x = outputData.x;

    if (static_cast<int>(x.size()) != n) {
        return false;
    }

    TypeData total = 0;
    for (int i = 0; i < n; ++i) {
        if ((x[i] < 0) || (x[i] > inputData.k)) {
            return false;
        }
        total += inputData.r[i][x[i]];
    }

    if (total != outputData.maxSum) {
        return false;
    }

    for (int i = 0; i < m; ++i) {
        TypeData total = 0;
        for (int j = 0; j < n; ++j) {
            total += inputData.g[i][j][x[j]];
        }

        if (total > inputData.b[i]) {
            return false;
        }
    }

    return true;
}