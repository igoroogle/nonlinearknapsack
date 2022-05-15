#include "SolveMMDPHybridMainHeuristic.h"
#include <iostream>
#include <cassert>


SolveMMDPHybridMainHeuristic::SolveMMDPHybridMainHeuristic(const InputData& inputData) : SolveMMDPHybrid(inputData) {

}

void SolveMMDPHybridMainHeuristic::solve() {
    genS();
    lowerBound = 0;

    //heurictic #1
    int n = inputData.n;
    sumR.resize(n);
    sumR[n - 1] = inputData.r[n - 1][inputData.k];
    for (int i = n - 2; i >= 0; --i) {
        sumR[i] = inputData.r[i][inputData.k] + sumR[i + 1];
    }

    //heurictic #2
    precalcHeuristic();

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

                //check upperBounds
                /*if (!isFathoming(n, k, p)) {
                    continue;
                }*/

                if (!isFathomingMainHeuristic(n, k, p)) {
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
                if (/*!isFathomingAbsolute(spaces[p].flist[inputData.m], n)
                    ||*/ !isFathomingAbsoluteMainHeuristic(spaces[p].flist[inputData.m], n, p)) {
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

    assert(isCorrectData(inputData, outputData));
    std::cout << "F_N size: " << indicesSize << '\n';
}

void SolveMMDPHybridMainHeuristic::precalcHeuristic() {
    //heuristic #2
    int m = inputData.m;
    int n = inputData.n;

    pHeuristic.assign(m, std::vector<TypeData>(n));
    for (int i = 0; i < m; ++i) {
        pHeuristic[i][n - 1] = 0;
        /*for (int j = 1; j <= inputData.k; ++j) {
            if (inputData.g[i][n - 1][j] > 0) {
                pHeuristic[i][n - 1] = std::max(pHeuristic[i][n - 1],
                                                inputData.r[n - 1][j] / inputData.g[i][n - 1][j]);
            }
        }*/

        for (int j = n - 2; j >= 0; --j) {
            pHeuristic[i][j] = pHeuristic[i][j + 1];
            for (int p = 1; p <= inputData.k; ++p) {
                if (inputData.g[i][j][p] > 0) {
                    pHeuristic[i][j] = std::max(pHeuristic[i][j], inputData.r[j][p] / inputData.g[i][j][p]);
                } else {
                    pHeuristic[i][j] = INF;
                }
            }
        }
    }

    /*pHeuristicMin.resize(n);
    for (int i = 0; i < n; ++i) {
        pHeuristicMin[i] = pHeuristic[0][i];
        for (int j = 1; j < m; ++j) {
            pHeuristicMin[i] = std::min(pHeuristicMin[i], pHeuristic[j][i]);
        }
    }*/
}


bool SolveMMDPHybridMainHeuristic::isFathomingMainHeuristic(int n, int k, int p) {
    TypeData base = inputData.r[n][k] + spaces[p].flist[inputData.m];
    return isFathomingAbsoluteMainHeuristic(base, n, p);
}

bool SolveMMDPHybridMainHeuristic::isFathomingAbsoluteMainHeuristic(TypeData base, int n, int p) {
    TypeData minHeuristic = INF;
    Vector x;
    //restoreX(p, x);

    for (int i = 0; i < inputData.m; ++i) {
        if (pHeuristic[i][n] < INF) {
            /*std::cout << "hah " << " " << pHeuristic[i][n] << i << ' ' << n;
            exit(0);*/
            minHeuristic = std::min(minHeuristic, pHeuristic[i][n] * (inputData.b[i] - spaces[p].flist[i]));
        }
    }

    if (minHeuristic >= INF) {
        return true;
    }

    if (n < inputData.n) {
        base += minHeuristic;
    }

    return (base >= lowerBound);
}

void SolveMMDPHybridMainHeuristic::restoreX(int p, Vector& x) {
    x.resize(inputData.n);
    while (spaces[p].trace[0] != -1) {
        int n = spaces[p].trace[0];
        int k = spaces[p].trace[1];
        x[n] = k;
        p = spaces[p].trace[2];
    }
}