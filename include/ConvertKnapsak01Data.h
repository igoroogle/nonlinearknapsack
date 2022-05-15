#ifndef NONLINEARKNAPSACK_CONVERTKNAPSAK01DATA_H
#define NONLINEARKNAPSACK_CONVERTKNAPSAK01DATA_H

#include "Knapsack01Data.h"
#include "InOutData.h"

class ConvertKnapsak01Data {
public:
    explicit ConvertKnapsak01Data(const Knapsack01Data& data);
    void convert();
    InputData getInputData();
private:
    Knapsack01Data data;
    InputData inputData;
};


#endif //NONLINEARKNAPSACK_CONVERTKNAPSAK01DATA_H
