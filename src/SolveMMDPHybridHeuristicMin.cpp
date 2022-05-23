#include "SolveMMDPHybridHeuristicMin.h"
#include <cassert>
#include <algorithm>


SolveMMDPHybridHeuristicMin::SolveMMDPHybridHeuristicMin(const InputData& inputData) : SolveMMDP(inputData) {

}

void SolveMMDPHybridHeuristicMin::solve() {
    genS();
    lowerBound = 0;

    //heurictic #2
    precalcHeuristic();

    //initialize F_0
    initialize();

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

        //delete by fathoming
        for (int& p : betaIndices) {
            if (spaces[p].inList) {
                if (!isFathomingAbsolute(spaces[p].flist[inputData.m], n, p)) {
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

void SolveMMDPHybridHeuristicMin::precalcHeuristic() {
    //heuristic #2
    int m = inputData.m;
    int n = inputData.n;

    pHeuristic.assign(m, std::vector<long double>(n));
    for (int i = 0; i < m; ++i) {
        pHeuristic[i][n - 1] = 0;
        for (int j = 1; j <= inputData.k; ++j) {
            if (inputData.g[i][n - 1][j] > 0) {
                pHeuristic[i][n - 1] = std::max(pHeuristic[i][n - 1],
                                                static_cast<long double>(inputData.r[n - 1][j])
                                                    / static_cast<long double>(inputData.g[i][n - 1][j]));
            } else {
                pHeuristic[i][n - 1] = INF;
            }
        }

        for (int j = n - 2; j >= 0; --j) {
            pHeuristic[i][j] = pHeuristic[i][j + 1];
            for (int p = 1; p <= inputData.k; ++p) {
                if (inputData.g[i][j][p] > 0) {
                    pHeuristic[i][j] = std::max(pHeuristic[i][j],
                                                static_cast<long double>(inputData.r[j][p])
                                                    / static_cast<long double>(inputData.g[i][j][p]));
                } else {
                    pHeuristic[i][j] = INF;
                }
            }
        }
    }
}


bool SolveMMDPHybridHeuristicMin::isFathoming(int n, int k, int p) {
    TypeData base = inputData.r[n][k] + spaces[p].flist[inputData.m];
    return isFathomingAbsolute(base, n, p);
}

bool SolveMMDPHybridHeuristicMin::isFathomingAbsolute(TypeData base, int n, int p) {
    long double minHeuristic = INF;
    Vector x;

    for (int i = 0; i < inputData.m; ++i) {
        if (pHeuristic[i][n] < INF && pHeuristic[i][n] > 0) {
            minHeuristic = std::min(minHeuristic, pHeuristic[i][n]
                * static_cast<double>(inputData.b[i] - spaces[p].flist[i]));
        }
    }

    if (minHeuristic >= INF) {
        return true;
    }

    if (n < inputData.n) {
        return (base + minHeuristic >= lowerBound);
    }

    return (base >= lowerBound);
}