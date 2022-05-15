#include "InitializeKnapsack01Data.h"
#include <iostream>

Knapsack01Data InitializeKnapsack01Data::getData() {
    return data;
}

void InitializeKnapsack01Data::readData() {
    std::cin >> data.m >> data.n >> data.ans;
    data.objects.resize(data.m);
    data.capacities.resize(data.m);
    data.a.assign(data.n, std::vector<TypeData>(data.m));

    for (int i = 0; i < data.m; ++i) {
        std::cin >> data.objects[i];
    }


    for (int i = 0; i < data.n; ++i) {
        for (int j = 0; j < data.m; ++j) {
            std::cin >> data.a[i][j];
        }
    }

    for (int i = 0; i < data.n; ++i) {
        std::cin >> data.capacities[i];
    }
}

TypeData InitializeKnapsack01Data::getAns() {
    return data.ans;
}