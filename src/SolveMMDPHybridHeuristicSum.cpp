#include "SolveMMDPHybridHeuristicSum.h"
#include <cassert>
#include <iostream>
#include <random>
#include <algorithm>

SolveMMDPHybridHeuristicSum::SolveMMDPHybridHeuristicSum(const InputData& inputData) : SolveMMDP(inputData) {

}

void SolveMMDPHybridHeuristicSum::solve() {
    genS();
    precalcHeuristic();
    lowerBound = 0;

    //initialize F_0
    initialize();


    for (int n = 0; n < inputData.n; ++n) {

        //label the points of F_n as beta^0, beta^1, etc.
        std::vector<int> betaIndices;
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

    restoreOutputData();
}



bool SolveMMDPHybridHeuristicSum::isFathoming(int n, int k, int p) {
    TypeData base = inputData.r[n][k] + spaces[p].flist[inputData.m];

    if (n + 1 < inputData.n) {
        base += sumR[n + 1];
    }

    return (base > lowerBound);
}

bool SolveMMDPHybridHeuristicSum::isFathomingAbsolute(TypeData base, int n) {
    if (n + 1 < inputData.n) {
        //base += std::min(sumR[n + 1], pHeuristicMin[n + 1] + 1);
        base += sumR[n + 1];
    }

    return (base >= lowerBound);
}

void SolveMMDPHybridHeuristicSum::precalcHeuristic() {
    //heurictic #1
    int n = inputData.n;
    sumR.resize(n);
    sumR[n - 1] = inputData.r[n - 1][inputData.k];
    for (int i = n - 2; i >= 0; --i) {
        sumR[i] = inputData.r[i][inputData.k] + sumR[i + 1];
    }
}