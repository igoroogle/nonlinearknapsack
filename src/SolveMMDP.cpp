#include "SolveMMDP.h"
#include <iostream>
#include <cassert>
#include <set>

SolveMMDP::SolveMMDP(const InputData& inputData) : SolveBase(inputData) {

}

void SolveMMDP::solve() {
    genS();

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
                add(n, k, p);
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

    /*for (auto& cur : indices) {
        std::cout << "ind " << cur << ' ' << spaces[cur].trace[0] << ' ' << spaces[cur].trace[1] << ' ';
        std::cout << spaces[cur].trace[2] << ' ' << spaces[cur].flist[m] << std::endl;
        printB(cur);
    }*/

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

void SolveMMDP::genS() {
    int n = inputData.n, k = inputData.k;
    inS.assign(n, std::vector<bool>(k + 1, true));
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (!isFeasible(i, j)) {
                inS[i][j] = false;
                continue;
            }

            for (int p = 0; p < j; ++p) {
                if (!inS[i][p]) {
                    continue;
                }

                if (isDominant(i, j, p)) {
                    inS[i][j] = false;
                    break;
                }

                if (isDominant(i, p, j)) {
                    inS[i][p] = false;
                }
            }
        }
    }
}


bool SolveMMDP::isFeasible(int n, int k) {
    for (int i = 0; i < inputData.m; ++i) {
        if (inputData.g[i][n][k] > inputData.b[i]) {
            return false;
        }
    }

    return true;
}

bool SolveMMDP::isDominant(int n, int subdominant, int dominant) {
    if (inputData.r[n][dominant] < inputData.r[n][subdominant]) {
        return false;
    }

    for (int i = 0; i < inputData.m; ++i) {
        if (inputData.g[i][n][dominant] > inputData.g[i][n][subdominant]) {
            return false;
        }
    }

    return true;
}

bool SolveMMDP::isFeasibility(int n, int k, int p) {
    while (spaces[p].trace[0] != -1) {
        for (int i = 0; i < inputData.m; ++i) {
            if (inputData.g[i][n][k] + spaces[p].flist[i] > inputData.b[i]) {
                return false;
            }
        }

        p = spaces[p].trace[2];
    }

    return true;
}

bool SolveMMDP::isFindDominanted(int n, int k, int p) {
    std::set<int> alreadyUsed;
    for (int i = 0; i < inputData.m; ++i) {
        TypeData upperBound = inputData.g[i][n][k] + spaces[p].flist[i];
        int t = p;
        while (t && spaces[t].flist[i] <= upperBound) {
            if (alreadyUsed.find(t) == alreadyUsed.end()) {
                if (isDominanted(n, k, p, t)) {
                    return true;
                }
                alreadyUsed.insert(t);
            }

            t = spaces[t].permute[i];
        }
    }

    return false;
}

bool SolveMMDP::isDominanted(int n, int k, int p, int t) {
    if (inputData.r[n][k] + spaces[p].flist[inputData.m] > spaces[t].flist[inputData.m]) {
        return false;
    }


    for (int i = 0; i < inputData.m; ++i) {
        if (inputData.g[i][n][k] + spaces[p].flist[i] < spaces[t].flist[i]) {
            return false;
        }
    }

    return true;
}

void SolveMMDP::del(int n, int k, int p) {
    int m = inputData.m;


    TypeData upperBound = inputData.r[n][k] + spaces[p].flist[m];
    int t = p;
    while (t && spaces[t].flist[m] <= upperBound) {

        if (isDominantedBy(n, k, p, t)) {
            if (spaces[t].inList) {//B^t is dominanted by Y^k + B^p
                spaces[t].inList = false;
                indices.erase(spaces[t].it);
                --indicesSize;
            }
        }

        t = spaces[t].permute[m];
    }

    for (int i = 0; i <= inputData.m; ++i) {
        TypeData upperBound = 0;
        if (i < m) {
            upperBound = inputData.g[i][n][k] + spaces[p].flist[i];
        } else {
            upperBound = inputData.r[n][k] + spaces[p].flist[i];
        }

        int lastIndex = p;
        int t = spaces[p].permute[i];
        while (t && spaces[t].flist[i] <= upperBound) {
            if (!spaces[t].inList) {
                spaces[lastIndex].permute[i] = spaces[t].permute[i];
            } else {
                lastIndex = t;
            }
            t = spaces[t].permute[i];
        }
    }
}

void SolveMMDP::add(int n, int k, int p) {
    int m = inputData.m;

    indices.push_back(static_cast<int>(spaces.size()));
    spaces.resize(spaces.size() + 1);
    spaces.back().trace = {n, k, p};
    auto it = indices.end();
    --it;
    spaces.back().it = it;
    spaces.back().inList = true;
    spaces.back().flist.resize(inputData.m + 1);
    spaces.back().permute.resize(inputData.m + 1);
    ++indicesSize;

    for (int i = 0; i <= inputData.m; ++i) {
        TypeData upperBound = 0;
        if (i < m) {
            upperBound = inputData.g[i][n][k] + spaces[p].flist[i];
        } else {
            upperBound = inputData.r[n][k] + spaces[p].flist[i];
        }

        int lastIndex = p;
        int t = spaces[p].permute[i];
        while (t && spaces[t].flist[i] <= upperBound) {
            lastIndex = t;
            t = spaces[t].permute[i];
        }

        spaces.back().permute[i] = t;
        spaces[lastIndex].permute[i] = static_cast<int>(spaces.size()) - 1;
    }

    for (int i = 0; i < inputData.m; ++i) {
        spaces.back().flist[i] = inputData.g[i][n][k] + spaces[p].flist[i];
    }
    spaces.back().flist[m] = inputData.r[n][k] + spaces[p].flist[m];
}

bool SolveMMDP::isDominantedBy(int n, int k, int p, int t) {
    if (inputData.r[n][k] + spaces[p].flist[inputData.m] < spaces[t].flist[inputData.m]) {
        return false;
    }


    for (int i = 0; i < inputData.m; ++i) {
        if (inputData.g[i][n][k] + spaces[p].flist[i] > spaces[t].flist[i]) {
            return false;
        }
    }

    return true;
}

void SolveMMDP::printB(int p) {
    Vector ans;
    ans.resize(inputData.n);
    while (spaces[p].trace[0] != -1) {
        ans[spaces[p].trace[0]] = spaces[p].trace[1];
        p = spaces[p].trace[2];
    }

    std::cout << "Vector: ";
    for (auto& cur : ans) {
        std::cout << cur << ' ';
    }
    std::cout << '\n';
}

//SolveMMDP