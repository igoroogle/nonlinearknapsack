#include "ConvertKnapsak01Data.h"

ConvertKnapsak01Data::ConvertKnapsak01Data (const Knapsack01Data& data) {
    this->data = data;
}

void ConvertKnapsak01Data::convert() {
    int n = data.m;
    int m = data.n;
    inputData.n = n;
    inputData.m = m;
    inputData.k = 1;

    inputData.b = data.capacities;
    //inputData.b.resize(m);
    /*for (int i = 0; i < m; ++i) {
        inputData.g[i].resize(n);
        for (int j = 0; j < n; ++j) {
            inputData.g[i][j].resize(2);
            //inputData.g[i][j][2] = data.a[j][i];
        }
    }*/

    inputData.r.resize(n);

    for (int i = 0; i < n; ++i) {
        inputData.r[i].resize(2);
        inputData.r[i][1] = data.objects[i];
    }

    inputData.g.resize(m);
    for (int i = 0; i < m; ++i) {
        inputData.g[i].resize(n);
        for (int j = 0; j < n; ++j) {
            inputData.g[i][j].resize(inputData.k + 1);
            for (int p = 1; p <= inputData.k; ++p) {
                inputData.g[i][j][1] = data.a[i][j];
            }
        }
    }

}

InputData ConvertKnapsak01Data::getInputData() {
    return inputData;
}