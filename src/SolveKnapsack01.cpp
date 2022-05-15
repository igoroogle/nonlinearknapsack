#include "SolveKnapsack01.h"
#include <iostream>
#include <cassert>
#include <set>

SolveKnapsack01::SolveKnapsack01(const InputData& inputData) : SolveBase(inputData) {

}

void SolveKnapsack01::solve() {
    assert(inputData.k == 1);
    Vector v;
    Matrix a;
    Vector b;
    initialize(v, a, b);

    //preparing
    std::set<size_t> includes, excludes, others, bestAns;
    double lowerBound;
    for (size_t i = 0; i < v.size(); ++i) {
        others.insert(i);
    }

    branchAndBound(v, a, b, includes, excludes, others, bestAns, lowerBound);
    assert(isCorrect(bestAns, a, b));
    //print(bestAns, v);
    changeOutputData(bestAns, v);

    /*std::cout << "check solving\n";
    InitializeData initializeData(inputData);
    initializeData.writeData();

    std::cout << "check output\n";
    DisplayData displayData(outputData);
    displayData.writeData();*/
}

void SolveKnapsack01::initialize(Vector& v, Matrix& a, Vector& b) {
    int n = inputData.n;
    int m = inputData.m;
    v.resize(n);
    a.assign(m, Vector(n));

    for (size_t i = 0; i < n; ++i) {
        v[i] = inputData.r[i][1];
    }

    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            a[i][j] = inputData.g[i][j][1];
        }
    }
    b = inputData.b;
}

bool SolveKnapsack01::isCorrect(std::set<size_t>& x, const Matrix& a, const Vector& b) {
    int m = a.size();
    int n = a[0].size();
    for (size_t i = 0; i < m; ++i) {
        TypeData sum = 0;
        for (size_t j = 0; j < n; ++j) {
            if (x.find(j) != x.end()) {
                sum += a[i][j];
                if (sum > b[i]) {
                    return false;
                }
            }
        }
    }

    return true;
}


void SolveKnapsack01::updLowerBound(const Vector& v, const Matrix& a, const Vector& b,
                                    std::set<size_t> includes, std::set<size_t>& bestAns, double& lowerBound) {
    if (!isCorrect(includes, a, b)) {
        return;
    }

    double sum = 0;
    for (auto cur: includes) {
        sum += v[cur];
    }

    if (sum > lowerBound) {
        lowerBound = sum;
        bestAns = includes;
    }
}

double SolveKnapsack01::getUpperBound(const Vector& v, const Vector& a, TypeData b,
                                      std::set<size_t>& includes, std::set<size_t>&others) {
    double ans = 0;
    double sum = 0;
    for (auto& cur : includes) {
        sum += a[cur];
        ans += v[cur];
    }

    std::vector<std::pair<double, size_t>> values;
    values.reserve(others.size());

    for (auto& cur : others) {
        values.emplace_back(static_cast<double>(v[cur]) / static_cast<double>(a[cur]), cur);
    }

    std::sort(values.begin(), values.end(), std::greater<std::pair<double, size_t>>());
    for (auto cur : values) {
        if (sum + a[cur.second] >= b) {
            ans += (static_cast<double>(b) - sum) / static_cast<double>(a[cur.second])
                   * static_cast<double>(v[cur.second]);
            break;
        }

        sum += a[cur.second];
        ans += v[cur.second];
    }

    return ans;
}

double SolveKnapsack01::getMinUpperBound(const Vector& v, const Matrix& a, const Vector& b,
                                         std::set<size_t> includes, std::set<size_t> others) {
    double ans = getUpperBound(v, a[0], b[0], includes, others);

    for (size_t i = 1; i < a.size(); ++i) {
        ans = std::min(ans, getUpperBound(v, a[i], b[i], includes, others));
    }

    return ans;
}

void SolveKnapsack01::branchAndBound(const Vector& v, const Matrix& a, const Vector& b,
                                     std::set<size_t> includes, std::set<size_t> excludes, std::set<size_t> others,
                                     std::set<size_t>& bestAns, double& lowerBound) {
    updLowerBound(v, a, b, includes, bestAns, lowerBound);

    if (others.empty()) {
        return;
    }

    std::vector<std::pair<double, size_t>> values;
    std::set<size_t> old_others = others;
    for (auto cur : old_others) {
        others.erase(cur);
        includes.insert(cur);
        values.emplace_back(getMinUpperBound(v, a, b, includes, others), cur);
        others.insert(cur);
        includes.erase(cur);
    }
    std::sort(values.begin(), values.end(), std::greater<std::pair<double, size_t>>());


    for (auto cur : values) {
        if (cur.first <= lowerBound) {
            excludes.insert(cur.second);
            others.erase(cur.second);
        }
    }

    for (auto cur : values) {
        if (cur.first > lowerBound) {
            includes.insert(cur.second);
            others.erase(cur.second);
            branchAndBound(v, a, b, includes, excludes, others, bestAns, lowerBound);
            includes.erase(cur.second);
            others.insert(cur.second);
        }
    }
}

void SolveKnapsack01::print(const std::set<size_t>& x, const Vector& v) {
    int n = v.size();
    TypeData sum = 0;
    Vector ans;
    for (size_t i = 0; i < n; ++i) {
        if (x.find(i) != x.end()) {
            ans.push_back(i + 1);
            sum += v[i];
        }
    }

    std::cout << "Total: " << sum << std::endl;
    std::cout << "Use: " << ' ';
    for (auto cur : ans) {
        std::cout << cur << ' ';
    }

    std::cout << std::endl;
}

void SolveKnapsack01::changeOutputData(const std::set<size_t>& x, const Vector& v) {
    int n = v.size();
    TypeData sum = 0;
    Vector ans;
    outputData.x.assign(n, 0);
    for (size_t i = 0; i < n; ++i) {
        if (x.find(i) != x.end()) {
            outputData.x[i] = 1;
            sum += v[i];
        }
    }

    outputData.maxSum = sum;
}

//SolveKnapsack01