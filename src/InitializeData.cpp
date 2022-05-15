#include "InitializeData.h"
#include <iostream>

InitializeData::InitializeData() {

}

InitializeData::InitializeData(InputData inputData) {
    this->inputData = inputData;
}

void InitializeData::readData() {
    int n, m, k;
    Vector b;
    Matrix r;
    Cube g;
    std::cin >> n >> m >> k;
    b.resize(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    r.resize(n);
    for (int i = 0; i < n; ++i) {
        r[i].resize(k + 1);
        for (int j = 1; j <= k; ++j) {
            std::cin >> r[i][j];
        }
    }

    g.resize(m);
    for (int i = 0; i < m; ++i) {
        g[i].resize(n);
        for (int j = 0; j < n; ++j) {
            g[i][j].resize(k + 1);
            for (int p = 1; p <= k; ++p) {
                std::cin >> g[i][j][p];
            }
        }
    }

    inputData.n = n;
    inputData.m = m;
    inputData.k = k;
    inputData.b = b;
    inputData.r = r;
    inputData.g = g;
}

void InitializeData::writeData() {
    int n, m, k;
    Vector b;
    Matrix r;
    Cube g;

    n = inputData.n;
    m = inputData.m;
    k = inputData.k;
    b = inputData.b;
    r = inputData.r;
    g = inputData.g;
    std::cout << "N M K: " << n << ' ' << m << ' ' << k << '\n';

    std::cout << "B: ";
    for (int i = 0; i < m; ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < n; ++i) {
        std::cout << "r_" << i + 1 << " ";
        for (int j = 0; j <= k; ++j) {
            std::cout << r[i][j] << ' ';
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    for (int i = 0; i < m; ++i) {
        std::cout << std::endl;
        std::cout << "g_" << i + 1 <<  " block \n";
        std::cout << '\n';

        for (int j = 0; j < n; ++j) {
            std::cout << "g_" << i + 1 << "," << j + 1 << ": ";
            for (int p = 0; p <= k; ++p) {
                std::cout << g[i][j][p] << ' ';
            }
            std::cout << '\n';
        }
    }
}

InputData InitializeData::getInputData() {
    return inputData;
}

//initializeData