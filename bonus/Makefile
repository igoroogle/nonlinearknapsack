.PHONY: all clean

#DBG_FLAGS=-fsanitize=address
EXEC=NonlinearKnapsack

all: $(EXEC)

$(EXEC): obj/main.o obj/Timer.o obj/InitializeData.o obj/DisplayData.o obj/InitializeKnapsack01Data.o obj/SolveBase.o obj/SolveStraightForward.o obj/SolveKnapsack01.o obj/SolveMMDP.o obj/SolveMMDPHybridHeuristicSum.o obj/SolveMMDPHybridHeuristicMin.o obj/SolveMMDPHybridHeuristicBoth.o obj/SolveMMDPHybridHeuristicRandom.o
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
obj/main.o: include/SolveMMDPHybridHeuristicSum.h
obj/main.o: include/SolveMMDPHybridHeuristicMin.h
obj/main.o: include/SolveMMDPHybridHeuristicBoth.h
obj/main.o: include/SolveMMDPHybridHeuristicRandom.h

obj/Timer.o: include/Timer.h
obj/InitializeData.o: include/InitializeData.h

obj/DisplayData.o: include/DisplayData.h
obj/InitializeKnapsack01Data.o: include/InitializeKnapsack01Data.h
obj/ConvertKnapsak01Data.o: include/ConvertKnapsak01Data.h
obj/SolveBase.o: include/SolveBase.h
obj/SolveStraightForward.o: include/SolveStraightForward.h
obj/SolveKnapsack01.o: include/SolveKnapsack01.h
obj/SolveMMDP.o: include/SolveMMDP.h
obj/SolveMMDPHybridHeuristicSum.o: include/SolveMMDPHybridHeuristicSum.h
obj/SolveMMDPHybridHeuristicMin.o: include/SolveMMDPHybridHeuristicMin.h

obj/SolveMMDPHybridHeuristicBoth.o: include/SolveMMDPHybridHeuristicSum.h
obj/SolveMMDPHybridHeuristicRandom.o: include/SolveMMDPHybridHeuristicRandom.h


clean:
	rm -rf obj $(EXEC)