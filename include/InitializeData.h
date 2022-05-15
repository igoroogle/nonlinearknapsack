#ifndef NONLINEARKNAPSACK_INITIALIZEDATA_H
#define NONLINEARKNAPSACK_INITIALIZEDATA_H

#include "InOutData.h"

class InitializeData {
public:
    InitializeData();
    explicit InitializeData(InputData inputData);
    void readData();
    void writeData();
    InputData getInputData();
private:
    InputData inputData;
};


#endif //NONLINEARKNAPSACK_INITIALIZEDATA_H
