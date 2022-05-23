#include "SolveStraightForward.h"

SolveStraightForward::SolveStraightForward(const InputData& inputData) : SolveBase(inputData) {

}

void SolveStraightForward::solve() {
    OutputData curData, bestData;
    curData.maxSum = 0;
    curData.x.resize(inputData.n);
    bestData = curData;
    rec(0, curData, bestData);
    outputData = bestData;
}

void SolveStraightForward::rec(int curInd, OutputData& curData, OutputData& bestData) {
    if (curInd >= inputData.n) {
        if ((isCorrectData(inputData, curData)) && (curData.maxSum > bestData.maxSum)) {
            bestData = curData;
        }
        return;
    }

    TypeData maxSum = curData.maxSum;
    for (int i = 0; i <= inputData.k; ++i) {
        curData.x[curInd] = i;
        curData.maxSum = maxSum + inputData.r[curInd][i];
        rec(curInd + 1, curData, bestData);
    }

    curData.maxSum = maxSum;
    curData.x[curInd] = 0;
}

//SolveStraightForward