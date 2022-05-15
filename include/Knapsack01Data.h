#ifndef NONLINEARKNAPSACK_KNAPSACK01DATA_H
#define NONLINEARKNAPSACK_KNAPSACK01DATA_H

#include "Constants.h"

struct Knapsack01Data {
    int n, m;
    Vector objects;
    Vector capacities;
    Matrix a;
    TypeData ans;
};


#endif //NONLINEARKNAPSACK_KNAPSACK01DATA_H
