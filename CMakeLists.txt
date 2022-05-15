cmake_minimum_required(VERSION 3.17)
project(nonlinearKnapsack)

set(CMAKE_CXX_STANDARD 20)

include_directories("include/")
add_executable(nonlinearKnapsack src/main.cpp src/Timer.cpp include/Timer.h include/InOutData.h include/Constants.h src/InitializeData.cpp include/InitializeData.h src/DisplayData.cpp include/DisplayData.h include/Knapsack01Data.h src/InitializeKnapsack01Data.cpp include/InitializeKnapsack01Data.h src/ConvertKnapsak01Data.cpp include/ConvertKnapsak01Data.h src/SolveBase.cpp include/SolveBase.h src/SolveStraightForward.cpp include/SolveStraightForward.h src/SolveKnapsack01.cpp include/SolveKnapsack01.h src/SolveMMDP.cpp include/SolveMMDP.h src/SolveMMDPHybrid.cpp include/SolveMMDPHybrid.h src/SolveMMDPHybridMainHeuristic.cpp include/SolveMMDPHybridMainHeuristic.h)