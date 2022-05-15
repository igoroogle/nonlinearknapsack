#ifndef NONLINEARKNAPSACK_SOLVEMMDP_H
#define NONLINEARKNAPSACK_SOLVEMMDP_H

#include "SolveBase.h"
#include <list>


struct Spaces {
    std::vector<int> trace;
    Vector flist;
    std::vector<int> permute;
    bool inList;
    std::list<int> :: iterator it;
};

class SolveMMDP : public SolveBase {
public:
    SolveMMDP(const InputData& inputData);
    void solve() override;
protected:
    std::vector<std::vector<bool>> inS; //check as undominated feasible points
    std::vector<Spaces> spaces;
    std::list<int> indices;
    int indicesSize;
    void genS(); //generate inS
    bool isFeasible(int n, int k);
    bool isDominant(int n, int subdominant, int dominant);
    bool isFeasibility(int n, int k, int p);
    bool isFindDominanted(int n, int k, int p);
    bool isDominanted(int n, int k, int p, int t);
    void del(int n, int k, int p);
    void add(int n, int k, int p);
    bool isDominantedBy(int n, int k, int p, int t);
    void printB(int p);
};


#endif //NONLINEARKNAPSACK_SOLVEMMDP_H
