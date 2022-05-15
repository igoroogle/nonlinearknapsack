#ifndef NONLINEARKNAPSACK_DISPLAYDATA_H
#define NONLINEARKNAPSACK_DISPLAYDATA_H

#include "InOutData.h"
class DisplayData {
public:
    explicit DisplayData(const OutputData& outputData);
    void writeData();
private:
    OutputData outputData;
};


#endif //NONLINEARKNAPSACK_DISPLAYDATA_H
