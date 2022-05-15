#ifndef NONLINEARKNAPSACK_INOUTDATA_H
#define NONLINEARKNAPSACK_INOUTDATA_H

#include "Constants.h"

struct InputData {
    int n, m, k;
    Vector b;
    Matrix r;
    Cube g;
};

struct OutputData {
    TypeData maxSum;
    Vector x;
};

//inputOutputData

#endif //NONLINEARKNAPSACK_INOUTDATA_H
