#include "SolveMMDPHybrid.h"
#include <cassert>
#include <iostream>

SolveMMDPHybrid::SolveMMDPHybrid(const InputData& inputData) : SolveMMDP(inputData) {

}

void SolveMMDPHybrid::solve() {
    genS();
    lowerBound = 0;

    //heurictic #1
    int n = inputData.n;
    sumR.resize(n);
    sumR[n - 1] = inputData.r[n - 1][inputData.k];
    for (int i = n - 2; i >= 0; --i) {
        sumR[i] = inputData.r[i][inputData.k] + sumR[i + 1];
    }

    //inicialize F_0
    spaces.resize(1);
    spaces[0].trace = {-1, 0, -1};
    indices.push_back(0);
    spaces[0].it = indices.begin();
    spaces[0].inList = true;
    spaces[0].flist.resize(inputData.m + 1);
    spaces[0].permute.resize(inputData.m + 1);
    indicesSize = 1;

    for (int n = 0; n < inputData.n; ++n) {

        //label the points of F_n as beta^0, beta^1, etc.
        std::vector<int> betaIndices;
        betaIndices.reserve(indicesSize);
        for (auto& cur : indices) {
            betaIndices.push_back(cur);
            assert(spaces[cur].inList);
        }

        for (int k = 1; k <= inputData.k; ++k) {
            if (!inS[n][k]) { //k is not in undominated feasible points
                continue;
            }

            for (int& p : betaIndices) {
                if (!isFeasibility(n, k, p)) {
                    continue;
                }

                if (isFindDominanted(n, k, p)) { //check some Value of Dominance
                    continue;
                }

                del(n, k, p);

                if (!isFathoming(n, k, p)) {
                    continue;
                }

                add(n, k, p);

                if (inputData.r[n][k] + spaces[p].flist[inputData.m] > lowerBound) {
                    lowerBound = inputData.r[n][k] + spaces[p].flist[inputData.m];
                }
            }
        }

        for (int& p : betaIndices) {
            if (spaces[p].inList) {
                if (!isFathomingAbsolute(spaces[p].flist[inputData.m], n)) {
                    spaces[p].inList = false;
                    indices.erase(spaces[p].it);
                    --indicesSize;
                }
            }
        }
    }

    int p = *indices.begin();
    int m = inputData.m;
    for (auto& cur : indices) {

        if (spaces[cur].flist[m] > spaces[p].flist[m]) {
            p = cur;
        }
    }

    outputData.maxSum = 0;
    outputData.x.resize(inputData.n);
    while (spaces[p].trace[0] != -1) {
        int n = spaces[p].trace[0];
        int k = spaces[p].trace[1];
        outputData.maxSum += inputData.r[n][k];
        outputData.x[n] = k;
        p = spaces[p].trace[2];
    }

    //assert(isCorrectData(inputData, outputData));
    std::cout << "F_N size: " << indicesSize << '\n';
}



bool SolveMMDPHybrid::isFathoming(int n, int k, int p) {
    TypeData base = inputData.r[n][k] + spaces[p].flist[inputData.m];
    /*for (int i = n + 1; i < inputData.n; ++i) {
        base += inputData.r[i][inputData.k];
        if (base > lowerBound) {
            return true;
        }
    }*/

    if (n + 1 < inputData.n) {
        //base += std::min(sumR[n + 1], pHeuristicMin[n + 1] + 1);
        base += sumR[n + 1];
    }

    return (base > lowerBound);
}

bool SolveMMDPHybrid::isFathomingAbsolute(TypeData base, int n) {
    /*for (int i = n + 1; i < inputData.n; ++i) {
        base += inputData.r[i][inputData.k];
        if (base > lowerBound) {
            return true;
        }
    }*/
    if (n + 1 < inputData.n) {
        //base += std::min(sumR[n + 1], pHeuristicMin[n + 1] + 1);
        base += sumR[n + 1];
    }

    return (base >= lowerBound);
}