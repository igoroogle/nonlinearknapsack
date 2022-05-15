#include "DisplayData.h"
#include <iostream>

DisplayData::DisplayData(const OutputData& outputData) {
    this->outputData = outputData;
}

void DisplayData::writeData() {
    std::cout << "maxSum: " << outputData.maxSum << '\n';
    std::cout << "X: ";

    for (auto& cur : outputData.x) {
        std::cout << cur << ' ';
    }
    std::cout << '\n';
}

//DisplayData