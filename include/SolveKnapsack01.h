#ifndef NONLINEARKNAPSACK_SOLVEKNAPSACK01_H
#define NONLINEARKNAPSACK_SOLVEKNAPSACK01_H

#include "SolveBase.h"
#include <set>

class SolveKnapsack01 : public SolveBase {
public:
    explicit SolveKnapsack01(const InputData& inputData);
    void solve() override;
private:
    void initialize(Vector& v, Matrix& a, Vector& b);
    bool isCorrect(std::set<size_t>& x, const Matrix& a, const Vector& b);
    void updLowerBound(const Vector& v, const Matrix& a, const Vector& b,
                       std::set<size_t> includes, std::set<size_t>& bestAns, double& lowerBound);
    double getUpperBound(const Vector& v, const Vector& a, TypeData b,
                         std::set<size_t>& includes, std::set<size_t>&others);
    double getMinUpperBound(const Vector& v, const Matrix& a, const Vector& b,
                            std::set<size_t> includes, std::set<size_t> others);

    void branchAndBound(const Vector& v, const Matrix& a, const Vector& b,
                        std::set<size_t> includes, std::set<size_t> excludes, std::set<size_t> others,
                        std::set<size_t>& bestAns, double& lowerBound);
    void print(const std::set<size_t>& x, const Vector& v);
    void changeOutputData(const std::set<size_t>& x, const Vector& v);
};


#endif //NONLINEARKNAPSACK_SOLVEKNAPSACK01_H
