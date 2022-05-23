#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <set>
#include <utility>

#include "Timer.h"
#include "InOutData.h"
#include "InitializeData.h"
#include "DisplayData.h"
#include "InitializeKnapsack01Data.h"
#include "ConvertKnapsak01Data.h"
#include "SolveBase.h"
#include "SolveStraightForward.h"
#include "SolveKnapsack01.h"
#include "SolveMMDP.h"
#include "SolveMMDPHybridHeuristicSum.h"
#include "SolveMMDPHybridHeuristicMin.h"
#include "SolveMMDPHybridHeuristicBoth.h"
#include "SolveMMDPHybridHeuristicRandom.h"

int main() {
    //freopen("ALL-MKP-Instances/sac94/weing/weing1.dat", "r", stdin);
    //freopen("ALL-MKP-Instances/sac94/pet/pet4.dat", "r", stdin);
    //freopen("ALL-MKP-Instances/sac94/weish/weish13.dat", "r", stdin);
    //freopen("ALL-MKP-Instances/gk/gk01.dat", "r", stdin);
    //freopen("ALL-MKP-Instances/sac94/sento/sento1.dat", "r", stdin);
    //freopen("ALL-MKP-Instances/chubeas/OR5x100/OR5x100.dat", "r", stdin);
    //freopen("test04.in", "r", stdin);
    int t = 1;
    //int t;
    //std::cin >> t;
    while (t--) {
        std::cout << "Starting t " << t << '\n';
        //freopen("ALL-MKP-Instances/sac94/pet/pet5.dat", "r", stdin); //28 10 1
        //freopen("ALL-MKP-Instances/sac94/pet/pet5.dat", "r", stdin);
        //freopen("ALL-MKP-Instances/sac94/pet/pet4.dat", "r", stdin); //better min
        //freopen("ALL-MKP-Instances/sac94/pet/pet5.dat", "r", stdin); //better min
        //freopen("ALL-MKP-Instances/sac94/pet/pet2.dat", "r", stdin); //better min
        //freopen("ALL-MKP-Instances/sac94/pet/pet3.dat", "r", stdin);
        //freopen("tes.txt", "r", stdin);
        //freopen("test04.txt", "r", stdin);


        //initialize Data
        //InitializeData initializeData;
        //initializeData.readData();
        InitializeKnapsack01Data initializeKnapsack01Data;
        initializeKnapsack01Data.readData();
        ConvertKnapsak01Data  convertKnapsak01Data(initializeKnapsack01Data.getData());
        convertKnapsak01Data.convert();


        //convertKnapsak01Data.getInputData()
        InputData inputData = convertKnapsak01Data.getInputData();
        InitializeData initializeData(inputData);
        initializeData.writeData();


        //Get Result
        /*OutputData outputData;
        outputData.maxSum = 323;
        outputData.x = {1, 2, 3, 4};
        DisplayData displayData(outputData);
        displayData.writeData();

        initializeData.writeData();*/


        //solveStraightForward
        /*SolveStraightForward solveStraightForward(initializeData.getInputData());
        {
            Timer timer;
            solveStraightForward.solve();
        }


        std::cout << "-----------\n";

        DisplayData displayData(solveStraightForward.getOutputData());
        displayData.writeData();*/




        //solveKnapsack01
        /*SolveKnapsack01 solveKnapsack01(initializeData.getInputData());
        {
            Timer timer;
            solveKnapsack01.solve();
        }
        std::cout << "-----------2\n";
        DisplayData displayData2(solveKnapsack01.getOutputData());
        displayData2.writeData();*/


        //solveMMDP
        /*SolveMMDP solveMMDP(initializeData.getInputData());
        {
            Timer timer;
            solveMMDP.solve();
        }
        std::cout << "-----------3 MMDP\n";
        DisplayData displayData3(solveMMDP.getOutputData());
        displayData3.writeData();*/


        //solveMmdpHybridHeuristicSum

        SolveMMDPHybridHeuristicSum solveMmdpHybridHeuristicSum(initializeData.getInputData());

        {
            Timer timer;
            solveMmdpHybridHeuristicSum.solve();
            //assert(initializeKnapsack01Data.getAns() == solveMmdpHybridHeuristicSum.getOutputData().maxSum);
        }
        std::cout << "-----------4 Sum\n";
        DisplayData displayData4(solveMmdpHybridHeuristicSum.getOutputData());
        displayData4.writeData();

        //SolveMMDPHybridHeuristicMin
        /*SolveMMDPHybridHeuristicMin solveMMDPHybridHeuristicMin(initializeData.getInputData());

        {
            Timer timer;
            solveMMDPHybridHeuristicMin.solve();
            //assert(initializeKnapsack01Data.getAns() == solveMMDPHybridHeuristicMin.getOutputData().maxSum);
        }
        std::cout << "-----------5 Min\n";
        DisplayData displayData5(solveMMDPHybridHeuristicMin.getOutputData());
        displayData5.writeData();*/


        //SolveMMDPHybridHeuristicBoth
        /*SolveMMDPHybridHeuristicBoth solveMMDPHybridHeuristicBoth(initializeData.getInputData());

        {
            Timer timer;
            solveMMDPHybridHeuristicBoth.solve();
            //assert(initializeKnapsack01Data.getAns() == solveMMDPHybridHeuristicBoth.getOutputData().maxSum);
        }
        std::cout << "-----------6 Both\n";
        DisplayData displayData6(solveMMDPHybridHeuristicBoth.getOutputData());
        displayData6.writeData();*/


        SolveMMDPHybridHeuristicRandom solveMMDPHybridHeuristicRandom(initializeData.getInputData());

        {
            Timer timer;
            solveMMDPHybridHeuristicRandom.solve();
            /*std::cout << solveMMDPHybridHeuristicMin.getOutputData().maxSum << "maxSum\n";
            std::cout << initializeKnapsack01Data.getAns() << "getAns\n";*/
            //assert(initializeKnapsack01Data.getAns() == solveMMDPHybridHeuristicRandom.getOutputData().maxSum);
        }
        std::cout << "-----------7 Random\n";
        DisplayData displayData7(solveMMDPHybridHeuristicRandom.getOutputData());
        displayData7.writeData();

        //solveMMDP
        /*
        SolveMMDP solveMMDP(initializeKnapsack01Data.getData());

        {
            Timer timer;
            solveMMDP.solve();
        }
        std::cout << "-----------3\n";
        DisplayData displayData3(solveMMDP.getOutputData());
        displayData3.writeData();
         */




        /*SolveMMDP solveMMDP(convertKnapsak01Data.getInputData());
        {
            Timer timer;
            solveMMDP.solve();
        }

        std::cout << "-----------3\n";
        DisplayData displayData3(solveMMDP.getOutputData());
        displayData3.writeData();*/
        std::cout << "Finishing t " << t << '\n';
    }
}


/*
test 1
2 2 2
2 4
1 2
3 4

1 2
3 4

1 2
3 4
ans ?

test 2 (0-1)
10 2 1
190 250
84
34
31
14
67
65
86
98
50
7
20
12
7
75
93
21
75
67
34
28
41
51
24
40
84
70
34
41
49
27
Ans 364


test 3 from file
3 2 3

8 12

2 4 4.75
3 6 8
4.25 6.25 6.75

1 2 3
2 4 6
3 6 9

2 4 6
3 6 9
4 8 12

ANS: 12.25


test 4 small test
1 2 2
4 4

2 2

2
2

2
2

 */