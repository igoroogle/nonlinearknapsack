#include "SolveMMDPHybridHeuristicRandom.h"
#include <random>
#include <iostream>


SolveMMDPHybridHeuristicRandom::SolveMMDPHybridHeuristicRandom(const InputData& inputData) : SolveMMDPHybridHeuristicBoth(inputData) {

}

void SolveMMDPHybridHeuristicRandom::solve() {
    genS();
    lowerBound = 0;

    //heurictic #both
    precalcHeuristic();

    //initialize F_0
    initialize();

    for (int n = 0; n < inputData.n; ++n) {

        //label the points of F_n as beta^0, beta^1, etc.
        std::vector<int> betaIndices;
        for (auto& cur : indices) {
            betaIndices.push_back(cur);
            assert(spaces[cur].inList);
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(betaIndices.begin(), betaIndices.end(), g);
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

                //check upperBounds
                if (!isFathomingSum(n, k, p)) {
                    continue;
                }

                if (!isFathomingMin(n, k, p)) {
                    continue;
                }

                add(n, k, p);

                if (inputData.r[n][k] + spaces[p].flist[inputData.m] > lowerBound) {
                    lowerBound = inputData.r[n][k] + spaces[p].flist[inputData.m];
                }
            }
        }

        //delete by fathoming
        for (int& p : betaIndices) {
            if (spaces[p].inList) {
                if (!isFathomingAbsoluteSum(spaces[p].flist[inputData.m], n)
                    || !isFathomingAbsoluteMin(spaces[p].flist[inputData.m], n, p)) {
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

    restoreOutputData();
}