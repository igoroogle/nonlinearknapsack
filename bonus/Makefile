.PHONY: all clean

#DBG_FLAGS=-fsanitize=address
EXEC=NonlinearKnapsack

all: $(EXEC)

$(EXEC): obj/main.o obj/Timer.o obj/Timer.o obj/InitializeData.o obj/DisplayData.o obj/InitializeKnapsack01Data.o obj/ConvertKnapsak01Data.o obj/SolveBase.o obj/SolveStraightForward.o obj/SolveKnapsack01.o obj/SolveMMDP.o obj/SolveMMDPHybrid.o obj/SolveMMDPHybridMainHeuristic.o
	g++ $(DBG_FLAGS) $^ -o $@

obj/%.o: src/%.cpp | obj
	g++ -c -std=c++2a  -I include $< -o $@

obj:
	mkdir -p obj

obj/main.o: include/Timer.h
obj/main.o: include/InitializeData.h
#obj/main.o: include/InOutData.h
obj/main.o: include/DisplayData.h
obj/main.o: include/InitializeKnapsack01Data.h
obj/main.o: include/ConvertKnapsak01Data.h
obj/main.o: include/SolveBase.h
obj/main.o: include/SolveStraightForward.h
obj/main.o: include/SolveKnapsack01.h
obj/main.o: include/SolveMMDP.h
obj/main.o: include/SolveMMDPHybrid.h
obj/main.o: include/SolveMMDPHybridMainHeuristic.h
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
#include "SolveMMDPHybrid.h"
obj/Timer.o: include/Timer.h
obj/InitializeData.o: include/InitializeData.h
#obj/InOutData.o: include/InOutData.h
obj/DisplayData.o: include/DisplayData.h
obj/InitializeKnapsack01Data.o: include/InitializeKnapsack01Data.h
obj/ConvertKnapsak01Data.o: include/ConvertKnapsak01Data.h
obj/SolveBase.o: include/SolveBase.h
obj/SolveStraightForward.o: include/SolveStraightForward.h
obj/SolveKnapsack01.o: include/SolveKnapsack01.h
obj/SolveMMDP.o: include/SolveMMDP.h
obj/SolveMMDPHybrid.o: include/SolveMMDPHybrid.h
obj/SolveMMDPHybrid.o: include/SolveMMDPHybridMainHeuristic.h


clean:
	rm -rf obj $(EXEC)